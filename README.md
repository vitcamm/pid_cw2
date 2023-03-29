# pid_cw2
classwork 2 - pid controller

Controller is initialized with hardcoded gains:
Kp=0.1
Ki=1
kd=0.0001.
Kp and Kd are small because there is no system dynamics to control, and because of that the output starts oscillating and diverges.
Sampling time chosen is 1ms; 
the program outputs two textfiles, one with the computed control value and one with the corresponding references. 
Main functions writes these two files, and user inputs are handled by an interface thread. Matlab plot following:



![PIDplot](https://user-images.githubusercontent.com/101279876/227035297-032fa61b-9055-4f55-a113-7f347683fb6b.png)
