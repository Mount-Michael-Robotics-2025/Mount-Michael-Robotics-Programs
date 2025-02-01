#include <vector>
#include <cmath>
#include "vex.h"
#include "odometry.h"

using namespace vex;

namespace pid {
  float kP = 0.75;
  float kI = 0.004;
  float kD = 0;
  
  float rP = 0.75;
  
  float integral = 0;
  float derivative = 0;
  float prevError = 0;
  float power = 0;

  float lateralError = 0;
  float rotationError = 0;

  float outputL = 0;
  float outputR = 0;

  double accGtoIPSS(double gUnits) { // G-Units to Inches per Square Seconds
    return gUnits * 386.08858267717;
  }

  void resetPID() {
    integral = 0;
    prevError = 0;
    InertialSensor.calibrate(2);
    InertialSensor.resetRotation();
  }

  void lateral() {
    integral += lateralError;
    if (prevError == 0) {
      prevError = lateralError;
    }
    derivative = lateralError - prevError;
    prevError = lateralError;

    power = lateralError*kP + integral*kI - derivative*kD;
    outputL += power * 12;
    outputR += power * 12;
  }

  void rotate() { //Counterclockwise
    power = rotationError*rP;
    outputR += power * 12;
    outputL += power * -12;
  }

  void setGoal(float _lateralError, float _rotationError) {
    lateralError = _lateralError;
    rotationError = _rotationError;
  }

  void loop() {
    outputL = 0;
    outputR = 0;
    lateral();
    rotate();
  }
}

namespace boomerang {
  float carrotScale = 0.5;
  std::vector<std::vector<float>> actionPointMatrix;
  std::vector<std::vector<float>> localActionPointMatrix;

  void setLocalAction() {
    
  }
  void setCarrot() {
    
  }
  void loop() {

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