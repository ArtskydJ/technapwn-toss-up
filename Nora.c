#pragma config(Sensor, in1,    GYRO,           sensorGyro)
#pragma config(Sensor, in2,    POT_SELECTOR,   sensorPotentiometer)
#pragma config(Sensor, in3,    PWR_EXP_VLTG,   sensorAnalog)
#pragma config(Sensor, in4,    POT_LIFT,       sensorPotentiometer)
#pragma config(Sensor, in5,    POT_INTK,       sensorPotentiometer)
#pragma config(Sensor, dgtl1,  QUAD_LEFT,      sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  QUAD_RIGHT,     sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  ULTRA_LEFT,     sensorSONAR_cm)
#pragma config(Sensor, dgtl7,  ULTRA_RIGHT,    sensorSONAR_cm)
#pragma config(Motor,  port1,           DRIVE_BL1,     tmotorVex393, openLoop)
#pragma config(Motor,  port2,           DRIVE_BL2,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           DRIVE_FL,      tmotorVex393, openLoop)
#pragma config(Motor,  port4,           LIFT_L,        tmotorVex393, openLoop)
#pragma config(Motor,  port5,           INTK_L,        tmotorVex393, openLoop)
#pragma config(Motor,  port6,           INTK_R,        tmotorVex393, openLoop)
#pragma config(Motor,  port7,           LIFT_R,        tmotorVex393, openLoop)
#pragma config(Motor,  port8,           DRIVE_BR1,     tmotorVex393, openLoop)
#pragma config(Motor,  port9,           DRIVE_BR2,     tmotorVex393, openLoop)
#pragma config(Motor,  port10,          DRIVE_FR,      tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define   NORA_C
#define   PRACTICE // If not defined, then competition mode
//#define   FULL_DEBUG_STREAM
#include "N_Definitions.c"
#include "N_Declarations.c"
#include "N_Autos/N_Autos.c"
#include "N_Autos/N_Scripts.c"
#include "N_OtherFunctions.c"
#include "N_Initialize.c"
#include "N_State.c"
#include "N_Input.c"
#include "N_Operator.c"
#include "N_Autonomous.c"
#include "N_Output.c"
#include "N_LCD.c"
#include "N_Sound.c"

			//============= Nora.c =============//
			//									//
			//    Author: Joseph Dykstra		//
			//      Team: Techna PWN Robotics	//
			//   Created: 2013-05-15			//
			//									//
			//============== 3018 ==============//

task main()
	{
	initialize();
	while(1)
		{
		stateControl();
		input();
		processLCD();
		if (sysState.curr != DISABLED)
			{
			processAutonomous();
			if (sysState.curr == OPERATOR)
				processOperator();
			}
		processErrors();
		outputMotion();
		outputLCD();
		outputSound();
		setAllLasts();
		constantLoopTime();
		}
	}
