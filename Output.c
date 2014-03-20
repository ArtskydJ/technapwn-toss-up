//Constants
static const int DISABLE_RANGE = 50;

//Variables
static int mtrTarget[10]={0,0,0,0,0,0,0,0,0,0};
static int mtrSlewed[10]={0,0,0,0,0,0,0,0,0,0};
static int slewConstants[3][10];

//Functions
void initializeOutput()
	{
	for (int j=0; j<10; j++)
		slewConstants[DISABLED][j] = 127;					//DISABLED

	slewConstants[OPERATOR][DRIVE_FL]  = OPER_DRV_SLEW;		//OPERATOR
	slewConstants[OPERATOR][DRIVE_BL1] = OPER_DRV_SLEW;
	slewConstants[OPERATOR][DRIVE_BL2] = OPER_DRV_SLEW;
	slewConstants[OPERATOR][DRIVE_FR]  = OPER_DRV_SLEW;
	slewConstants[OPERATOR][DRIVE_BR1] = OPER_DRV_SLEW;
	slewConstants[OPERATOR][DRIVE_BR2] = OPER_DRV_SLEW;
	slewConstants[OPERATOR][LIFT_L]    = OPER_LIFT_SLEW;
	slewConstants[OPERATOR][LIFT_R]    = OPER_LIFT_SLEW;
	slewConstants[OPERATOR][INTK_L]    = OPER_INTK_SLEW;
	//slewConstants[OPERATOR][INTK_R]    = OPER_INTK_SLEW;

	slewConstants[AUTONOMOUS][DRIVE_FL]  = AUTO_DRV_SLEW;		//AUTONOMOUS
	slewConstants[AUTONOMOUS][DRIVE_BL1] = AUTO_DRV_SLEW;
	slewConstants[AUTONOMOUS][DRIVE_BL2] = AUTO_DRV_SLEW;
	slewConstants[AUTONOMOUS][DRIVE_FR]  = AUTO_DRV_SLEW;
	slewConstants[AUTONOMOUS][DRIVE_BR1] = AUTO_DRV_SLEW;
	slewConstants[AUTONOMOUS][DRIVE_BR2] = AUTO_DRV_SLEW;
	slewConstants[AUTONOMOUS][LIFT_L]    = AUTO_LIFT_SLEW;
	slewConstants[AUTONOMOUS][LIFT_R]    = AUTO_LIFT_SLEW;
	slewConstants[AUTONOMOUS][INTK_L]    = AUTO_INTK_SLEW;
	//slewConstants[AUTONOMOUS][INTK_R]    = AUTO_INTK_SLEW;
	zeroMotors();
	}

/* This function sets all motor targets to 0.
*/
void zeroMotors(void)
	{
	outDrvFwd = 0;
	outDrvTrn = 0;
	outDrvStf = 0;
	outLift = 0;
	outIntk = 0;
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
		//if (sysState.curr == OPERATOR)
		//	{					 // Y=FWD  Z=TURN  X=STRAFE
			mtrTarget[DRIVE_FL]  = outDrvFwd + outDrvTrn + outDrvStf;
			mtrTarget[DRIVE_BL1] = outDrvFwd + outDrvTrn - outDrvStf;
			mtrTarget[DRIVE_BL2] = outDrvFwd + outDrvTrn - outDrvStf;
			mtrTarget[DRIVE_FR]  = outDrvFwd - outDrvTrn - outDrvStf;
			mtrTarget[DRIVE_BR1] = outDrvFwd - outDrvTrn + outDrvStf;
			mtrTarget[DRIVE_BR2] = outDrvFwd - outDrvTrn + outDrvStf;
		/*	}
		else if (sysState.curr == AUTONOMOUS)
			{			 // L=LEFT R=RIGHT S=STRAFE
			mtrTarget[DRIVE_FL]  = outDrvL + outDrvS;
			mtrTarget[DRIVE_BL1] = outDrvL - outDrvS;
			mtrTarget[DRIVE_BL2] = outDrvL - outDrvS;
			mtrTarget[DRIVE_FR]  = outDrvR - outDrvS;
			mtrTarget[DRIVE_BR1] = outDrvR + outDrvS;
			mtrTarget[DRIVE_BR2] = outDrvR + outDrvS;
			}*/

		int tLLift, tRLift, tLLiftAdd, tRLiftAdd, tTarget;
		bool tDisableLift=false;
		tTarget = 0;
		if (abs(outLift) > 127)
			{
			updatePIDController(PIDLift, outLift*2 - (senLiftLPot.curr+senLiftRPot.curr));
			tLLift = capIntValue(REV, PIDLift.output, FWD);
			tRLift = capIntValue(REV, PIDLift.output, FWD);
			tTarget = outLift;

			if (senLiftLPot.curr < outLift + DISABLE_RANGE &&
			    senLiftLPot.curr > outLift - DISABLE_RANGE &&
			    senLiftRPot.curr < outLift + DISABLE_RANGE &&
			    senLiftRPot.curr > outLift - DISABLE_RANGE)
				tDisableLift=true;
			}
		else
			{
			tLLift = outLift;
			tRLift = outLift;
			}

#ifdef LIFT_SYNC
		if (!btnDisablePots)
#else
		if (0)
#endif
			{
			tLLiftAdd = capIntValue(REV*2, (senLiftRPot.curr-senLiftLPot.curr)*sysLiftP, FWD*2);
			tRLiftAdd = capIntValue(REV*2, (senLiftLPot.curr-senLiftRPot.curr)*sysLiftP, FWD*2);
			}
		else
			{
			tLLiftAdd = 0;
			tRLiftAdd = 0;
			}

		if (tDisableLift)
			{
			mtrTarget[LIFT_L]=0;
			mtrTarget[LIFT_R]=0;
			}
		else
			{
			mtrTarget[LIFT_L] = tLLift + tLLiftAdd;
			mtrTarget[LIFT_R] = tRLift + tRLiftAdd;
			}
		mtrTarget[LIFT_L] = mtrTarget[LIFT_L];
		mtrTarget[LIFT_R] = mtrTarget[LIFT_R];


		mtrTarget[INTK_L] = outIntk;
		//mtrTarget[INTK_R] = outIntk;
		if (sysMotorsEnabled)
			{
			SensorValue[BRAKE] = outBrake;
			}
		}

	for (int j=0; j<10; j++)
		{
		mtrSlewed[j] += slew(mtrTarget[j], mtrSlewed[j], slewConstants[sysState.curr][j]); //SLEW CONTROLLERS
		mtrSlewed[j] = capIntValue(-127, mtrSlewed[j], 127); //CAP ALL MOTORS
		motor[j] = mtrSlewed[j]*sysMotorsEnabled; //ASSIGN MOTORS
		}
	}


/* This function gets the target motor value, the
previously assigned motor value, and the slew.
*/
int slew(int INtargetValue, int INlastValue, int INslew)
	{
	return capIntValue(-INslew, INtargetValue-INlastValue, INslew);
	}


/* This function returns the delta for the
emulated quadrature shaft encoder with the given
speed of a wheel.
*/
int emulateWheelQSE(int INspeed)
	{
	return ( (float) INspeed * timerEmulateSpeed / (127 * 2) );
	}


/* This function returns the delta for the
emulated potentiometer position with the given
speed and gearing of a lift.
 INgearing needs a 5 if the gearing is 1:5, a 7
if the gearing is 1:7, etc.
*/
int emulateLiftPot(int INspeed, int INgearing)
	{
	return ( (float) INspeed * timerEmulateSpeed / (25*INgearing) );
	}
