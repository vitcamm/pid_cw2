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
    ofstream ref;
    bool stop;

    
    cout<<"\nref:"<<endl;
    cin>>refsignal;


    CONTROLLER Pid(0.1, 1, 0.0001, 0.001, 0);
    log.open("control_input_log.txt");
    ref.open("reference.txt");
    cout<<"\nSystem start:"<<endl;
    
    Pid.system_start();
    Pid.set_xdes(refsignal);
    cout<<"\nInitial value:\t"<<Pid.getval()<<endl;
    boost::thread terminate_t(&interface, &Pid);
    
    
    do{ 
        log<<Pid.getval()<<endl;
        ref<<Pid.getXdes()<<endl;
        stop=Pid.getFlag();
        usleep(0.01*1e6);
    }while(!stop);

    ref.close();
    log.close();
    return 0;
}
