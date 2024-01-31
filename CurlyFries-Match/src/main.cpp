#include "vex.h"
#include "test-ui-library.cpp"

using namespace vex;

competition Competition;
/////

/*  IMPORTANT INFO
  > Control Schemes
    > TANK
      > L: [Axis 3]
      > R: [Axis 2]
    > ARCA (arcade)
      > L: [Axis 3] + ([Axis 4] / 2)
      > R: [Axis 3] - ([Axis 4] / 2)
    > -RC-
      > L: [Axis 3] + ([Axis 1] / 2)
      > R: [Axis 3] - ([Axis 1] / 2)
  > 
*/

//Constants
const color palette[2][2] = {{ClrNavy, ClrWhite}, {ClrMaroon, ClrBlack}}; //{bg color, accent color}
const char controlName[3][5] = {"TANK", "ARCA", "-RC-"};
/////

//Settings
int team = 0;
color paletteCurrent[2] = {palette[team][0], palette[team][1]};
int autonMode = 0; 
int controlMode = 0;
int lockButtons = 0;
/////

//Onscreen Buttons and Sliders

void buttonTeam() {
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFillColor(palette[team][1]);
  Brain.Screen.drawRectangle(341, 21, 40, 41);
  Brain.Screen.drawCircle(341, 41, 20);
  Brain.Screen.drawCircle(381, 41, 20);
  Brain.Screen.setPenColor(palette[team][0]);
  Brain.Screen.setFillColor(palette[team][0]);
  Brain.Screen.drawRectangle(341, 23, 40, 37);
  Brain.Screen.drawCircle(341, 41, 18);
  Brain.Screen.drawCircle(381, 41, 18);
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFillColor(palette[team][1]);
  Brain.Screen.drawRectangle(341, 37, 40, 9);
  Brain.Screen.drawCircle(341, 41, 4);
  Brain.Screen.drawCircle(381, 41, 4);
  Brain.Screen.drawCircle(341 + (team * 40), 41, 14);
}

void buttonAuton() {
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFillColor(palette[team][1]);
  Brain.Screen.drawRectangle(421, 101, 41, 40);
  Brain.Screen.drawCircle(441, 101, 20);
  Brain.Screen.drawCircle(441, 141, 20);
  Brain.Screen.setPenColor(palette[team][0]);
  Brain.Screen.setFillColor(palette[team][0]);
  Brain.Screen.drawRectangle(423, 101, 37, 40);
  Brain.Screen.drawCircle(441, 101, 18);
  Brain.Screen.drawCircle(441, 141, 18);
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFillColor(palette[team][1]);
  Brain.Screen.drawRectangle(437, 101, 9, 40);
  Brain.Screen.drawCircle(441, 101, 4);
  Brain.Screen.drawCircle(441, 141, 4);
  Brain.Screen.drawCircle(441, 101 + (40 * autonMode), 14);
}

void buttonControl() {
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFillColor(palette[team][1]);
  Brain.Screen.drawRectangle(341, 181, 40, 41);
  Brain.Screen.drawCircle(341, 201, 20);
  Brain.Screen.drawCircle(381, 201, 20);
  Brain.Screen.setPenColor(palette[team][0]);
  Brain.Screen.setFillColor(palette[team][0]);
  Brain.Screen.drawRectangle(341, 183, 40, 37);
  Brain.Screen.drawCircle(341, 201, 18);
  Brain.Screen.drawCircle(381, 201, 18);
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFillColor(palette[team][1]);
  Brain.Screen.drawRectangle(341, 185, 40, 33);
  Brain.Screen.drawCircle(341, 201, 16);
  Brain.Screen.drawCircle(381, 201, 16);
  Brain.Screen.setPenColor(palette[team][0]);
  Brain.Screen.setFont(mono20);
  Brain.Screen.printAt(341, 207, true, controlName[controlMode]);
}

