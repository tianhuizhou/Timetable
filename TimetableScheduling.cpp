/* before we run the program, we need to know these information:
 * 1. total courses which need to be schedule: total_course
 * 2. when is the last avaliable time for taking a course: total_time
 * 3. how many classrooms we have: total_classroom
 * 4. how many teachers we have: total_teacher
 */
#include <iostream>
#include "first.cpp"
#include "second.cpp"
#include "third.cpp"

using namespace std;

int main() {
	// set up these premise variable
    int total_course = 4;
    int total_time = 3; // as the row_max
    int total_classroom = 3;// as the col_max
    int total_teacher = 3;
    
    //total cost that is class clash
    int cost = 0;
    //the key is crn, store another map that hold time & location
    map<int, map<int, int> > classTable;
    //schedule1 records the time and location for counting class clash
    vector<vector<int> > schedule;
    //schedule2 records the time and teacher for counting class clash
    vector<vector<int> > schedule2;
    //to record the courses and teachers
    vector<int> course_teacher;
    
    //input data to each container for testing
    //let do three classes first.
    //initialize the two containers of schedule, fill up 0 with three rows and cols
    vector<int> temp(3,0);
    for(int i = 0; i<3;++i){
        schedule.push_back(temp);
        schedule2.push_back(temp);
    }
    
    //initialize the course_teacher, the value is the number of a teacher.
    for(int i = 0; i<3; ++i){
    course_teacher.push_back(i);
    }
    course_teacher.push_back(1);//the teacher 1 will have two courses, which is class 1 and 3.(each number means index)
    
    cout<<"Start: randomly generated "<<endl;
    cost = first(classTable, schedule, schedule2, course_teacher, total_time, total_classroom);
    cout<<"total cost is: "<<cost<<endl;//debug the cost
    cout<<"check the map: "<<endl;
    for(int i = 0; i<4; ++i){
        cout<<classTable[i].begin()->first<<classTable[i].begin()->second<<endl;
        
    }
    //part 2
    cout<<"Testing part 2(Monte carlo): "<<endl;
    cost = MonteCarlo(classTable, schedule, schedule2, course_teacher, cost);
    cout<<"cost after montecarlo is: "<<cost<<endl;
    for(int i = 0; i<4; ++i){
        cout<<classTable[i].begin()->first<<classTable[i].begin()->second<<endl;
        
    }
    //part 3
    cout<<"Testing part 3(annealing simulated): "<<endl;
    cost = third(classTable, schedule, schedule2, course_teacher, cost);
    cout<<"cost after annealing simulated is: "<<cost<<endl;
	return 0;
}
