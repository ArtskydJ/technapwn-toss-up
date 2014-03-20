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
			if		(btnSubroutine1) {sysVirtualAuto=true; autoRoutine.curr = -1;}
			else if	(btnSubroutine2) {sysVirtualAuto=true; autoRoutine.curr = -2;}
			else if	(btnSubroutine3) {sysVirtualAuto=true; autoRoutine.curr = -3;}
			else if	(btnSubroutine4) {sysVirtualAuto=true; autoRoutine.curr = -4;}
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
			if (autoScriptTakeover[DRIVE] == ST_TAKEOVER)
				autoRoutine.curr = 0; //Disable script
			//else

		//--Lift--//
		if (btnLiftUp.curr || btnLiftDown.curr)
			if (autoScriptTakeover[LIFT] == ST_TAKEOVER)
				autoRoutine.curr = 0;
			//else

		//--Intake--//
		if (btnIntkUp.curr || btnIntkDown.curr)
			if (autoScriptTakeover[INTK] == ST_TAKEOVER)
				autoRoutine.curr = 0;
			//else


		//Remember to use btnDisablePots
		}
	}
