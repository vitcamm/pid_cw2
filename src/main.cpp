#include "control_loop.h"
#include <fstream>

using namespace std;

//the goal is to implement a simple PID controller, 
//running on input value to reach the desired one

// Sense: read a value from keyboard
// Plan:  generate the correct input
// Act:   set the input
int main(int argc, char** argv) {
    
    float refsignal=0;
    
    ofstream log;
    //ofstream err;

    CONTROLLER Pi(1, 0.0, 0.000, 0.001, 1);
    log.open("control_log.txt");
    //err.open("error_log.txt");
    //boost::thread t(boost::bind(&CONTROLLER::loop, &Pi))
    cout<<"\nref:"<<endl;
    cin>>refsignal;
    cout<<"\nSystem start:"<<endl;
    //Pi.system_start();
    Pi.set_xdes(refsignal);
    cout<<"\nValore iniziale: \t"<<Pi.getval()<<endl;
    
    
    do{
    
    log<<Pi.getval()<<endl;
    //err<<Pi.getErr()<<endl;
    usleep(0.1*1e6);
    }while(1);


    log.close();
    //err.close();
    return 0;
}
