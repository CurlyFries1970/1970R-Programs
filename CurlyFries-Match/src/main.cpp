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
const char paletteName[2][6] = {"POLAR", "MOUNT"};
const char autonName[2][5] = {"AWAY", "NEAR"};
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
void switchTeams();
brainArt::sliderHorizontal teamButton(341, 41, 40, 20, 2, &team, &paletteCurrent[0], &paletteCurrent[1], &switchTeams);

void switchAuton();
brainArt::sliderVertical autonButton(441, 101, 40, 20, 2, &autonMode, &paletteCurrent[0], &paletteCurrent[1], &switchAuton);

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

void (*ctrl_symbol[3])() = {TANK, ARCA, _RC_};
/////

//Draw UI
void controllerInfo() {
  if (lockButtons == 0) {
    char message[100];
    Controller1.Screen.setCursor(0, 0);
    strcpy(message, "(X) Color: ");
    strcat(message, paletteName[team]);
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

void art() {
  Brain.Screen.clearScreen(palette[team][0]);
  paletteCurrent[0] = palette[team][0];
  paletteCurrent[1] = palette[team][1];

  teamButton.drawToScreen();
  autonButton.drawToScreen();
  controlButton.drawToScreen();
  lockButton.drawToScreen();

  uiText();

  ctrl_symbol[controlMode]();

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
  teamButton.pressTest(Brain.Screen.xPosition(), Brain.Screen.yPosition());
  autonButton.pressTest(Brain.Screen.xPosition(), Brain.Screen.yPosition());
  controlButton.pressTest(Brain.Screen.xPosition(), Brain.Screen.yPosition());
  lockButton.pressTest(Brain.Screen.xPosition(), Brain.Screen.yPosition());
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