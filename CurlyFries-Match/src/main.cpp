#include "vex.h"
#include "ui-library-v1.h"
#include "autons.h"

using namespace vex;

competition Competition;
/////

/*  IMPORTANT INFO
  > Settings have been replaced by a bare bones auton selector, plans are to reincorporate after first semester
  > Main 4 settings mapped to ABXY controller buttons and brain screen buttons
    > Settings displayed on brain screen and controller screen
    > (A) Auton
      > Changes auton based off of starting location on field
      > Currently no difference
    > (B) Control
      > Switches how movement is handled
      > Refer to below control schemes
    > (X) Team
      > Changes team to account for mirrored starting positions
    > (Y) Lock
      > Disables all other buttons, preventing accidental presses mid match
      > Represented on controller by replacing screen button symbols with (Y)
  
  > Control Schemes
    > TANK
      > Joysticks control drivetrain sides independently
      > Best for testing
      > L: [Axis 3]
      > R: [Axis 2]
    > ARCA (arcade)
      > One joystick controls all directions
      > L: [Axis 3] + ([Axis 4] * 2 / 3)
      > R: [Axis 3] - ([Axis 4] * 2 / 3)
    > -RC-
      > Left joystick controls FWD/BKWD movement, right joystick controls turning
      > What we currently use most often
      > L: [Axis 3] + ([Axis 1] * 2 / 3)
      > R: [Axis 3] - ([Axis 1] * 2 / 3)
    > 2/3 is our preferred turn dampening, allowing precise movement while not sacrificing too much speed
*/

//Constants
/*
const color palette[2][2] = {{ClrNavy, ClrWhite}, {ClrMaroon, ClrBlack}}; //{bg color, accent color}
const char paletteName[2][6] = {"POLAR", "MOUNT"};
const char autonName[3][5] = {"SKLS", "AWAY", "NEAR"};
const char controlName[3][5] = {"TANK", "ARCA", "-RC-"};
*/
const char autonModeName[3][7] = {"Match", "Skills", "Off"};
const char autonColorName[2][5] = {"Red", "Blue"};
const char autonSideName[2][2] = {"+", "-"};
const char autonVariationName[2][7] = {"Light", "Greedy"};
/////

//Settings
int autonMode = 0;
int autonColor = 1;
//color paletteCurrent[2] = {palette[team][0], palette[team][1]};
int autonSide = 1; 
int autonVariation = 0;
/*
int controlMode = 2;
int lockButtons = 0;
*/
bool reverseDrive = false; //Reverses what side the program considers to be the front
/////

/*
//Onscreen Buttons and Sliders
void switchTeams();
brainArt::sliderHorizontal teamButton(341, 41, 40, 20, 2, &team, &paletteCurrent[0], &paletteCurrent[1], &switchTeams);

void switchAuton();
brainArt::sliderVertical autonButton(441, 101, 40, 20, 3, &autonMode, &paletteCurrent[0], &paletteCurrent[1], &switchAuton);

void switchControls();
void writeControls() {
  Brain.Screen.setPenColor(palette[team][0]);
  Brain.Screen.setFont(mono20);
  Brain.Screen.printAt(341, 207, true, controlName[controlMode]);
}
brainArt::buttonHorizontalP controlButton(341, 201, 40, 20, &paletteCurrent[0], &paletteCurrent[1], &writeControls, &switchControls);

void switchLock();
void drawLock() {
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
brainArt::buttonVertical lockButton(281, 101, 40, 20, &paletteCurrent[0], &paletteCurrent[1], &drawLock, &switchLock);
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

void (*ctrl_symbol[3])() = {&TANK, &ARCA, &_RC_};
/////
*/

//Draw UI
void controllerInfo() {
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(0, 0);

  char message[100];
  strcpy(message, "(A) Auton: ");
  strcat(message, autonModeName[autonMode]);
  Controller1.Screen.print(message);
  Controller1.Screen.newLine();

  if (autonMode == 0) {
    strcpy(message, autonColorName[autonColor]);
    strcat(message, " ");
    strcat(message, autonSideName[autonSide]);
    strcat(message, " ");
    strcat(message, autonVariationName[autonVariation]);
    Controller1.Screen.print(message);
    Controller1.Screen.newLine();
    strcpy(message, "(X)  (Y)  (B)");
    Controller1.Screen.print(message);
  }
}

/*
void writeAutonMode() {
  Brain.Screen.setPenColor(palette[team][1]);
  Brain.Screen.setFont(mono20);
  Brain.Screen.printAt(101, 207, true, autonName[autonMode]);
}

void drawDirectionArrow() {

}


void art() {
  Brain.Screen.clearScreen(palette[team][0]);
  paletteCurrent[0] = palette[team][0];
  paletteCurrent[1] = palette[team][1];

  teamButton.drawToScreen();
  autonButton.drawToScreen();
  controlButton.drawToScreen();
  lockButton.drawToScreen();

  ctrl_symbol[controlMode]();

  uiText();
  writeAutonMode();
  drawDirectionArrow();
  controllerInfo();
  
}
*/
/////


