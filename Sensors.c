//Sensors.c

//Functions
void initializeSensors()
	{
	//--Sensors--//
	SensorValue[QUAD_LEFT] = 0;
	SensorValue[QUAD_RIGHT] = 0;
	SensorValue[GYRO] = 0;

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
	sysState.curr = DISABLED; //Usually changes to operator later
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
	setLastInt(&senLiftLPot);
	setLastInt(&senLiftRPot);
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
	senLeftQSE.curr =  SensorValue[QUAD_LEFT];
	senRightQSE.curr = SensorValue[QUAD_RIGHT];
	senLeftUS.curr =   SensorValue[ULTRA_LEFT];
	senRightUS.curr =  SensorValue[ULTRA_RIGHT];
	senSelectorPot =   SensorValue[POT_SELECTOR];
	senPwrExpVoltage = SensorValue[PWR_EXP_VLTG];
	senLiftLPot.curr = SensorValue[POT_LIFTL];
	senLiftRPot.curr = SensorValue[POT_LIFTR];

	//--Errors--//
	sysError = ERR_NONE;
	//if (senPwrExpVoltage<7200)	sysError = ERR_LOW_POW_EX; //power expander voltage is not x1000
	//if (timerRobotIdle>=60000)	sysError = ERR_ROBOT_IDLE;
	if (nAvgBatteryLevel<6400)		sysError = ERR_LOW_CORTEX;

	//--Sensor Irregularity Fixer--//
	/*slewLCInt(senGyro,3);		//Estimated .5
	slewLCInt(senLeftQSE,2);	//Estimated .33
	slewLCInt(senRightQSE,2);	//Estimated .33
	slewLCInt(senLeftUS,6);		//Estimated 2.5
	slewLCInt(senRightUS,6);	//Estimated 2.5*/
#else
	//--Emulated Sensors--//
	static int combinedTime=0;
	combinedTime += timerElapsedTime;
	if (combinedTime >= 100) //If 1/10th of a second or more has passed
		{
		senLeftQSE.curr  +=	emulateWheelQSE(combinedTime, outDrvL);
		senRightQSE.curr +=	emulateWheelQSE(combinedTime, outDrvR);
		senLiftLPot.curr +=	emulateLiftPot(combinedTime, outDrvL, 10);
		senLiftRPot.curr +=	emulateLiftPot(combinedTime, outDrvR, 10);
		senGyro.curr += emulateGyro(combinedTime, outDrvL, outDrvR);
		combinedTime = 0;
		}
#endif

	//--Autonomous Routine--//
	if (sysState.curr != AUTONOMOUS) //If not in autonomous
		autoRoutine.curr = potPosition(NO_AUTO_ROUTINES)+1; //Update autoRoutine variable
	}