void buttonLock() {
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFillColor(palette[team][1]);
  Brain.Screen.drawRectangle(261, 101, 41, 40);
  Brain.Screen.drawCircle(281, 101, 20);
  Brain.Screen.drawCircle(281, 141, 20);
  Brain.Screen.setPenColor(palette[team][0]);
  Brain.Screen.setFillColor(palette[team][0]);
  Brain.Screen.drawRectangle(263, 101, 37, 40);
  Brain.Screen.drawCircle(281, 101, 18);
  Brain.Screen.drawCircle(281, 141, 18);
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFillColor(palette[team][1]);
  Brain.Screen.drawRectangle(265, 101, 33, 40);
  Brain.Screen.drawCircle(281, 101, 16);
  Brain.Screen.drawCircle(281, 141, 16);
  Brain.Screen.setPenColor(palette[team][0]);
  Brain.Screen.setFillColor(palette[team][0]);
  Brain.Screen.drawCircle(281, 110, 8);
  Brain.Screen.drawRectangle(273, 110, 17, 8);
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFillColor(palette[team][1]);
  Brain.Screen.drawCircle(281, 110, 4);
  Brain.Screen.drawRectangle(277, 110, 9, 8);
  Brain.Screen.setPenColor(palette[team][0]);
  Brain.Screen.setFillColor(palette[team][0]);
  Brain.Screen.drawRectangle(271, 118, 21, 16);
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFillColor(palette[team][1]);
  Brain.Screen.drawCircle(281, 124, 3);
  Brain.Screen.drawRectangle(280, 124, 3, 8);
  if (lockButtons == 0) {
    Brain.Screen.drawRectangle(281, 110, 9, 8);
  }
}
/////

//UI Text
void uiText() {
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFillColor(palette[team][0]);
  Brain.Screen.setFont(mono12);
  Brain.Screen.printAt(314, 94, true,  "^ Color Switch ^");
  Brain.Screen.printAt(314, 114, true, "> Auton Switch >");
  Brain.Screen.printAt(314, 134, true, "< Lock Buttons <");
  Brain.Screen.printAt(314, 154, true, "v Control Mode v");
}
/////

//Draw Triangle
void drawTriangle(int pointX, int pointY, int steps) {
  for (int i = 0; i <= steps; i++) {
    Brain.Screen.drawLine(pointX - (i / 2), pointY + i, pointX + (i / 2), pointY + i);
  }
}
/////

//Draw Control Symbol
void TANK() {
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFillColor(palette[team][1]);
  Brain.Screen.drawRectangle(60, 60, 120, 120);
}

void ARCA() {
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFillColor(palette[team][1]);
  Brain.Screen.drawCircle(120, 120, 60);
}

void _RC_() {
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFillColor(palette[team][1]);
  drawTriangle(120, 60, 120);
}

void (*ctrl_symbol[3])() = {TANK, ARCA, _RC_};
/////

//Draw UI
void art() {
  Brain.Screen.clearScreen(palette[team][0]);
  paletteCurrent[0] = palette[team][0];
  paletteCurrent[1] = palette[team][1];

  buttonTeam();
  buttonAuton();
  buttonControl();
  buttonLock();

  uiText();

  ctrl_symbol[controlMode]();
}
/////

//Button Actions
void switchTeams() {
  if (lockButtons == 0) {
    team = ((team + 1) % 2);
    art();
  }
}

void switchAuton() {
  if (lockButtons == 0) {
    autonMode = ((autonMode + 1) % 2);
    art();
  }
}

void switchControls(void) {
  if (lockButtons == 0) {
    controlMode = ((controlMode + 1) % 3);
    art();
  }
}

void switchLock(void) {
  lockButtons = ((lockButtons + 1) % 2);
  art();
}
/////

//Pneumatics //Not in use right now
void flipWings() {
  if (SolenoidPair.value() == false) {
    SolenoidPair = true;
  } else {
    SolenoidPair = false;
  }
}
/////

//Onscreen Button Handler
void buttons() {
  if (Brain.Screen.xPosition() > 320 && Brain.Screen.yPosition() < 60) {
    switchTeams();
  }
  if (Brain.Screen.xPosition() > 420 && Brain.Screen.yPosition() > 80 && Brain.Screen.yPosition() < 160) {
    switchAuton();
  }
  if (Brain.Screen.xPosition() > 320 && Brain.Screen.yPosition() > 180) {
    switchControls();
  }
  if (Brain.Screen.xPosition() > 280 && Brain.Screen.xPosition() < 320 && Brain.Screen.yPosition() > 80 && Brain.Screen.yPosition() < 160) {
    switchLock();
  }
}
/////