//Button Actions
/*
void switchTeams() {
  if (lockButtons == 0) {
    team = ((team + 1) % 2);
    art();
  }
}

void switchAuton() {
  if (lockButtons == 0) {
    autonMode = ((autonMode + 2) % 3);
    art();
  }
}

void switchControls() {
  if (lockButtons == 0) {
    controlMode = ((controlMode + 1) % 3);
    art();
  }
}

void switchLock() {
  lockButtons = ((lockButtons + 1) % 2);
  art();
}
*/

void switchDirection() {
  reverseDrive = not reverseDrive;
}

void switchMode() {
  autonMode++;
  autonMode %= 3;
  controllerInfo();
}

void switchColor() {
  autonColor++;
  autonColor %= 2;
  controllerInfo();
}

void switchSide() {
  autonSide++;
  autonSide %= 2;
  controllerInfo();
}

void switchVariation() {
  autonVariation++;
  autonVariation %= 2;
  controllerInfo();
}

void switchGoalClamp() {
  GoalClamp.set(not GoalClamp.value());
}
/////

/*
//Onscreen Button Handler
void buttons() {
  teamButton.pressTest(Brain.Screen.xPosition(), Brain.Screen.yPosition());
  autonButton.pressTest(Brain.Screen.xPosition(), Brain.Screen.yPosition());
  controlButton.pressTest(Brain.Screen.xPosition(), Brain.Screen.yPosition());
  lockButton.pressTest(Brain.Screen.xPosition(), Brain.Screen.yPosition());
}
/////
*/

//Setup
void pre_auton(void) {
  //Initialize
  vexcodeInit();
  //art();
  controllerInfo();

  //Event Listeners
  Controller1.ButtonA.pressed(switchMode);
  Controller1.ButtonX.pressed(switchColor);
  Controller1.ButtonY.pressed(switchSide);
  Controller1.ButtonB.pressed(switchVariation);
  Controller1.ButtonL1.pressed(switchDirection);
  Controller1.ButtonL2.pressed(switchGoalClamp);
  /*
  Brain.Screen.pressed(buttons);
  Controller1.ButtonX.pressed(switchTeams);
  Controller1.ButtonA.pressed(switchAuton);
  Controller1.ButtonB.pressed(switchControls);
  Controller1.ButtonY.pressed(switchLock);
  */
}
/////

//Autonomous Period
void autonomous(void) {
  if (autonMode == 0) {
    if (autonSide == 0) {
      if (autonVariation == 0) {
        matchAuton::lightP(&autonColor);
      } else {
        matchAuton::greedyP(&autonColor);
      }
    } else {
      if (autonVariation == 0) {
        matchAuton::lightN(&autonColor);
      } else {
        matchAuton::greedyN(&autonColor);
      }
    }
  } else if (autonMode == 1) {

  }
}
/////

//User Control
float driftL = 1; //Adjust for drift in robot
float driftR = 1;
void userControl(void) {
  while (true) {
    //Control

    /*
    int trainL[3] = {Controller1.Axis3.value(),
    (Controller1.Axis3.value() + (Controller1.Axis4.value() * 2 / 3)),
    (Controller1.Axis3.value() + (Controller1.Axis1.value() * 2 / 3))};
    int trainR[3] = {Controller1.Axis2.value(),
    (Controller1.Axis3.value() - (Controller1.Axis4.value() * 2 / 3)),
    (Controller1.Axis3.value() - (Controller1.Axis1.value() * 2 / 3))};

    int trainLVolt = driftL * 0.120 * ((trainL[controlMode] * not reverseDrive) - (trainR[controlMode] * reverseDrive));
    int trainRVolt = driftR * 0.120 * ((trainR[controlMode] * not reverseDrive) - (trainL[controlMode] * reverseDrive));
    */

    int trainLVolt = driftL * 0.12 * (Controller1.Axis3.value() + (Controller1.Axis1.value() * 2 / 3));
    int trainRVolt = driftR * 0.12 * (Controller1.Axis3.value() - (Controller1.Axis1.value() * 2 / 3));

    //Spin
    DrivetrainL.spin(fwd, trainLVolt, voltageUnits::volt);
    DrivetrainR.spin(fwd, trainRVolt, voltageUnits::volt);
    Belt.spin(fwd, 12 * (Controller1.ButtonR2.pressing() - Controller1.ButtonR1.pressing()), voltageUnits::volt);
    Intake.spin(fwd, 12 * (Controller1.ButtonR2.pressing() - Controller1.ButtonR1.pressing()), voltageUnits::volt);
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