#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, in1,    POT_LIFT,       sensorPotentiometer)
#pragma config(Sensor, in2,    GYRO,           sensorGyro)
#pragma config(Sensor, in3,    POT_SELECTOR,   sensorPotentiometer)
#pragma config(Sensor, in4,    POT1,           sensorPotentiometer)
#pragma config(Sensor, in5,    POT2,           sensorPotentiometer)
#pragma config(Sensor, in6,    POT3,           sensorPotentiometer)
#pragma config(Sensor, in7,    POT4,           sensorPotentiometer)
#pragma config(Sensor, in8,    POT5,           sensorPotentiometer)
#pragma config(Sensor, dgtl1,  QUAD_LEFT,      sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  ULTRA_RIGHT,    sensorSONAR_cm)
#pragma config(Sensor, dgtl5,  ULTRA_LEFT,     sensorSONAR_cm)
#pragma config(Sensor, dgtl7,  QUAD_RIGHT,     sensorQuadEncoder)
#pragma config(Sensor, dgtl11, LOADER,         sensorDigitalOut)
#pragma config(Sensor, dgtl12, CATAPULT,       sensorDigitalOut)
#pragma config(Motor,  port1,           DRIVE_BL1,     tmotorVex393, openLoop)
#pragma config(Motor,  port2,           DRIVE_BR2,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           LIFT_R,        tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           DRIVE_FR,      tmotorVex393, openLoop)
#pragma config(Motor,  port5,           DRIVE_FL,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port6,           INTK_L,        tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port7,           LIFT_L2,       tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port8,           LIFT_L,        tmotorVex393, openLoop)
#pragma config(Motor,  port9,           DRIVE_BL2,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          DRIVE_BR1,     tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "1-DefinitionsAndDeclarations.c"
#include "2-OtherFunctions.c"
#include "Autos/1-AutoRedMiddle.c"
#include "Autos/2-AutoRedHanging.c"
#include "Autos/3-AutoBlueMiddle.c"
#include "Autos/4-AutoBlueHanging.c"
#include "Autos/5-AutoRedProgSkills.c"
#include "Autos/6-AutoTests.c"
#include "Autos/7-Scripts.c"
#include "3-State.c"
#include "4-Sensors.c"
#include "5-Operator.c"
#include "6-Autonomous.c"
#include "7-Output.c"
#include "8-LCD.c"
//#include "9-Sound.c"

//============= Nora.c =============//
//    Author: Joseph Dykstra        //
//      Team: Techna PWN Robotics   //
//   Created: 2013-05-15            //
//============== 3018 ==============//

task main()
	{
	initializeOutput();
	initializeLCD();
	initializeSensors();
	while (true)
		{
		inputProcessState();
		inputSensors();
		inputOperator();

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

		outputMotion();
		outputLCD();
		//outputSound();
		constantLoopTime();
		}
	}
