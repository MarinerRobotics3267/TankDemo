// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "DriveControl.h"
#include "Telemetry.h"
#include "Vision.h"

DriveTrain drivetrain;                // Object to control drive motors
DriveControl controller(&drivetrain); // Create drive control object
Telemetry data(&drivetrain);          // Reference our drivetrain object
Vision vision;                        // Object for interfacing with camera

void Robot::RobotInit()
{
  // Link our drivetrain with our telemetry
  drivetrain.loadTelemetry(data.exportTelemetry());
} // Runs once one startup
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit()
{
  // Put auto startup code here. Runs once on auto start.

} // Runs once on auto start
void Robot::AutonomousPeriodic()
{
  // Put main auto code here. Called every 20s during auto.
  data.runMetrics(); // Constantly update robot position data
}

void Robot::TeleopInit() {} // Runs once on teleop start
void Robot::TeleopPeriodic()
{
  // Put main code here. Called every 20ms by default.
  controller.teleopController(); // Take input from controllers -- main control during teleop
  data.runMetrics();             // Constantly update robot position data

} // Put main teleop control code here

void Robot::DisabledInit() {}     // Garbage
void Robot::DisabledPeriodic() {} // Garbage

void Robot::TestInit() {}     // Garbage
void Robot::TestPeriodic() {} // Garbage

void Robot::SimulationInit() {}     // Garbage
void Robot::SimulationPeriodic() {} // Garbage

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
