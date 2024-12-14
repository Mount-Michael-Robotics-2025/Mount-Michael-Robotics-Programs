#include "vex.h"

using namespace vex;

namespace pid {
  float kP = 0.75;
  float kI = 0.004;
  float kD = 0;
  
  float error = 0;
  float integral = 0;
  float derivative = 0;
  float prevError = 0;
  float power = 0;

  float runTime = 0;
  float distanceTraveled = 0;
  double velocity = 0; 

  double accGtoIPSS(double gUnits) { // G-Units to Inches per Square Seconds
    return gUnits * 386.08858267717;
  }

  void travel(float goalInches, int timeLimit = 999) {
    prevError = goalInches;
    error = goalInches;
    integral = 0;

    runTime = 0;
    distanceTraveled = 0;
    velocity = 0;

    InertialSensor.calibrate(2);

    while (fabsf(error) >= 0.5 && runTime < timeLimit) {
      error = goalInches - distanceTraveled;
      integral += error;
      derivative = error - prevError;
      prevError = error;

      power = error*kP + integral*kI - derivative*kD;
      DrivetrainAll.spin(fwd, power * 12, voltageUnits::volt);

      runTime += .02;
      velocity += accGtoIPSS(InertialSensor.acceleration(yaxis)) * .02;
      distanceTraveled += velocity * .02;
      wait(20, msec);
    }
  }
  void rotate(float goalDegrees, int timeLimit = 999) { //Counterclockwise
    prevError = goalDegrees;
    error = goalDegrees;
    integral = 0;

    runTime = 0;

    InertialSensor.calibrate(2);
    InertialSensor.resetRotation();

    while (fabsf(error) >= 0.5 && runTime < timeLimit) {
      error = goalDegrees - InertialSensor.rotation(deg);
      integral += error;
      derivative = error - prevError;
      prevError = error;

      power = error*kP + integral*kI - derivative*kD;
      DrivetrainR.spin(fwd, power * 12, volt);
      DrivetrainL.spin(fwd, -power * 12, volt);

      runTime += .02;
      wait(20, msec);
    }
  }
}

namespace directMove {
  void travelInches(float lInches, float rInches, int mirror) {
    lInches *= (1 / (3.25 * 3.1416));
    rInches *= (1 / (3.25 * 3.1416));
    DrivetrainL.spinFor(((lInches * !mirror) + (rInches * mirror)) * 360, deg, false);
    DrivetrainR.spinFor(((rInches * !mirror) + (lInches * mirror)) * 360, deg);
  }
  void travelInches(float lInches, float rInches, int mirror, bool cont) {
    lInches *= (1 / (3.25 * 3.1416));
    rInches *= (1 / (3.25 * 3.1416));
    DrivetrainL.spinFor(((lInches * !mirror) + (rInches * mirror)) * 360, deg, false);
    DrivetrainR.spinFor(((rInches * !mirror) + (lInches * mirror)) * 360, deg, cont);
  }
}