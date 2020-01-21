/* annealing simulated algorithm
 */

#include <stdio.h>
#include <time.h>
#include <random>
#include <map>
#include <vector>

using namespace std;
//void annealingSimulated ()
int third(map<int, map<int,int> >& classTable, vector<vector<int> >& schedule, vector<vector<int> >& schedule2, vector<int> crnTeacher, int tCost){
    int T = 500;//the temperature of system, the initial T should be a high temperature
    int T_min = 50;//the temperature of system, the initial T should be a high temperature
    double r = 0.80;//a factor to control the speed of cool down
    int increase_max = 10;//need to test
    int increase = 0;
    int dCost = 0;
    int max_swap = 10;//need to test
    int cur_swap = 0;
    
    while(T > T_min){
        while(cur_swap < max_swap){
            if(tCost == 0) return tCost;// no class clash anymore
            
            dCost=0;
            
            int crn_course = rand() % 4;// assume we have 4 courses in campus
            map<int,int> temp = classTable[crn_course];
            int time_tem = temp.begin()->first;
            int loc_tem = temp.begin()->second;
            int index_teacher = crnTeacher[crn_course];
            int row_tem = rand() % 3;//time we have
            int col_tem = rand() % 3;//classroom we have 
            //debug
            cout<<"the new position is "<<row_tem<<col_tem<<endl;
            cout<<"the previous is: "<<time_tem<<loc_tem<<endl;
            cout<<"the index of course is: "<<crn_course<<endl;
            
            if(schedule[time_tem][loc_tem]>1){//there is class clash on time&room
                cout<<"the current schedule: "<<schedule[time_tem][loc_tem]<<endl;
                cout<<"the new position: "<<schedule[row_tem][col_tem]<<endl;
                   if(schedule[row_tem][col_tem]==0){
                dCost++;
                }
             }else{// there no class clash on time&room
                  if(schedule[row_tem][col_tem] > 0){
                dCost--;
                }
             }

              if(schedule2[time_tem][index_teacher]>1){// there is a clash about time&tec
                if(schedule2[row_tem][index_teacher]==0){
                    dCost++;
                }
             }else{//there no class clash about time&tec
                  if(schedule2[row_tem][index_teacher] > 0){
                dCost--;
                }
            }
            
            cout<<"the diffrence cost is: "<<dCost<<endl;
            if(dCost>0){//after move it, we get a better solution, so we always accept the move
                //accept the move from C(i) to C(i+1)
                schedule[time_tem][loc_tem]--;
                schedule[row_tem][col_tem]++;
                schedule2[time_tem][index_teacher]--;
                schedule2[row_tem][index_teacher]++;
                tCost = tCost - dCost;
                //(row_tem,col_tem) -> classTable[crn_course];
                map<int, int> temp;
                temp[row_tem] = col_tem;
                classTable.erase(crn_course);
                classTable[crn_course] = temp;
                increase++;
            }
            else
            {
            //if we don't get a better solution or even make it worse, we accept the move by some probability. The probability should decrease as time goes on.
                
            // the range of the function exp(dE/T) is (0,1), if dE/T goes up, the exp(dE/T) also increase.
                double num_random = (rand() % 100)/100;
                if ( exp( -dCost/T ) > num_random ){
                    cout<<"doing this part"<<endl;
                    schedule[time_tem][loc_tem]--;
                    schedule[row_tem][col_tem]++;
                    schedule2[time_tem][index_teacher]--;
                    schedule2[row_tem][index_teacher]++;
                    tCost = tCost - dCost;
                    //(row_tem,col_tem) -> classTable[crn_course];
                    map<int, int> temp;
                    temp[row_tem] = col_tem;
                    classTable.erase(crn_course);
                    classTable[crn_course] = temp;
                    increase++;
                }
            }
            //check the totall cost if it is 0, we get the solution
            if(tCost == 0) return tCost;// no class clash anymore
            cout<<"current cost is "<<tCost<<endl;
            for(int i = 0; i<4; ++i){
                cout<<classTable[i].begin()->first<<classTable[i].begin()->second<<endl;
                
            }
            if(increase == increase_max){
                increase = 0;
                cur_swap = 0;
                break;
            }
           // i++;
            cur_swap++;
        }//ends while
        cur_swap=0;
        T = r * T ; //decrease the temperature,0.8<r<0.99. 
/*
 * if r is too big, we will have a high probability to get the optimization of whole picture, but it gonna take a long time. If r is too small, the process of searching will be really fast, but we might just get a partial optimization
 */
    }//ends while
    return tCost;
}
