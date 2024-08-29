#include "vex.h"
#include "robot-config.h"

using namespace vex;

namespace pid {
  float kP = 1;
  float kI = 0;
  float kD = 0;
  
  float lError = 0;
  float rError = 0;

  float lIntegral = 0;
  float rIntegral = 0;
      
  float lDerivative = 0;
  float rDerivative = 0;

  float lPrevError = 0;
  float rPrevError = 0;

  float lPower = 0;
  float rPower = 0;

  void travel(float lDrive, float rDrive) {
    lPrevError = lDrive;
    rPrevError = rDrive;

    lError = lDrive;
    rError = rDrive;

    BackL.resetPosition();
    BackR.resetPosition();

    while (fabsf(lError) >= 0.01 || fabsf(lError) >= 0.01) {
      lError = lDrive - (BackL.position(deg) / 360);
      rError = rDrive - (BackR.position(deg) / 360);

      lIntegral += lError;
      rIntegral += rError;

      lDerivative = lError - lPrevError;
      rDerivative = rError - rPrevError;

      lPrevError = lError;
      rPrevError = rError;

      lPower = lError*kP + lIntegral*kI - lDerivative*kD;
      rPower = rError*kP + rIntegral*kI - rDerivative*kD;

      FrontL.spin(fwd, lPower * 12, voltageUnits::volt);
      FrontR.spin(fwd, rPower * 12, voltageUnits::volt);
      MidL.spin(fwd, lPower * 12, voltageUnits::volt);
      MidR.spin(fwd, rPower * 12, voltageUnits::volt);
      BackL.spin(fwd, lPower * 12, voltageUnits::volt);
      BackR.spin(fwd, rPower * 12, voltageUnits::volt);

      wait(20, msec);
    }
  }
}