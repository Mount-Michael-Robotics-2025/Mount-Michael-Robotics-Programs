# 1970B Programming Journal

### 03/20/24

  I have started looking into PIDs to improve our autons. I laid out a skeleton for the process here. 

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
