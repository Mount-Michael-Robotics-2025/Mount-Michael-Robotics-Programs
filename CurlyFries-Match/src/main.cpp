#include "vex.h"
#include "ui-library-v1.cpp"
#include "autonPID.h"

using namespace vex;

competition Competition;
/////

/*  IMPORTANT INFO
  > Main 4 settings mapped to ABXY controller buttons and brain screen buttons
    > Settings displayed on brain screen and controller screen
    > (A) Auton
      > Changes auton based off of starting location on field
      > Currently no difference
    > (B) Control
      > Switches how movement is handled
      > Refer to below control schemes
    > (X) Team
      > Purely cosmetic
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
const color palette[2][2] = {{ClrNavy, ClrWhite}, {ClrMaroon, ClrBlack}}; //{bg color, accent color}
const char paletteName[2][6] = {"POLAR", "MOUNT"};
const char autonName[3][5] = {"SKLS", "AWAY", "NEAR"};
const char controlName[3][5] = {"TANK", "ARCA", "-RC-"};
/////

//Settings
int team = 0;
color paletteCurrent[2] = {palette[team][0], palette[team][1]};
int autonMode = 0; 
int controlMode = 2;
int lockButtons = 0;
bool reverseDrive = false; //Reverses what side the program considers to be the front
bool flyWheelMode = false;
/////

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
brainArt::buttonHorizontal controlButton(341, 201, 40, 20, &paletteCurrent[0], &paletteCurrent[1], &writeControls, &switchControls);

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

//Draw UI
void controllerInfo() {
  if (lockButtons == 0) {
    char message[100];
    Controller1.Screen.setCursor(0, 0);
    strcpy(message, "(X) Color: "); //Essentially {message = ""}
    strcat(message, paletteName[team]); //Essentially {message += ""}
    Controller1.Screen.print(message);
    Controller1.Screen.newLine();
    strcpy(message, "(A) Auton: ");
    strcat(message, autonName[autonMode]);
    Controller1.Screen.print(message);
    Controller1.Screen.newLine();
    strcpy(message, "(B) Control: ");
    strcat(message, controlName[controlMode]);
    Controller1.Screen.print(message);
  } else {
    char message[100];
    Controller1.Screen.setCursor(0, 0);
    strcpy(message, "(Y) Color: ");
    strcat(message, paletteName[team]);
    Controller1.Screen.print(message);
    Controller1.Screen.newLine();
    strcpy(message, "(Y) Auton: ");
    strcat(message, autonName[autonMode]);
    Controller1.Screen.print(message);
    Controller1.Screen.newLine();
    strcpy(message, "(Y) Control: ");
    strcat(message, controlName[controlMode]);
    Controller1.Screen.print(message);
  }
}

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

void switchDirection() {
  reverseDrive = not reverseDrive;
}

void switchFlyWheel() {
  flyWheelMode = not flyWheelMode;
}
/////

//Onscreen Button Handler
void buttons() {
  teamButton.pressTest(Brain.Screen.xPosition(), Brain.Screen.yPosition());
  autonButton.pressTest(Brain.Screen.xPosition(), Brain.Screen.yPosition());
  controlButton.pressTest(Brain.Screen.xPosition(), Brain.Screen.yPosition());
  lockButton.pressTest(Brain.Screen.xPosition(), Brain.Screen.yPosition());
}
/////

//Auton Shortcuts
void driveUp(float lDrive, float rDrive) {
  if (fabsf(rDrive) > fabsf(lDrive)) {
    SmallL.spinFor(fwd, (360 * lDrive), degrees, false);
    SmallR.spinFor(fwd, (360 * rDrive), degrees, false);
    FrontL.spinFor(fwd, (360 * lDrive), degrees, false);
    FrontR.spinFor(fwd, (360 * rDrive), degrees, false);
    MidL.spinFor(fwd,(360 * lDrive), degrees, false);
    MidR.spinFor(fwd, (360 * rDrive), degrees, false);
    BackL.spinFor(fwd, (360 * lDrive), degrees, false);
    BackR.spinFor(fwd, (360 * rDrive), degrees);
  } else {
    SmallR.spinFor(fwd, (360 * rDrive), degrees, false);
    SmallL.spinFor(fwd, (360 * lDrive), degrees, false);
    FrontR.spinFor(fwd, (360 * rDrive), degrees, false);
    FrontL.spinFor(fwd, (360 * lDrive), degrees, false);
    MidR.spinFor(fwd, (360 * rDrive), degrees, false);
    MidL.spinFor(fwd,(360 * lDrive), degrees, false);
    BackR.spinFor(fwd, (360 * rDrive), degrees, false);
    BackL.spinFor(fwd, (360 * lDrive), degrees);
  }
}

void setDrivetrainV(int vel) {
  SmallL.setVelocity(vel, pct);
  SmallR.setVelocity(vel, pct);
  FrontL.setVelocity(vel, pct);
  FrontR.setVelocity(vel, pct);
  MidL.setVelocity(vel, pct);
  MidR.setVelocity(vel, pct);
  BackL.setVelocity(vel, pct);
  BackR.setVelocity(vel, pct);
}
/////

//Autonomous Modes
void autonNear() {
  pid::travel(3, 3);
}

void autonAway() {
}

void autonSkills() {
}

void (*autonList[3])() = {autonSkills, autonAway, autonNear};
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
  Controller1.ButtonL1.pressed(switchDirection);
  Controller1.ButtonR2.pressed(switchFlyWheel);

}
/////

//Autonomous Period
void autonomous(void) {
  autonList[autonMode]();
}
/////

//User Control
float driftL = 1; //Adjust for drift in robot
float driftR = 1;
void userControl(void) {
  while (true) {
    //Control
    int trainL[3] = {Controller1.Axis3.value(),
    (Controller1.Axis3.value() + (Controller1.Axis4.value() * 2 / 3)),
    (Controller1.Axis3.value() + (Controller1.Axis1.value() * 2 / 3))};
    int trainR[3] = {Controller1.Axis2.value(),
    (Controller1.Axis3.value() - (Controller1.Axis4.value() * 2 / 3)),
    (Controller1.Axis3.value() - (Controller1.Axis1.value() * 2 / 3))};

    //bool reverseDrive = Controller1.ButtonL1.pressing();

    int trainLVolt = driftL * 0.120 * ((trainL[controlMode] * not reverseDrive) - (trainR[controlMode] * reverseDrive));
    int trainRVolt = driftR * 0.120 * ((trainR[controlMode] * not reverseDrive) - (trainL[controlMode] * reverseDrive));

    //Spin
    SmallL.spin(fwd, trainLVolt, voltageUnits::volt);
    SmallR.spin(fwd, trainRVolt, voltageUnits::volt);
    FrontL.spin(fwd, trainLVolt, voltageUnits::volt);
    FrontR.spin(fwd, trainRVolt, voltageUnits::volt);
    MidL.spin(fwd, trainLVolt, voltageUnits::volt);
    MidR.spin(fwd, trainRVolt, voltageUnits::volt);
    BackL.spin(fwd, trainLVolt, voltageUnits::volt);
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