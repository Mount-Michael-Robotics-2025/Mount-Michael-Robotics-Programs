# 1970B Programming Journal

<details>
<summary> 03/20/24 </summary>

  I have started looking into PIDs to improve our autons. I laid out a skeleton for the process here.
  ###### *Future me here. This is absolutely full of errors. I didn't have the robot with me to test the program and it shows.* 🙃

```cpp
//PID
namespace pid {
    int kP = 0.01;
    int kI = 0;
    int kD = 0;
    
    int lError = 0;
    int rError = 0;

    int lIntegral = 0;
    int rIntegral = 0;
        
    int lDerivative = 0;
    int rDerivative = 0;

    int lPrevError = 0;
    int rPrevError = 0;

    int lPower = 0;
    int rPower = 0;
        

    void travel(int* lTraveled, int* rTraveled, int lDrive, int rDrive) {
        lPrevError = lDrive;
        rPrevError = rDrive;
        
        while (lError != 0 && rError != 0) {
            lError = lDrive - *lTraveled;
            rError = rDrive - *rTraveled;

            lIntegral += lError;
            rIntegral += rError;

            lDerivative = lError - lPrevError;
            rDerivative = rError - rPrevError;

            lPrevError = lError;
            rPrevError = rError;

            lPower = lError*kP + lIntegral*kI + lDerivative*kD;
            rPower = rError*kP + rIntegral*kI + rDerivative*kD;

            SmallL.spin(fwd, lPower, voltageUnits::volt);
            SmallR.spin(fwd, lPower, voltageUnits::volt);
            FrontL.spin(fwd, lPower, voltageUnits::volt);
            FrontR.spin(fwd, rPower, voltageUnits::volt);
            MidL.spin(fwd, rPower, voltageUnits::volt);
            MidR.spin(fwd, rPower, voltageUnits::volt);
            BackL.spin(fwd, rPower, voltageUnits::volt);
            BackR.spin(fwd, rPower, voltageUnits::volt);

            wait(20, msec);
        }
    }
}
/////
```
</details>

<details>
<summary> 03/22/24 </summary>
In anticipation of the upcoming competition, I made a set of functions for a potential mecanum wheel + omniwheel drivetrain. The mecanum wheels would be on the four corners, connected to their own motors in order to achieve basic mecanum motion. The omni wheels would be inbetween the mecanum wheels and add power to forward/backward movement and, theoretically, to diagonal movement too.
  
```cpp
//Theoretical Mecanum Wheel Drive
int mLeftFront() {
  return Controller1.Axis3.value() - Controller1.Axis3.value() + (Controller1.Axis1.value() * 2 / 3);
}
int mLeftBack() {
  return Controller1.Axis3.value() + Controller1.Axis3.value() + (Controller1.Axis1.value() * 2 / 3);
}
int mLeftCenter() {
  return (mLeftBack() + mLeftFront()) / 2;
}
int mRightFront() {
  return Controller1.Axis3.value() + Controller1.Axis3.value() - (Controller1.Axis1.value() * 2 / 3);
}
int mRightBack() {
  return Controller1.Axis3.value() - Controller1.Axis3.value() - (Controller1.Axis1.value() * 2 / 3);
}
int mRightCenter() {
  return (mRightBack() + mRightFront()) / 2;
}
/////
```

</details>
