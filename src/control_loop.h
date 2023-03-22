#include <iostream>
#include<unistd.h>
#include "boost/thread.hpp"



using namespace std;

class CONTROLLER {
    public:
        CONTROLLER(double kp, double ki, double kd,double Ts, double xdes);
        void loop();               //Main loop function        
        void system_start();       //start the system
        void set_xdes(double x);   //member to set the desired value
        void setFlag(bool flag);
        bool getFlag();
        double getXdes();
        double getval();
        double getErr();
    private:
        double _Kp;
        double _Ki;
        double _Kd;
        double _Integral;
        double _Ts;
        double _xdes;
        double _Val;
        double _Olderr;
        bool _stop;
};
