// Microduino_Stepper.cpp
//
// Copyright (C) 2009-2016 Shenyang
// $Id: Microduino_Stepper.cpp,v 1.00 2016/04/07 $

#ifndef __MICRODUINO_STEPPER_H__
#define __MICRODUINO_STEPPER_H__

#include <stdlib.h>
#include <Arduino.h>

#define _useTimer1
#define MAX_SPEED 	1024
#if F_CPU == 16000000
#define TIMER_COMP	160	//12.5K
#elif F_CPU == 8000000
#define TIMER_COMP	80 //12.5K
#endif


#define PIN_SET(pin) (*portOutputRegister(digitalPinToPort(pin)) |= digitalPinToBitMask(pin))
#define PIN_CLR(pin) (*portOutputRegister(digitalPinToPort(pin)) &= ~digitalPinToBitMask(pin))

#define MAX_STEPPERS 		4
#define INVALID_STEPPER		255 

#define PIN_EN  	4      //PORTB,0
#define PIN_DIRA 	A0    //PORTA,7
#define PIN_STEPA 	5   //PORTB,1
#define PIN_DIRB 	A1    //PORTA,6
#define PIN_STEPB 	6   //PORTB,2
#define PIN_DIRC 	A2    //PORTA,5
#define PIN_STEPC 	7   //PORTB,3
#define PIN_DIRD 	A3    //PORTA,4
#define PIN_STEPD 	8   //PORTD,6

#define DEFAULT_ACCEL 120
#define DEFAULT_MAX_SPEED 1

void stepperAllEnable();
void stepperAllDisable();

class Stepper
{
public:
	 
	Stepper(uint8_t _dirPin, uint8_t _stepPin);
	
	uint8_t begin();
	
	uint8_t begin(uint16_t _maxSpeed);

	bool setSpeed(int16_t _speed);
 
	void setMaxAccel(uint16_t _accel);
	
	void setMaxSpeed(uint16_t _maxSpeed);

	int16_t getSpeed();
	
	uint16_t getMaxAccel();
	
	uint16_t getMaxSpeed();

	void computeStep();
private:

	uint8_t 	stepperIndex;
	uint8_t 	dirPin;
	uint8_t 	stepPin;
	int16_t		speed;
	uint16_t	maxAccel;
	uint16_t 	maxSpeed;
	uint16_t 	period;
	uint16_t	counter;

};


class StepServo
{
public:
    
    StepServo(uint8_t _dirPin, uint8_t _stepPin);
	
	uint8_t begin();
	void setMaxSpeed(float _speed);
    void setAcceleration(float acceleration);
	float getAcceleration();
	void setSpeed(float _speed);
	float getSpeed();
	bool runSpeedToPosition();
	void setCurrentPosition(int32_t position);
	int32_t getCurrentPosition();
	int32_t getTargetPosition();
	int32_t distanceToGo();
	void moveTo(int32_t _absolute);
	void move(int32_t _relative);
	void runToPosition();
	void runToNewPosition(int32_t position);
	void runDistance(int32_t _relative);
	void stop();
	void run();

private:
	typedef enum{
		DIRECTION_CCW = 0,  ///< Clockwise
        DIRECTION_CW  = 1   ///< Counter-Clockwise
    } Direction;
    
	uint8_t 	stepperIndex;
	uint8_t 	dirPin;
	uint8_t 	stepPin;
	int32_t  	currentPos = 0;    // Steps
    int32_t  	targetPos = 0;     // Steps
    float    	speed = 0;         // Steps per second
    float    	maxSpeed;
    float    	accel = 1.0;
    uint32_t  	stepInterval = 0;
    uint32_t  	lastStepTime = 0;
    int32_t 	n = 0;
    float 		c0 = 0.0;
    float 		cn = 0.0;
    float 		cmin = 1.0; // at max speed
    bool 		direction; // 1 == CW
	
	void computeNewSpeed();
	bool runSpeed();
	void step();

};

typedef struct{
	uint8_t isActive = false;
	Stepper *stepper;
}Stepper_t;


#endif

  

