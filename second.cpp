/**
 * Monte Carlo Part of the Algorithm
 * @authors Jatin Pandya, Tianhui Zhou
 * @since 10/17/2019
 */

#include <iostream>
#include <random>
#include <iterator>
#include <map>
#include <vector>
#include <time.h>
#include <stdlib.h>

using namespace std;
//void MonteCarlo (map*, vector*, vector*, int*);
// Why did we switch the MonteCarlo method from void to int?
int MonteCarlo (map<int, map<int, int> >& classTable, vector<vector<int> >& schedule, vector<vector<int> >& schedule2, vector<int> crnTeacher, int cost) {

	
    int unincrease, iteration, max_iteration, dif_cost;
	

	iteration = 0;
	max_iteration = 10;//testing
	unincrease = 0;
	dif_cost = 0; // move if > 0

    int max_unincrease = 5;//testing
    
    srand((unsigned int)time(NULL));



	while (iteration < max_iteration) {
        cout<<"****** Round "<<iteration+1<<" ******"<<endl;
		int crn_course = (rand() % 4);
        cout<<"pick up the index of "<<crn_course<<" course."<<endl;
        	//get the index number of teacher from the container
		int index_teacher = crnTeacher[crn_course]; 
        
        	int loc_tem, time_tem, row_tem, col_tem;
		
        
        //get the loc_tem and time_tem from the map, it is inside of ClassTable
        map<int,int> temp = classTable[crn_course];
         time_tem = temp.begin()->first;
         loc_tem = temp.begin()->second;
        
        //the bounds of two variable depend on our total courses and classroom
        cout<<"randomly move a course:"<<endl;
		row_tem = (rand() % 3) ; //time
        cout<<"randomly generate a number for new time: "<<row_tem<<endl;
		col_tem = (rand() % 3) ; //location
        cout<<"randomly generate a number for new location: "<<col_tem<<endl;
        cout<<"its current position is: "<<time_tem<<loc_tem<<endl;
        cout<<"the teacher index is: "<<crnTeacher[crn_course]<<endl;
        
		if (schedule[time_tem][loc_tem] >  1) { // clash in time&location
			if (schedule[row_tem][col_tem] == 0)
				dif_cost++;
		} else { //no clash
			if (schedule[row_tem][col_tem] > 0)
				dif_cost--;
		}
        
        if(row_tem != time_tem){
		if (schedule2[time_tem][index_teacher] > 1) { // there is a clash in time&teach
			if (schedule2[row_tem][index_teacher] == 0)
				dif_cost++;	
		} else {
			if (schedule2[row_tem][index_teacher] > 0) 
				dif_cost--;
		}
        }
        cout<<"the diffrence cost is: "<<dif_cost<<endl;
        
        // cost function updating
        
		if (dif_cost > 0) {
            cout<<"***** move it *****"<<endl;
			schedule[time_tem][loc_tem]--;
			schedule[row_tem][col_tem]++;
			schedule2[time_tem][index_teacher]--;
			schedule2[row_tem][index_teacher]++;
			cost = cost - dif_cost;
			//(row_tem,col_tem) -> classTable[crn_course];
            map<int, int> temp;
            temp[row_tem] = col_tem;
            classTable.erase(crn_course);
            classTable[crn_course] = temp;
			unincrease = 0;
            cout<<"check the map: "<<endl;
            for(int i = 0; i<4; ++i){
             cout<<classTable[i].begin()->first<<classTable[i].begin()->second<<endl;
            }
		} else {
			unincrease++;
		}
        cout<<"cost is: "<<cost<<endl;
        cout<<" "<<endl;
		if (unincrease == max_unincrease) break;
		if (cost == 0) break;
		iteration++;
        dif_cost=0;
	}
	return cost;
}
