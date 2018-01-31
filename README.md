# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## PID components

* The P component is the component that is directly proportional to the cross track error (by a given factor). This factor is a hyper parameter. Increasing the factor makes the car oscillate faster thus making it unstable.

* The D component is the component that is directly proportional to the rate of change of cross track error (by a given factor). This factor is a hyper parameter. This component helps us to the reduce the amount of ocillation introduced by the P factor. But the by product of this component is that it is possible to have larger error for sustained amount of time and thus never reaching its trajectory.

* The I component is the component that is directly proportinal to the sum of all cross track errors (by a given factor). This factor is a hyper parameter. This component mitigates the possibility of sustained high cross track error over a period of time due both P and D components. This helping the car steer towards its trajectory.


## Hyper-parameter choice

For the project submission I have manually tried various hyper parameters starting from 0.5 for all the three parameters and adjusted them accordingly untill the car completes the track. 
I implemented twiddle and tried to use it to search for better parametrs but found it much harder to do. 
Twiddle call is commented out in the current submission.
Also I used sum of last 100 cross track errors for i_error instead of all the errors. This seems to work for this track.

