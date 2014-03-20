//Functions
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

	//--Timers--//
	int tTimerMaster = time1(T3);
	ClearTimer(T3);
	if (autoClockRunning && sysState.curr==AUTONOMOUS)
		timerAuto +=		tTimerMaster;
	timerLCDScroll +=		tTimerMaster;
	timerLCDBacklight +=	tTimerMaster;
	timerElapsedTime =		tTimerMaster; //Yes, it is supposed to be =, not +=

	if (timerLCDScroll>62000)      timerLCDScroll =    62000; //Prevent wrapping
	if (timerLCDBacklight>62000)   timerLCDBacklight = 62000; //Prevent wrapping
	if (timerRobotIdle>62000)      timerRobotIdle =    62000; //Prevent wrapping
	//if (joystickIsMoved(true) && LCD_TIMEOUT) timerLCDBacklight = 0; //!!!!!!!!!!!!!!!!!!!!!!!!!1backlight mode!!!!!!!!!!!!!!!!!!!!!!!!

#ifdef PHYSICAL_ROBOT_TARGET
	timerRobotIdle +=		tTimerMaster;
	if (joystickIsMoved(true) || nLCDButtons>0)	timerRobotIdle = 0;

	//--Robot Sensors--//
	static int addToGyro=0;
	senGyro.curr = SensorValue[GYRO] + addToGyro;
	if ((senGyro.last%3600)>3300 && (senGyro.curr%3600)<300)
		{
		addToGyro += 3600;
		senGyro.curr += 3600;
		}
	if ((senGyro.last%3600)<300 && (senGyro.curr%3600)>3300)
		{
		addToGyro -= 3600;
		senGyro.curr -= 3600;
		}
	senLeftQSE.curr =  SensorValue[QUAD_LEFT];
	senRightQSE.curr = SensorValue[QUAD_RIGHT];
	senLeftUS.curr =   SensorValue[ULTRA_LEFT];
	senRightUS.curr =  SensorValue[ULTRA_RIGHT];
	senSelectorPot =   SensorValue[POT_SELECTOR];
	senPwrExpVoltage = SensorValue[PWR_EXP_VLTG];
	senLiftLPot.curr = SensorValue[POT_LIFTL];
	senLiftRPot.curr = SensorValue[POT_LIFTR];

	sysError = ERR_NONE;
	//if (senPwrExpVoltage<7200)	sysError = ERR_LOW_POW_EX; //power expander voltage is not x1000
	//if (timerRobotIdle>=60000)	sysError = ERR_ROBOT_IDLE;
	if (nAvgBatteryLevel<1000)		sysError = ERR_LOW_CORTEX;

	//--Sensor Irregularity Fixer--//
	slewLCInt(senGyro,3);		//Estimated .5
	slewLCInt(senLeftQSE,2);	//Estimated .33
	slewLCInt(senRightQSE,2);	//Estimated .33
	slewLCInt(senLeftUS,6);		//Estimated 2.5
	slewLCInt(senRightUS,6);	//Estimated 2.5
#else
	//--Emulated Sensors--//
	emulateSensors();
#endif

	//--Autonomous Routine--//
	if (sysState.curr != AUTONOMOUS) //If not in autonomous
		autoRoutine.curr = potPosition(NO_AUTO_ROUTINES)+1; //Update autoRoutine variable
	}


/*This function returns a reversed value for pots
that were installed so that the number goes up
when the arm goes down, etc.
*/
static int potReverse(int INpot)
	{
	return (4095-INpot);
	}
