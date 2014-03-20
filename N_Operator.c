void processOperator()
	{
	if (sysMotorTest)
		sysMotorTest = !joystickIsMoved(0);
	else
		{
		//--Settings--//
		if (btnInvertDriveModifier)
			{
			if		(btnInvertDriveFwd) sysInvertDriveOffset = DRV_FWD;
			else if	(btnInvertDriveRev) sysInvertDriveOffset = DRV_REV;
			else if	(btnInvertDriveLft) sysInvertDriveOffset = DRV_LFT;
			else if	(btnInvertDriveRht) sysInvertDriveOffset = DRV_RHT;
			}
		if (btnSubroutineModifier)
			{						//Negative values are for driver autos
			if		(btnSubroutine1) {/*sysVirtualAuto=true;*/ autoRoutine.curr = -1;}
			else if	(btnSubroutine2) {/*sysVirtualAuto=true;*/ autoRoutine.curr = -2;}
			else if	(btnSubroutine3) {/*sysVirtualAuto=true;*/ autoRoutine.curr = -3;}
			else if	(btnSubroutine4) {/*sysVirtualAuto=true;*/ autoRoutine.curr = -4;}
			}
		sysInvertDrive = DRV_FWD; //((senAbsGyro+450)%900 + sysInvertDriveOffset) % 4;

		//--Controls--//
		switch(sysInvertDrive)
			{
			case DRV_RHT: //Rotated 0°   (Robot faces driver's right)
				outDrvX = stkDrvY;
				outDrvY = stkDrvX; break;
			case DRV_FWD: //Rotated 90°  (Robot faces away from driver)
				outDrvX = stkDrvX;
				outDrvY = stkDrvY; break;
			case DRV_LFT: //Rotated 180° (Robot faces driver's left)
				outDrvX = -stkDrvY;
				outDrvY = -stkDrvX; break;
			case DRV_REV: //Rotated 270° (Robot faces driver)
				outDrvX = -stkDrvX;
				outDrvY = -stkDrvY; break;
			}
		outDrvZ = stkDrvZ;
		//--Drive--//
		if (joystickIsMoved(0))
			if (autoScriptTakeover[DRIVE] == STO_TAKEOVER)
				autoRoutine.curr = 0; //Disable script

		//--Lift--//
		if (btnLiftUp.curr || btnLiftDown.curr)
			{
			if (autoScriptTakeover[LIFT] == STO_TAKEOVER)
				autoRoutine.curr = 0;
			}
		if (btnLiftUp.curr)				//If Lift Up Pressed
			outLift = REV;					//Lift Motors Reverse
		else if (btnLiftDown.curr)		//If Lift Down Pressed
			outLift = FWD;					//Lift Motors Forward
		else if (abs(outLift) <= FWD)	//If a speed setting and no lift buttons pressed
			outLift = 0;					//Lift Motors Off


		//--Intake--//
		if (btnIntkUp.curr || btnIntkDown.curr)
			{
			if (autoScriptTakeover[INTK] == STO_TAKEOVER)
				autoRoutine.curr = 0;
			}

		if (btnIntkUp.curr)				//If Intake Out Pressed
			outIntk = FWD;					//Intake Motors Forward
		else if (btnIntkDown.curr)		//If Intake In Pressed
			outIntk = REV;					//Intake Motors Reverse
		else							//If no Intake buttons Pressed
			outIntk = 0;					//Intake Motors Off


		//Remember to use btnDisablePots
		}
	}
