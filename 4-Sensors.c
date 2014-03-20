//Sensors.c

//Functions
//This function is run at the beginning of the program only. It is for resetting
//the robot the it's starting state. All sensors and timers are reset, and a
//hint is printed into the debug stream.
void initializeSensors()
	{
	//--Sensors--//
	SensorValue[QUAD_LEFT] = 0;
	//SensorValue[QUAD_RIGHT] = 0;
	SensorValue[GYRO] = 0;
	SensorValue[CATAPULT] = 0;
	outCatapult = false;

	//--Timers--//
	ClearTimer(T1);
	ClearTimer(T2);
	ClearTimer(T3);
	ClearTimer(T4);

	//--Other--//
	writeDebugStreamLine("\n================");
#ifdef PHYSICAL_ROBOT_TARGET
	writeDebugStreamLine("-Physical Robot-");
#else
	writeDebugStreamLine("----Emulator----");
#endif
	sysState.curr = DISABLED; //Other variables should change this to operator (see State.c)
	autoRoutine.curr = 0;
	}


void inputSensors(void)
	{
	//--Last Values--//
	setLastInt(&senGyro);
	setLastInt(&senLeftQSE);
	setLastInt(&senRightQSE);
	setLastInt(&senLeftUS);
	setLastInt(&senRightUS);
	setLastInt(&autoRoutine);
	setLastInt(&senLiftPot);
	setLastBool(&btnScreenLeft);
	setLastBool(&btnScreenCenter);
	setLastBool(&btnScreenRight);

	//--Timers--//
	int tTimerMaster = time1(T3);
	ClearTimer(T3);
	if (autoClockRunning && sysState.curr==AUTONOMOUS)
		timerAuto +=		tTimerMaster;
	timerLCDScroll +=		tTimerMaster;
	timerLCDBacklight +=	tTimerMaster;
	timerElapsedTime =		tTimerMaster; //Yes, it is supposed to be =, not +=

	//--LCD Buttons--//
	btnScreenLeft.curr =	(nLCDButtons & 1)>0;
	btnScreenCenter.curr =	(nLCDButtons & 2)>0;
	btnScreenRight.curr =	(nLCDButtons & 4)>0;

	//--Timers--//
	if (timerLCDScroll>62000)      timerLCDScroll =    62000; //Prevent wrapping
	if (timerLCDBacklight>62000)   timerLCDBacklight = 62000; //Prevent wrapping
	if (timerRobotIdle>62000)      timerRobotIdle =    62000; //Prevent wrapping
	if ((joystickIsMoved(true) || nLCDButtons != 0)
		&& sysLCDBacklight==(T_BACKLIGHT)LCD_TIMEOUT)
                                   timerLCDBacklight = 0;     //Reset

#ifdef PHYSICAL_ROBOT_TARGET
	timerRobotIdle +=		tTimerMaster;
	if (joystickIsMoved(true) || nLCDButtons>0)	timerRobotIdle = 0;

	//--Robot Sensors--//
	senGyro.curr =     SensorValue[GYRO];
	senLeftQSE.curr =  -SensorValue[QUAD_LEFT]; //reversed
	//senRightQSE.curr = SensorValue[QUAD_RIGHT];
	if (SensorValue[ULTRA_LEFT]>US_DEAD_ZONE)
		senLeftUS.curr =   SensorValue[ULTRA_LEFT];
	if (SensorValue[ULTRA_RIGHT]>US_DEAD_ZONE)
		senRightUS.curr =  SensorValue[ULTRA_RIGHT];
	senSelectorPot =   SensorValue[POT_SELECTOR];
	//senPwrExpVoltage = SensorValue[PWR_EXP_VLTG];
	senLiftPot.curr =  SensorValue[POT_LIFT];

	//--Errors--//
	sysError = ERR_NONE;
	//if (senPwrExpVoltage<7200)	sysError = ERR_LOW_POW_EX; //power expander voltage is not x1000
	//if (timerRobotIdle>=60000)	sysError = ERR_ROBOT_IDLE;
	if (nAvgBatteryLevel<6400)		sysError = ERR_LOW_CORTEX;

#else
	//--Emulated Sensors--//
	static int combinedTime=0;
	combinedTime += timerElapsedTime;
	if (combinedTime >= 100) //If 1/10th of a second or more has passed
		{
		senLeftQSE.curr +=  emulateWheelQSE(combinedTime, outDrvL);
		senRightQSE.curr += emulateWheelQSE(combinedTime, outDrvR);
		senLiftPot.curr +=  emulateLiftPot(combinedTime, outLift, 10);
		senGyro.curr +=     emulateGyro(combinedTime, outDrvL, outDrvR);
		combinedTime = 0;
		}
#endif

	//--Autonomous Routine--//
	if (sysState.curr != AUTONOMOUS) //If not in autonomous
		autoRoutine.curr = potPosition(NO_AUTO_ROUTINES)+1; //Update autoRoutine variable
	}
