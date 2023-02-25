#include "Autonomous.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>

Autonomous::Autonomous(DriveTrain* dvtobj, RobotAuxilary* auxobj, Vision* camobj){
    drivetrain = dvtobj;
    utilties = auxobj;
    camera = camobj;
    m_chooser = new frc::SendableChooser<int>;//Allocate memory for the sendable chooser
    m_chooser->SetDefaultOption("Default", 0);
    m_chooser->AddOption("Straight Forward",1);
    m_chooser->AddOption("Custom 1", 2);
    frc::SmartDashboard::PutData(m_chooser);//Put options on smart dashboard
    print_timer = new Timer(250);//Set a timer for every 250ms for debug printing
}

void Autonomous::manageAuto(){
    switch(m_chooser->GetSelected()){
        case 1:
            straightForward(310);
            break;
        case 2:
            custom1();
            break;
        default:
            defaultAuto();
            break;

    }
}

void Autonomous::defaultAuto(){
    static int steps = 0;
    
    /*if(print_timer->getTimer()){
        //std::cout<<"Left Position: "<<drivetrain->getLeftPosition()<<std::endl;
       //std::cout<<"Right Position: "<<drivetrain->getRightPostion()<<std::endl;
       //std::cout<<"Angle: "<<drivetrain->getAngle()<<std::endl;
    }*/

    switch(steps){
        case 0:
            //utilties->togglePincher();
            steps++;
            break;
        case 1:
            if(utilties->moveArm(0.3)==2){
                steps++;
            }
            break;
        case 2:
            utilties->togglePincher();
            steps++;
            break;
        case 3:
            if(utilties->moveArm(-.3)==1){
                steps++;
            }
            break;
        case 4:
            if(drivetrain->relativeMoveForward(220,220)){
                //if possible lining up on the cube before getting to it would be a nice touch
                steps+=3;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;

        case 5:
                if(drivetrain->relativeTurn(camera->getStoredYaw()*2)){
                    drivetrain->resetFlags();
                    steps++;
                }
            break;

        case 6:
                if(drivetrain->relativeTurn(camera->getStoredYaw()*2)){
                    drivetrain->resetFlags();
                    camera->resetFlags();
                    steps++;
                }
            break;

        case 7:
                if(drivetrain->relativeMoveForward(95,95)){
                    drivetrain->resetFlags();
                    steps++;
                }
            break;
        case 8:
        if(print_timer->getTimer()){
            utilties->togglePincher();
            steps++;
        }
            break;
        
        case 9:
                if(drivetrain->relativeMoveBackward(10,10)){
                    drivetrain->resetFlags();
                    steps++;
                }
            break;

        
        case 10:
            if(drivetrain->relativeTurn(-45)){
                steps++;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;
        case 11:
            if (drivetrain->relativeMoveBackward(100,100)){
                steps++;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;
        case 12:
            if(drivetrain->relativeTurn(45)){
                drivetrain->resetFlags();
                steps++;
            }
            break;
        case 13:
            if(drivetrain->relativeMoveBackward(92.0,92.0)){
                drivetrain->resetFlags();
                steps++;
            }
            break;
        case 14:
            if(drivetrain->balance()){
                drivetrain->resetFlags();
                steps++;
            }
        default:
            break;
    }

}

void Autonomous::straightForward(double dist){
    if(print_timer->getTimer()){
        std::cout<<"Left Position: "<<drivetrain->getLeftPosition()<<std::endl;
        std::cout<<"Right Position: "<<drivetrain->getRightPostion()<<std::endl;
        std::cout<<"Angle: "<<drivetrain->getAngle()<<std::endl;
    }
    drivetrain->relativeMoveForward(dist,dist);
}

void Autonomous::custom1(){
    static int steps = 0;
    switch(steps){
        
        case 0:
            if(drivetrain->relativeMoveForward(50,50)){
                utilties->chram();
                //utilties->moveArm(0.5); //positive moves up
                steps++;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;
        case 1:
            if(drivetrain->relativeMoveBackward(50,50)){
                utilties->unChram();
                steps++;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;
        case 2:
            if(drivetrain->relativeTurn(-90)){
                steps++;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;
        case 3:
            if(drivetrain->relativeMoveForward(50,50)){
                steps++;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;
        case 4:
            if(drivetrain->relativeMoveBackward(50,50)){
                steps++;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;
        case 5:
            if(drivetrain->relativeTurn(-180)){
                steps++;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;
        case 6:
            if(drivetrain->relativeMoveForward(50,50)){
                steps++;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;
        case 7:
            if(drivetrain->relativeMoveBackward(50,50)){
                steps++;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;
        case 8:
            if(drivetrain->relativeTurn(10)){
                steps++;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;
        case 9:
            if(drivetrain->relativeMoveForward(50,50)){
                steps++;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;
        case 10:
            if(drivetrain->relativeMoveBackward(50,50)){
                steps++;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;
        case 11:
            if(drivetrain->relativeTurn(-10)){
                steps++;
                drivetrain->resetFlags();//Reset the flags to enable further steps
            }
            break;
        
        default:
            break;
    }
}




Autonomous::~Autonomous(){
    delete m_chooser;
}