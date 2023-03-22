#include "control_loop.h"

//We can use the class constructor to set parameters
CONTROLLER::CONTROLLER(double kp, double ki, double kd, double Ts, double xdes) {
    _Kp=kp;
    _Ki=ki;
    _Kd=kd;
    _Integral=0.0;      //Il valore dell'integrale è sempre inizializzato a zero
    _Ts=Ts;             //Sample time
    _xdes=xdes;
    _Val=0.0;
    _Olderr=0.0;
    _stop=false;
    boost::thread loop_t(&CONTROLLER::loop, this);    
}


//Sense: get input to change the state of our System
void CONTROLLER::set_xdes(double x) {
    _xdes=x;
}

void CONTROLLER::setFlag(bool flag){
    _stop=flag;
}

bool CONTROLLER::getFlag(){ 
    return _stop;
}
double CONTROLLER::getval(){
    return _Val;
}

//Random initial value
void CONTROLLER::system_start() {
    _Val=rand() % 10;
}

double CONTROLLER::getErr(){
    return _Olderr;
}



void CONTROLLER::loop() {
    double e=0.0; //errore
    double diff;
    //Control input
    while(_stop==false){
        _Olderr=e;
        e=_xdes-_Val;
        _Integral+=e*_Ts;
        diff=(e-_Olderr)/_Ts;
        _Val=_Kp*e+_Ki*_Integral+ _Kd*diff;
        usleep(0.01*1e6);
    }

}


