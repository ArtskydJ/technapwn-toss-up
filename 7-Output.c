//Output.c

//Constants
//static const int LIFT_DISABLE_RANGE = 10;

//Variables
static int mtrTarget[10] = {0,0,0,0,0,0,0,0,0,0};
static int mtrSlewed[10] = {0,0,0,0,0,0,0,0,0,0};
static int slewConstants[10];

//Functions
//This function sets all slew constants in an array. This ugly code simplifies
//later code immensely.
void initializeOutput()
	{
	slewConstants[DRIVE_FL]  = DRV_SLEW;
	slewConstants[DRIVE_BL1] = DRV_SLEW;
	slewConstants[DRIVE_BL2] = DRV_SLEW;
	slewConstants[DRIVE_FR]  = DRV_SLEW;
	slewConstants[DRIVE_BR1] = DRV_SLEW;
	slewConstants[DRIVE_BR2] = DRV_SLEW;
	slewConstants[LIFT_L]    = LIFT_SLEW;
	slewConstants[LIFT_R]    = LIFT_SLEW;
	slewConstants[INTK_L]    = INTK_SLEW;
	slewConstants[DESCORER]  = DSCR_SLEW;

	zeroMotors();
	}

//This function sets all motor targets to 0, but not the motors themselves.
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


//This function applies the output variables to their respective motors.
void outputMotion(void)
	{
	if (sysState.curr == DISABLED)     //Disabled
		{
		zeroMotors();
		}
	else if (sysMotorTest)             //Enabled, Motor test mode
		{
		for (int j=0; j<10; j++)
			mtrTarget[j] = (mtrTestEnabled[j]*stkMtrTest1);
		}
	else                               //Enabled, Normal mode
		{
		mtrTarget[DRIVE_FL] =  outDrvL + outDrvS;
		mtrTarget[DRIVE_BL1] = outDrvL - outDrvS;
		mtrTarget[DRIVE_BL2] = outDrvL - outDrvS;
		mtrTarget[DRIVE_FR] =  outDrvR - outDrvS;
		mtrTarget[DRIVE_BR1] = outDrvR + outDrvS;
		mtrTarget[DRIVE_BR2] = outDrvR + outDrvS;
		mtrTarget[LIFT_L] =  outLift;
		mtrTarget[LIFT_R] =  outLift;
		mtrTarget[INTK_L] = outIntk;
		mtrTarget[DESCORER] = outDescorer;
		
		//Pneumatics
		SensorValue[CATAPULT] = outCatapult;
		SensorValue[LOADER] = outLoader;
		}

	for (int j=0; j<10; j++) //Assign motors (with slew control)
		{
		mtrSlewed[j] = slew(mtrTarget[j], mtrSlewed[j], slewConstants[j]);
		mtrSlewed[j] = capIntValue(REV, mtrSlewed[j], FWD);
		motor[j] = mtrSlewed[j];
		}
	}
