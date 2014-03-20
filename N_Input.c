void input()
	{
#if (_TARGET=="Robot")
	//--Joystick Sticks--//
	stkDrvX =			joystickFilter(vexRT[Ch4]);
	stkDrvY =			joystickFilter(vexRT[Ch3]);
	stkDrvZ =			joystickFilter(vexRT[Ch1]);
	stkMtrTest =					  (vexRT[Ch2]);

	//--Joystick Buttons--//
	btnLiftUp.curr =			(bool)vexRT[Btn5U];
	btnLiftDown.curr =			(bool)vexRT[Btn5D];
	btnIntkUp.curr =			(bool)vexRT[Btn6U];
	btnIntkDown.curr =			(bool)vexRT[Btn6D];
	//**Modifiers - 7 UDLR
	btnDisablePots = 			(bool)vexRT[Btn7D];
	btnSubroutineModifier =		(bool)vexRT[Btn7L];
	btnInvertDriveModifier =	(bool)vexRT[Btn7R];
	//**Normal - 8 UDLR
	btnInvertDriveFwd =			(bool)vexRT[Btn8U];
	btnInvertDriveRev =			(bool)vexRT[Btn8D];
	btnInvertDriveLft =			(bool)vexRT[Btn8L];
	btnInvertDriveRht =			(bool)vexRT[Btn8R];
	btnSubroutine1 =			(bool)vexRT[Btn8U];
	btnSubroutine2 =			(bool)vexRT[Btn8D];
	btnSubroutine3 =			(bool)vexRT[Btn8L];
	btnSubroutine4 =			(bool)vexRT[Btn8R];

	//--Robot Sensors--//
	senGyro.curr =				SensorValue[GYRO];
	senLeftQSE.curr =			SensorValue[QUAD_LEFT];
	senRightQSE.curr =			SensorValue[QUAD_RIGHT];
	senLeftUS.curr =			SensorValue[ULTRA_LEFT];
	senRightUS.curr =			SensorValue[ULTRA_RIGHT];
	senSelectorPot =			SensorValue[POT_SELECTOR];
	senPwrExpVoltage =			SensorValue[PWR_EXP_VLTG];
	senLeftLiftPot.curr =		SensorValue[POT_LIFTL];
	senRightLiftPot.curr =		SensorValue[POT_LIFTR]+L_2_OFF; //Offset
	
	//--Sensor Irregularity Fixer--//
	fixIrregularity(senGyro,3);		//Estimated .5
	fixIrregularity(senLeftQSE,2);	//Estimated .33
	fixIrregularity(senRightQSE,2);	//Estimated .33
	fixIrregularity(senLeftUS,6);	//Estimated 2.5
	fixIrregularity(senRightUS,6);	//Estimated 2.5

#else //EMULATOR
	senLeftQSE.curr  +=	emulateWheelQSE(mtrSlewed[DRIVE_BL1]); //EMULATOR ONLY
	senRightQSE.curr +=	emulateWheelQSE(mtrSlewed[DRIVE_BR1]);
	senLeftLiftPot +=	emulateLiftPot(mtrSlewed[L_LIFT], 15);
	senRightLiftPot +=	emulateLiftPot(mtrSlewed[R_LIFT], 15); //EMULATOR ONLY
#endif

	//--Robot Buttons--//
	btnScreenLeft.curr =	(nLCDButtons & 1);
	btnScreenCenter.curr =	(nLCDButtons & 2);
	btnScreenRight.curr =	(nLCDButtons & 4);
	timerMaster = time1(T3);
	ClearTimer(T3);
	if (autoClockRunning && sysState.curr==AUTONOMOUS)
		timerAuto +=		timerMaster;
	timerLCDScroll +=		timerMaster;
	timerLCDBacklight +=	timerMaster;

#if (_TARGET=="Robot")
	timerRobotIdle +=		timerMaster;
	if (joystickIsMoved(true) || nLCDButtons>0)	timerRobotIdle = 0;
	if (timerRobotIdle>60000)					timerRobotIdle = 60000; //Prevent wrapping
#endif

	StringFormat(batteryLevel[0], "Main:%1.2f | Powe", (float)nAvgBatteryLevel/1000);
	StringFormat(batteryLevel[1], "r Expander:%1.2f ", (float)senPwrExpVoltage/70);		//70 45.6 280 or 182.4
	StringFormat(batteryLevel[2], "| Backup:%1.2f | ", (float)BackupBatteryLevel/1000);
	if (senGyro.last>3000 && senGyro.curr<600)	senAddToAbsGyro += 3600;
	if (senGyro.last<600 && senGyro.curr>3000)	senAddToAbsGyro -= 3600;
	senAbsGyro = senAddToAbsGyro + senGyro.curr;

	if (sysState.curr != AUTONOMOUS)
		autoRoutine.curr = potPosition(NO_AUTO_ROUTINES)+1;
	}