/*
//Hold Catapult Still //Not in use
void brakingMech() {
  if (Controller1.ButtonL2.pressing()) {
    CatapultL.setStopping(hold);
    CatapultR.setStopping(hold);
    CatapultL.stop();
    CatapultR.stop();
  } else {
    CatapultL.setStopping(brake);
    CatapultR.setStopping(brake);
  }
}
/////
*/

//Drive Shortcut
void driveUp(double lDrive, double rDrive) {
  
  FrontL.spinFor(fwd, (360 * lDrive), degrees, false);
  MidL.spinFor(fwd,(360 * lDrive), degrees, false);
  BackL.spinFor(fwd, (360 * lDrive), degrees, false);
  FrontR.spinFor(fwd, (360 * rDrive), degrees, false);
  MidR.spinFor(fwd, (360 * rDrive), degrees, false);
  BackR.spinFor(fwd, (360 * rDrive), degrees, true);
}
/////

//Autonomous Modes
void autonClose() {
  FrontL.setVelocity(50, pct);
  MidL.setVelocity(50, pct);
  BackL.setVelocity(50, pct);
  FrontR.setVelocity(50, pct);
  MidR.setVelocity(50, pct);
  BackR.setVelocity(50, pct);

  driveUp(30, 30);
  driveUp(-20, -20);

  FrontL.setVelocity(100, pct);
  MidL.setVelocity(100, pct);
  BackL.setVelocity(100, pct);
  FrontR.setVelocity(100, pct);
  MidR.setVelocity(100, pct);
  BackR.setVelocity(100, pct);
}

void autonFar() {
  FrontL.setVelocity(50, pct);
  MidL.setVelocity(50, pct);
  BackL.setVelocity(50, pct);
  FrontR.setVelocity(50, pct);
  MidR.setVelocity(50, pct);
  BackR.setVelocity(50, pct);

  driveUp(70, 70);

  FrontL.setVelocity(100, pct);
  MidL.setVelocity(100, pct);
  BackL.setVelocity(100, pct);
  FrontR.setVelocity(100, pct);
  MidR.setVelocity(100, pct);
  BackR.setVelocity(100, pct);
}
/////

//Setup
void pre_auton(void) {
  //Initialize
  vexcodeInit();
  art();
  SolenoidPair = false;

  //Event Listeners
  Brain.Screen.pressed(buttons);
  Controller1.ButtonX.pressed(switchTeams);
  Controller1.ButtonA.pressed(switchAuton);
  Controller1.ButtonB.pressed(switchControls);
  Controller1.ButtonY.pressed(switchLock);
  Controller1.ButtonL1.pressed(flipWings);

}
/////

//Autonomous Period
void autonomous(void) {
  SolenoidPair = false;
  if (autonMode == 1) {
    autonClose();
  } else {
    autonFar();
  }
  flipWings();
}
/////

//User Control
void userControl(void) {
  while (true) {
    //Control
    int trainL[3] = {Controller1.Axis3.value(), (Controller1.Axis3.value() + (Controller1.Axis4.value() * 2 / 3)), (Controller1.Axis3.value() + (Controller1.Axis1.value() * 2 / 3))};
    int trainR[3] = {Controller1.Axis2.value(), (Controller1.Axis3.value() - (Controller1.Axis4.value() * 2 / 3)), (Controller1.Axis3.value() - (Controller1.Axis1.value() * 2 / 3))};

    int trainLVolt = 0.12 * trainL[controlMode];
    int trainRVolt = 0.12 * trainR[controlMode];

    //Spin
    FrontL.spin(fwd, trainLVolt, voltageUnits::volt);
    MidL.spin(fwd, trainLVolt, voltageUnits::volt);
    BackL.spin(fwd, trainLVolt, voltageUnits::volt);
    FrontR.spin(fwd, trainRVolt, voltageUnits::volt);
    MidR.spin(fwd, trainRVolt, voltageUnits::volt);
    BackR.spin(fwd, trainRVolt, voltageUnits::volt);
    wait(20, msec);
    }
}
/////

//Main
int main() {
  //Callbacks
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);

  //Run Pre-Auton
  pre_auton();

  //Prevent Wasted Resources
  while (true) {
    wait(100, msec);
  }
}
/////