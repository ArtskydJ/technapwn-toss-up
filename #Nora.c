#pragma config(Sensor, in1,    POT_LIFTR,      sensorPotentiometer)
#pragma config(Sensor, in2,    POT_LIFTL,      sensorPotentiometer)
#pragma config(Sensor, in3,    POT_SELECTOR,   sensorAnalog)
#pragma config(Sensor, in4,    GYRO,           sensorGyro)
#pragma config(Sensor, in5,    PWR_EXP_VLTG,   sensorPotentiometer)
#pragma config(Sensor, dgtl1,  QUAD_LEFT,      sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  QUAD_RIGHT,     sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  ULTRA_LEFT,     sensorSONAR_cm)
#pragma config(Sensor, dgtl7,  ULTRA_RIGHT,    sensorSONAR_cm)
#pragma config(Motor,  port1,           DRIVE_BL1,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           DRIVE_BR2,     tmotorVex393, openLoop)
#pragma config(Motor,  port3,           LIFT_R,        tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           DRIVE_FL,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5,           DRIVE_FR,      tmotorVex393, openLoop)
#pragma config(Motor,  port6,           INTK_L,        tmotorVex393, openLoop)
#pragma config(Motor,  port8,           LIFT_L,        tmotorVex393, openLoop)
#pragma config(Motor,  port9,           DRIVE_BL2,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          DRIVE_BR1,     tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define   NORA_C
//#define   FULL_DEBUG_STREAM
#include "DefinitionsAndDeclarations.c"
#include "Autos/Autos.c"
#include "Autos/Scripts.c"
#include "OtherFunctions.c"
#include "LastCurrentFunctions.c"
#include "Initialize.c"
#include "Timers.c"
#include "State.c"
#include "Sensors.c"
#include "Operator.c"
#include "Autonomous.c"
#include "Output.c"
#include "LCD.c"
#include "Sound.c"


			//============= Nora.c =============//
			//									//
			//    Author: Joseph Dykstra		//
			//      Team: Techna PWN Robotics	//
			//   Created: 2013-05-15			//
			//									//
			//============== 3018 ==============//


task main()
	{
	initializeAutonomous();
	initializeOutput();
	initializeLCD();
	initializeOther();
	while(1)
		{
		inputState();
		inputLCD();
		inputSensors();
		inputOperator();
		inputAutonomous();
		inputEmulator();
		inputTimers();
		

		processState();
		processLCD();
		if (sysState.curr == OPERATOR)
			{
			processScripts();
			processOperator();
			}
		else if (sysState.curr == AUTONOMOUS)
			{
			processAutonomous();
			}
		processErrors();

		outputMotion();
		outputLCD();
		outputSound();

		setAllLasts();
		constantLoopTime();
		}
	}


//These are here so that I can easily open them when #Nora.c is open
#include "Docs/#Bug List.txt"
#include "Docs/#To Do List.txt"
#include "Docs/#How To Program Auto Routine.txt"
