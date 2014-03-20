//Output.c

//Constants
static const int LIFT_DISABLE_RANGE = 50;

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
	slewConstants[OPERATOR][LIFT_L2]   = OPER_LIFT_SLEW;
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
	outDrvL = 0;
	outDrvR = 0;
	outDrvS = 0;
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
	if (sysState.curr == DISABLED)     //Disabled
		{
		zeroMotors();
		}
	else if (sysMotorTest)             //Enabled, Motor mode
		{
		for (int j=0; j<10; j++)
			mtrTarget[j] = (mtrTestEnabled[j]*stkMtrTest);
		}
	else                               //Enabled, Normal mode
		{
		mtrTarget[DRIVE_FL] =  outDrvL + outDrvS;
		mtrTarget[DRIVE_BL1] = outDrvL - outDrvS;
		mtrTarget[DRIVE_BL2] = outDrvL - outDrvS;
		mtrTarget[DRIVE_FR] =  outDrvR - outDrvS;
		mtrTarget[DRIVE_BR1] = outDrvR + outDrvS;
		mtrTarget[DRIVE_BR2] = outDrvR + outDrvS;

		if (outLift >= L_PRE_START && outLift <= L_PRE_END)     //preset position
			{
			outLift = L_PRESETS[outLift-L_PRE_START];
			}

		if (abs(outLift) > 127)                                 //position
			{
			if (senLiftLPot.curr < outLift + LIFT_DISABLE_RANGE &&
			    senLiftLPot.curr > outLift - LIFT_DISABLE_RANGE &&
			    senLiftRPot.curr < outLift + LIFT_DISABLE_RANGE &&
			    senLiftRPot.curr > outLift - LIFT_DISABLE_RANGE)  //if close to target, neutralize lift
					outLift = 0;
			else
				outLift = outLift*2 - (senLiftLPot.curr+senLiftRPot.curr); //otherwise, target potentiometers
			}

		mtrTarget[LIFT_L] =  outLift;
		mtrTarget[LIFT_L2] = outLift;
		mtrTarget[LIFT_R] =  outLift;

		mtrTarget[INTK_L] = outIntk;

		if (sysMotorsEnabled) //Pneumatics
			{
			SensorValue[INTK_EXTEND] = outIntkExtend;
			}
		}

	for (int j=0; j<10; j++)
		{
		mtrSlewed[j] += slew(mtrTarget[j], mtrSlewed[j], slewConstants[sysState.curr][j]); //SLEW CONTROLLERS
		mtrSlewed[j] = capIntValue(REV, mtrSlewed[j], FWD); //CAP ALL MOTORS
		motor[j] = mtrSlewed[j]*sysMotorsEnabled; //ASSIGN MOTORS
		}
	}
