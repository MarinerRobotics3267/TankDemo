#include "DriveControl.h"
#include <cmath>

DriveControl::DriveControl(){
    controller_1 = new frc::XboxController(0);//Init main controller
    controller_2 = new frc::XboxController(1);//Init secondary controller
    drivebase = new DriveTrain();//Init our drive train
    is_tank_drive = true;//Start the robot in tank drive mode
    //Timers
    shift_timer = new Timer(300);//Delay time in milliseconds
    drive_switch_timer = new Timer(300);//Delay time in milliseconds
}


void DriveControl::teleopController(){
    pollButtons();//Continuously check the state of the buttons on the xbox controllers and respond accordingly
    if(is_tank_drive){//if the tank drive boolean is true, then use tank dive
        tankOperation();//Use tank drive style
    }else {//else use reverse drive
        reverseTank();//Use traditional drive style
    }
}

void DriveControl::tankOperation(){
    drivebase->setSpeed(filterInput(controller_1->GetLeftY(),0.175),filterInput(controller_1->GetRightY(),0.175));//Set tank normal
}

void DriveControl::reverseTank(){//Need to test the math on this one
    drivebase->setSpeed(-filterInput(controller_1->GetLeftY(),0.175),-filterInput(controller_1->GetRightY(),0.175));//Set tank reverse
}

void DriveControl::traditionalDrive(){
    
}

double DriveControl::filterInput(double input, double threshold){
    double tempval = input;

    if(std::abs(tempval) > std::abs(threshold)){//if the value is above the threshold, then we just return it.
        return tempval;
    }

    return 0.0;//Return zero if the input from the controller does not reach above the threshold
}

void DriveControl::pollButtons(){
    //Change drive styles    
    if(controller_1->GetBackButton() && controller_1->GetStartButton() && drive_switch_timer->getTimer()){//Swap drive modes if start and back button are pushed simultaneously
        is_tank_drive = !is_tank_drive;//Swap tank drive state
    }
    //Shift gears
    if(controller_1->GetAButton() && shift_timer->getTimer()){//If they press the A button
        drivebase->attemptGearShift();//Attempt shift to opposite gear ratio
    }
}

DriveControl::~DriveControl(){
    //Free memory
    delete controller_1;
    delete controller_2;
    delete drivebase;
}