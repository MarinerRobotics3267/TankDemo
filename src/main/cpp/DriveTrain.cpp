#include "DriveTrain.h"

/**
 * @brief Construct a new Drive Train:: Drive Train object
 *
 */
DriveTrain::DriveTrain()
{
    // Spark motor controller creation for neo brushless motors
    left_motor_1 = new rev::CANSparkMax(4, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    left_motor_2 = new rev::CANSparkMax(5, rev::CANSparkMax::MotorType::kBrushless);
    right_motor_1 = new rev::CANSparkMax(6, rev::CANSparkMax::MotorType::kBrushless);
    right_motor_2 = new rev::CANSparkMax(7, rev::CANSparkMax::MotorType::kBrushless);
    configureMotors();
    // Motor encoder creation for neo brushless motors
    // We have to create a copy of the object created by calling get encoder, which returns an object, not a pointer
    left_encoder_1 = new rev::SparkMaxRelativeEncoder(left_motor_1->GetEncoder());
    left_encoder_2 = new rev::SparkMaxRelativeEncoder(left_motor_2->GetEncoder());
    right_encoder_1 = new rev::SparkMaxRelativeEncoder(right_motor_1->GetEncoder());
    right_encoder_2 = new rev::SparkMaxRelativeEncoder(right_motor_2->GetEncoder());
    setZero();

    /*TalonFX Motor Controllers
    leftmotor1 = new ctre::phoenixpro::hardware::TalonFX(0,"");//Leave can name empty for auto init
    leftmotor2 = new ctre::phoenixpro::hardware::TalonFX(1,"");//Leave can name empty for auto init
    rightmotor1 = new ctre::phoenixpro::hardware::TalonFX(2,"");//Leave can name empty for auto init
    rightmotor2 = new ctre::phoenixpro::hardware::TalonFX(3,"");//Leave can name empty for auto init
    */
}

/**
 * @brief Configure the motors to turn in the correct direction relative to robot forward.
 * Used at startup
 *
 */
void DriveTrain::configureMotors()
{
    // Robot specific motor settings
    left_motor_1->SetInverted(true); // Invert left side motors since they are flipped
    left_motor_2->SetInverted(true); // Invert left side motors since they are flipped
    //
    left_motor_2->Follow(*left_motor_1);   // Have to dereference pointer since function is defined as pass by reference, so we need to
    right_motor_2->Follow(*right_motor_1); // pass the address of the object, not the address of the pointer
}

/**
 * @brief Set all encoders to zero. Used at startup
 *
 */
void DriveTrain::setZero()
{
    // Set the start position of the motor encoders to zero
    left_encoder_1->SetPosition(0.0);
    left_encoder_2->SetPosition(0.0);
    right_encoder_1->SetPosition(0.0);
    right_encoder_2->SetPosition(0.0);
}

/**
 * @brief Method to be used with robot snapshots. Does not evaluate relativity to left or right positions
 * 
 * @param lpos 
 * @param rpos 
 * @param lspd 
 * @param rspd 
 * @return true 
 * @return false 
 */
bool DriveTrain::moveTo(double lpos, double rpos, double lspd, double rspd)
{
    bool at_position = false;
   if(lpos == telemetry_link->left_position && rpos == telemetry_link->right_position){
    setSpeed(0.0,0.0);//If at position, stop motors
    at_position = true;
   }else{
    setSpeed(lspd,rspd);//If we are not at position, then set motors to the desired speed
   }
   return at_position;
}

/**
 * @brief Set the speed of the robots left and right motors
 *
 * @param ls Left side motor speed
 * @param rs Right side motor speed
 */
void DriveTrain::setSpeed(double ls, double rs)
{
    // Set the speeds for each side of the robots drive train
    left_motor_1->Set(ls);
    // leftmotor2->Set(ls);//Should be controlled by motor 1
    right_motor_1->Set(rs);
    // rightmotor2->Set(rs);//Should be controlled by motor 1
}

/**
 * @brief Links drivetrain data to the telemetry class
 *
 * @param dta Data packet being sent to the telemetry class
 */
void DriveTrain::loadTelemetry(SparkMaxPacket *dta)
{
    telemetry_link = dta;
}

/**
 * @brief Fill the data packet being sent with fresh data
 *
 */
void DriveTrain::updateTelemetry()
{
    // Update motor power
    telemetry_link->left_motor_power = left_motor_1->Get();   // Don't average since second motor is just a follower
    telemetry_link->right_motor_power = right_motor_1->Get(); // Don't average since second motor is just a follower
    // Update encoder positions
    telemetry_link->left_position = left_encoder_1->GetPosition() * left_encoder_2->GetPosition() / 2;    // Average the left side motor values and
    telemetry_link->right_position = right_encoder_1->GetPosition() * right_encoder_2->GetPosition() / 2; // Average the left side motor values
}

/**
 * @brief Destroy the Drive Train:: Drive Train object
 *
 */
DriveTrain::~DriveTrain()
{
    // Motors
    delete left_motor_1;
    delete left_motor_2;
    delete right_motor_1;
    delete right_motor_2;
    // Encoders
    delete left_encoder_1;
    delete left_encoder_2;
    delete right_encoder_1;
    delete right_encoder_2;
}