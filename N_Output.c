void outputMotion()
	{
	if (sysState.curr == DISABLED)
		zeroMotors();
	else if (sysMotorTest)
		for (int j=0; j<10; j++)
			mtrTarget[j] = (mtrTestEnabled[j]*stkMtrTest);
	else
		{
		if (sysState.curr == OPERATOR)
			{					 // Y=FWD  Z=TURN  X=STRAFE
			mtrTarget[DRIVE_FL]  = outDrvY + outDrvZ + outDrvX;
			mtrTarget[DRIVE_BL1] = outDrvY + outDrvZ - outDrvX;
			mtrTarget[DRIVE_BL2] = outDrvY + outDrvZ - outDrvX;
			mtrTarget[DRIVE_FR]  = outDrvY - outDrvZ - outDrvX;
			mtrTarget[DRIVE_BR1] = outDrvY - outDrvZ + outDrvX;
			mtrTarget[DRIVE_BR2] = outDrvY - outDrvZ + outDrvX;
			}
		else if (sysState.curr == AUTONOMOUS)
			{			 // L=LEFT R=RIGHT S=STRAFE
			mtrTarget[DRIVE_FL]  = outDrvL + outDrvS;
			mtrTarget[DRIVE_BL1] = outDrvL - outDrvS;
			mtrTarget[DRIVE_BL2] = outDrvL - outDrvS;
			mtrTarget[DRIVE_FR]  = outDrvR - outDrvS;
			mtrTarget[DRIVE_BR1] = outDrvR + outDrvS;
			mtrTarget[DRIVE_BR2] = outDrvR + outDrvS;
			}

		float tLLift, tRLift;			// LIFT SYNC...
		int tLLiftAdd, tRLiftAdd, tTarget=0;
		if (abs(outLift) > 127)
			{
			tLLift = updatePIDController(PIDLiftL, outLift - senLiftLPot);
			tRLift = updatePIDController(PIDLiftR, outLift - senLiftRPot);
			capValue(REV,tLLift,FWD);
			capValue(REV,tRLift,FWD);
			tTarget = outLift;
			}
		else if (outLift != 0)
			{
			tLLift = outLift;
			tRLift = outLift;
			}

		tLLiftAdd = senLiftRPot-senLiftLPot;
		tRLiftAdd = senLiftLPot-senLiftRPot;
		capValue(REV, tLLiftAdd, FWD);
		capValue(REV, tRLiftAdd, FWD);
		mtrTarget[LIFT_L] = tLLift+tLLiftAdd;
		mtrTarget[LIFT_R] = tRLift+tRLiftAdd;

		
		mtrTarget[INTK_L] = outIntk;
		//mtrTarget[INTK_R] = outIntk;
		}

	for (int j=0; j<10; j++)
		{
		mtrSlewed[j] += slew(mtrTarget[j], mtrSlewed[j], slewConstants[sysState.curr][j]); //SLEW CONTROLLERS
		capValue(-127, mtrSlewed[j], 127); //CAP ALL MOTORS
		motor[j] = mtrSlewed[j]*sysMotorsEnabled; //ASSIGN MOTORS
		}
	}
