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

    double kp;
    double ki;
    double kd;
    double Ts;
    double xdes;
    
    if(argc==1){
        kp=0.1;
        ki=1;
        kd=0.0001;
        Ts=0.001; 
        xdes=0.0; 
    } else if ((argc>1 && argc<6)||(argc>6)){
        cout<<"Numero di argomenti: "<<argc<<endl;
        cout<<"Errore"<<endl;
        return 0;
    } else {
        kp=atof(argv[1]);
        cout<<"kp: "<<kp<<endl;
        ki=atof(argv[2]);
        cout<<"ki: "<<ki<<endl;
        kd=atof(argv[3]);
        cout<<"kd: "<<kd<<endl;
        Ts=atof(argv[4]);
        cout<<"sample time: "<<Ts<<endl;
        xdes=atof(argv[5]);
    }
    
    cout<<"\nref:"<<endl;
    cin>>refsignal;

    //double kp, double ki, double kd,double Ts, double xdes
    CONTROLLER Pid(kp,ki,kd,Ts, xdes);
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
        usleep(0.001*1e6);
    }while(!stop);

    ref.close();
    log.close();
    return 0;
}
