#include "control_loop.h"
#include <fstream>

using namespace std;

//the goal is to implement a simple PID controller, 
//running on input value to reach the desired one

// Sense: read a value from keyboard
// Plan:  generate the correct input
// Act:   set the input

void interface(CONTROLLER* C){
    char control='a';
    double ref;
    do{
        cout<<"\nSet new Reference[r], Exit[y/n]"<<endl;
        //cout<<"Exit? [y/n]"<<endl;
        cin>>control;
        if(control=='y') {
        C->setFlag(true);
        }else if (control=='r'){
            cout<<"\nr:"<<endl;
            cin>>ref;
            C->set_xdes(ref);
        }else{
            C->setFlag(false);
        }
    } while(!C->getFlag());
}




int main(int argc, char** argv) {
    
    double refsignal=0;
    ofstream log;
    bool stop;
    double Ts=0.0;
    double Kp=0.0;
    double Ki=0.0;
    double Kd=0.0;

    cout<<"\nControllore PID";
    cout<<"Inserire Sample time:\t";
    cin>>Ts;    
    cout<<"\n Inserire Kp:\t";
    cin>>Kp;
    cout<<"\n Inserire Ki:\t";
    cin>>Ki;
    cout<<"\n Inserire Kd:\t";
    cin>>Kd;
    cout<<"\nref:"<<endl;
    cin>>refsignal;


    CONTROLLER Pid(Kp, Ki, Kd, Ts, 0);
    log.open("control_log2.txt");
    cout<<"\nSystem start:"<<endl;
    
    Pid.system_start();
    Pid.set_xdes(refsignal);
    cout<<"\nInitial value:\t"<<Pid.getval()<<endl;
    boost::thread terminate_t(&interface, &Pid);
    
    
    do{ 
        log<<Pid.getval()<<endl;
        stop=Pid.getFlag();
        usleep(0.01*1e6);
    }while(!stop);


    log.close();
    return 0;
}
