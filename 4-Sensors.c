//Sensors.c

//Functions
//This function is run at the beginning of the program only. It is for resetting
//the robot the it's starting state. All sensors and timers are reset, and a
//hint is printed into the debug stream.
void initializeSensors(void)
	{
	//--Sensors--//
	SensorValue[QUAD_LEFT] = 0;
	SensorValue[QUAD_RIGHT] = 0;
	SensorValue[GYRO] = 0;
	
	SensorValue[TRANNY] = 0;
	SensorValue[LOADER] = 0;
	SensorValue[BRAKE] = 0;
	SensorValue[CATAPULT] = 0;
	outTranny = false;
	outLoader = false;
	outBrake = false;
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
	setLastInt(&senCenterUS);
	setLastInt(&senLineFollow);
	setLastInt(&autoRoutine);
	setLastInt(&senLiftPot);
	setLastBool(&btnScreenLeft);
	setLastBool(&btnScreenCenter);
	setLastBool(&btnScreenRight);

	//--Timers--//
	int tTimerMaster = time1(T3);
	ClearTimer(T3);
	if (autoClockRunning && sysState.curr==AUTONOMOUS)
		{
		timerTemp +=				tTimerMaster;
		if (timerTemp>=3000) //every 3 seconds...
			{
			timerAutoTimeAdd += timerTemp/10;
			timerTemp = 0;
			}
		timerAuto =			timerAutoTimeAdd + (timerTemp/10);
		}
	timerLCDScroll +=		tTimerMaster;
	timerLCDBacklight +=	tTimerMaster;
	if (sysDriverSkillsRunning)
		timerDriverSkills +=tTimerMaster;
	else
		timerDriverSkills = 0;
	timerElapsedTime =		tTimerMaster; //Yes, '='

	//--LCD Buttons--//
	btnScreenLeft.curr =	(nLCDButtons & 1) > 0;
	btnScreenCenter.curr =	(nLCDButtons & 2) > 0;
	btnScreenRight.curr =	(nLCDButtons & 4) > 0;

	//--Timers--//
	if (timerLCDScroll > 62000)    timerLCDScroll =    62000; //Prevent wrapping
	if (timerLCDBacklight > 62000) timerLCDBacklight = 62000; //Prevent wrapping
	if (timerDriverSkills > 62000) timerLCDBacklight = 62000; //Prevent wrapping
	if (timerRobotIdle > 62000)    timerRobotIdle =    62000; //Prevent wrapping
	if ((joystickIsMoved(true) || screenButtonIsPressed())
		&& sysLCDBacklight==(T_BACKLIGHT)LCD_TIMEOUT)
	                               timerLCDBacklight = 0;     //Reset

#ifdef PHYSICAL_ROBOT_TARGET
	timerRobotIdle +=		tTimerMaster;
	if (joystickIsMoved(true) || screenButtonIsPressed())	timerRobotIdle = 0;

	//--Robot Sensors--//
	senGyro.curr =        SensorValue[GYRO];
	senLeftQSE.curr =     SensorValue[QUAD_LEFT];
	senRightQSE.curr =   -SensorValue[QUAD_RIGHT];
	if (SensorValue[ULTRA_LEFT]>US_DEAD_ZONE)
		senLeftUS.curr =  SensorValue[ULTRA_LEFT];
	if (SensorValue[ULTRA_RIGHT]>US_DEAD_ZONE)
		senRightUS.curr = SensorValue[ULTRA_RIGHT];
	/*if (SensorValue[ULTRA_CENTER]>US_DEAD_ZONE)
		senRightUS.curr =  SensorValue[ULTRA_RIGHT];*/
	senLineFollow.curr =  SensorValue[LINE_FOLLOWER];
	senSelectorPot =      SensorValue[POT_SELECTOR];
	//senPwrExpVoltage = SensorValue[PWR_EXP_VLTG];
	senLiftPot.curr =  (SensorValue[POT_LIFT]<650)? senLiftPot.curr : SensorValue[POT_LIFT];

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
		senLiftPot.curr +=  emulateLiftPot(combinedTime, outLift, 5);
		senGyro.curr +=     emulateGyro(combinedTime, outDrvL, outDrvR);
		combinedTime = 0;
		}
	senLineFollow = LINE_LOW;
#endif

	//--Autonomous Routine--//
	if (sysState.curr != AUTONOMOUS) //If not in autonomous
		autoRoutine.curr = potPosition(NO_AUTO_ROUTINES)+1; //Update autoRoutine variable
	}

bool screenButtonIsPressed(void)
	{
	return (btnScreenLeft.curr || btnScreenCenter.curr || btnScreenRight.curr);
	}
