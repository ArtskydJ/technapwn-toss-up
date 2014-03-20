void outputMotion()
	{
	if (sysState.curr == DISABLED)
		{
		zeroMotors();
		}
	else if (sysMotorTest)
		{
		for (int j=0; j<10; j++)
			mtrTarget[j] = (mtrTestEnabled[j]*stkMtrTest);
		}
	else
		{
		if (sysState.curr == OPERATOR)
			{					 // Y=FWD  Z=TURN  X=STRAFE
			mtrTarget[DRIVE_FL]  = outDrvY-outDrvZ+outDrvX;
			mtrTarget[DRIVE_BL1] = outDrvY-outDrvZ-outDrvX;
			mtrTarget[DRIVE_BL2] = outDrvY-outDrvZ-outDrvX;
			mtrTarget[DRIVE_FR]  = outDrvY+outDrvZ-outDrvX;
			mtrTarget[DRIVE_BR1] = outDrvY+outDrvZ+outDrvX;
			mtrTarget[DRIVE_BR2] = outDrvY+outDrvZ+outDrvX;
			}
		else if (sysState.curr == AUTONOMOUS)
			{			 // L=LEFT R=RIGHT S=STRAFE
			mtrTarget[DRIVE_FL]  = outDrvL+outDrvS;
			mtrTarget[DRIVE_BL1] = outDrvL-outDrvS;
			mtrTarget[DRIVE_BL2] = outDrvL-outDrvS;
			mtrTarget[DRIVE_FR]  = outDrvR-outDrvS;
			mtrTarget[DRIVE_BR1] = outDrvR+outDrvS;
			mtrTarget[DRIVE_BR2] = outDrvR+outDrvS;
			}
			
		if (abs(outLift) > 127) outLift = updatePIDController(PIDLift, outLift - senLiftPot); //Lift
		mtrTarget[LIFT_L] = outLift;
		mtrTarget[LIFT_R] = outLift;
		
		if (abs(outIntk) > 127) outIntk = updatePIDController(PIDIntk, outIntk - senIntkPot); //Intake
		mtrTarget[LIFT_L] = outIntk;
		mtrTarget[LIFT_R] = outIntk;
		}

	for (int j=0; j<10; j++)
		{
		mtrSlewed[j] += slew(mtrTarget[j]/(1+btnHalfSpeed), mtrSlewed[j], slewConstants[sysState.curr][j]); //SLEW CONTROLLERS
		capValue(-127, mtrSlewed[j], 127); //CAP ALL MOTORS
		motor[j] = mtrSlewed[j]*sysMotorsEnabled; //ASSIGN MOTORS
		}
	}
