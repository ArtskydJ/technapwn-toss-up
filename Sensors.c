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

#if (_TARGET=="Robot")

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
	senLeftQSE.curr  +=	emulateWheelQSE(mtrSlewed[DRIVE_BL1]);
	senRightQSE.curr +=	emulateWheelQSE(mtrSlewed[DRIVE_BR1]);
	senLiftLPot.curr +=	emulateLiftPot(mtrSlewed[LIFT_L], 15);
	senLiftRPot.curr +=	emulateLiftPot(mtrSlewed[LIFT_R], 15);
#endif

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
