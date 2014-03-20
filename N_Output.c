
static short mtrTarget[10]={0,0,0,0,0,0,0,0,0,0};
static short mtrSlewed[10]={0,0,0,0,0,0,0,0,0,0};

/* This function sets all motor targets to 0.
*/
void zeroMotors(void)
	{
	outLift = 0;
	outDrvX = 0;
	outDrvY = 0;
	outDrvZ = 0;
	for (int j=0; j<10; j++)
		mtrTarget[j] = 0;
	}


/* This function uses the output variables to
set motors to their respective speeds.
*/
void outputMotion(void)
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

		int tLLift, tRLift, tLLiftAdd, tRLiftAdd, tTarget;
		tTarget = 0;
		if (abs(outLift) > 127)
			{
			tLLift = updatePIDController(PIDLiftL, outLift - senLiftLPot.curr);
			tRLift = updatePIDController(PIDLiftR, outLift - senLiftRPot.curr);
			capValue(REV,tLLift,FWD);
			capValue(REV,tRLift,FWD);
			tTarget = outLift;
			}
		else
			{
			tLLift = outLift;
			tRLift = outLift;
			}

		if (0) //if (btnNoPots.curr)
			{
			tLLiftAdd = senLiftRPot.curr-senLiftLPot.curr;
			tRLiftAdd = senLiftLPot.curr-senLiftRPot.curr;
			capValue(REV*2, tLLiftAdd, FWD*2);
			capValue(REV*2, tRLiftAdd, FWD*2);
			}
		else
			{
			tLLiftAdd = 0;
			tRLiftAdd = 0;
			}
		mtrTarget[LIFT_L] = tLLift + tLLiftAdd;
		mtrTarget[LIFT_R] = tRLift + tRLiftAdd;



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


void inputEmulator(void)
	{
#if (_TARGET!="Robot")
	senLeftQSE.curr  +=	emulateWheelQSE(mtrSlewed[DRIVE_BL1]);
	senRightQSE.curr +=	emulateWheelQSE(mtrSlewed[DRIVE_BR1]);
	senLiftLPot.curr +=	emulateLiftPot(mtrSlewed[LIFT_L], 15);
	senLiftRPot.curr +=	emulateLiftPot(mtrSlewed[LIFT_R], 15);
#endif
	}
