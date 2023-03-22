# pid_cw2
classwork 2 - pid controller

Controller is initialized with hardcoded gains:
Kp=0.1
Ki=1
kd=0.0001
kp and kd are small because since there is no system dynamics to control the output starts oscillating and diverges.
Sampling time chosen is 1ms; 
the program outputs two textfiles, one with the computed control value and one with the corresponding references. 
Main functions writes these two files, and user inputs are handled by an interface thread.



