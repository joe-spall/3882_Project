#ifndef ELEGOO_H
#define ELEGOO_H
// Servo
#include <Servo.h>  //servo library

// Servo Pin definition
#define SERVO_PIN 3
// Servo Starting Pos
#define SERVO_CENTER_DEFAULT 90

// IR Remote
#include <IRremote.h>

//------- IR REMOTE CODES ---------//
#define FORWARD_CODE  16736925
#define BACKWARD_CODE 16754775
#define LEFT_CODE     16720605
#define RIGHT_CODE    16761405
#define STOP_CODE     16712445

// IR Receiver Pin 
#define RECV_REMOTE_PIN 12

// Motor Pin definition
#define RIGHT_MOTORS_PIN 6
#define LEFT_MOTORS_PIN 5
#define IN1_PIN 7
#define IN2_PIN 8
#define IN3_PIN 9
#define IN4_PIN 11

// Ultrasonic Pin definition
#define ECHO_PIN A4
#define TRIG_PIN A5

// Light Pin definition
#define LIGHT_RIGHT_PIN 10
#define LIGHT_CENTER_PIN 4
#define LIGHT_LEFT_PIN 2

enum IR_REMOTE_STATE
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    STOP
};

class Elegoo
{
    private:
        byte currPosServo;
        byte centerPosServo = 90;
        IR_REMOTE_STATE stateRemote = STOP;
        void writeSpeedMotor(float pwrLeft, float pwrRight);
        bool verifyPwrMotor(float pwrLeft, float pwrRight);
        bool verifyPosServo(byte angle);
    
    public:
        // Elegoo Constructor
        Elegoo();
        void init();
        // Motor Control
        void goForwardMotor(float pwrLeft, float pwrRight);
        void goBackwardMotor(float pwrLeft, float pwrRight);
        void goLeftMotor(float pwrLeft, float pwrRight);
        void goRightMotor(float pwrLeft, float pwrRight);
        void stopMotor();
        // Ultrasonic Control
        unsigned long getDistance();
        // Ultrasonic Servo Control
        Servo ultrasonicServo;      // create servo object to control servo
        byte getCenterServo();
        void setCenterServo(byte centerAngle);
        void goCenterServo();
        byte getPosServo();
        void setPosServo(byte angle);
        // Light Control
        bool isRightDark();
        bool isCenterDark();
        bool isLeftDark();
        // IR Control
        IRrecv &irrecv;
        decode_results resultsRemote;

        void setStateRemote();
        IR_REMOTE_STATE getStateRemote();
};
#endif
