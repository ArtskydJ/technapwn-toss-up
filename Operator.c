//Constants
static const int JOYSTICK_DEAD_ZONE = 10;
static const int DRV_FWD = 0;
static const int DRV_LFT = 1;
static const int DRV_REV = 2;
static const int DRV_RHT = 3;

//Variables
static int stkMtrTest;
static int stkDrvFwd;
static int stkDrvTrn;
static int stkDrvStf;
static T_LC_BOOL btnLiftUp;
static T_LC_BOOL btnLiftDown;
static T_LC_BOOL btnIntkUp;
static T_LC_BOOL btnIntkDown;
static T_LC_BOOL btnLiftUp2;
static T_LC_BOOL btnLiftDown2;
static T_LC_BOOL btnIntkUp2;
static T_LC_BOOL btnIntkDown2;
static bool btnInvertDriveModifier;
static bool btnInvertDriveFwd;
static bool btnInvertDriveLft;
static bool btnInvertDriveRev;
static bool btnInvertDriveRht;
static bool btnSubroutineModifier;
static bool btnSubroutine1;
static bool btnSubroutine2;
static bool btnSubroutine3;
static bool btnSubroutine4;
static char sysInvertDrive = 0;
static char sysInvertDriveOffset = 0;

//Functions
void inputOperator(void)
	{
	//Set Lasts
	setLastBool(&btnLiftUp);
	setLastBool(&btnLiftDown);
	setLastBool(&btnIntkUp);
	setLastBool(&btnIntkDown);

#ifdef PHYSICAL_ROBOT_TARGET
	//Sticks
	stkDrvFwd =			joystickFilter(vexRT[Ch3]);
	stkDrvStf =			joystickFilter(vexRT[Ch4]);
	stkDrvTrn =			joystickFilter(vexRT[Ch1]);
	stkMtrTest =					  (vexRT[Ch2]);

	//Normal Buttons
	btnLiftUp.curr =			(bool)vexRT[Btn5U];
	btnLiftDown.curr =			(bool)vexRT[Btn5D];
	btnIntkUp.curr =			(bool)vexRT[Btn6U];
	btnIntkDown.curr =			(bool)vexRT[Btn6D];
	btnLiftUp2.curr =			(bool)vexRT[Btn5UXmtr2];
	btnLiftDown2.curr =			(bool)vexRT[Btn5DXmtr2];
	btnIntkUp2.curr =			(bool)vexRT[Btn6UXmtr2];
	btnIntkDown2.curr =			(bool)vexRT[Btn6DXmtr2];

	//Button Modifiers
	btnDisablePots = 			(bool)vexRT[Btn7L];
	//btnSubroutineModifier =	(bool)vexRT[Btn7L];
	//btnInvertDriveModifier =	(bool)vexRT[Btn7R];

	//Function Buttons
	btnInvertDriveFwd =			(bool)vexRT[Btn8U];
	btnInvertDriveRev =			(bool)vexRT[Btn8D];
	btnInvertDriveLft =			(bool)vexRT[Btn8L];
	btnInvertDriveRht =			(bool)vexRT[Btn8R];
	btnSubroutine1 =			(bool)vexRT[Btn8U];
	btnSubroutine2 =			(bool)vexRT[Btn8D];
	btnSubroutine3 =			(bool)vexRT[Btn8L];
	btnSubroutine4 =			(bool)vexRT[Btn8R];
#endif
	}


/* This function checks if the joysticks are
moved from their deadzones.
*/
bool joystickIsMoved(bool checkStkTrn)
	{
	return (stkDrvStf + stkDrvFwd + (stkDrvTrn * checkStkTrn)) != 0;
	}


/* This function takes the raw joystick value and
returns a scaled value.
*/
int joystickFilter(int INraw)
	{
	if (abs(INraw) < JOYSTICK_DEAD_ZONE)	//Dead Zone
		INraw=0;
	INraw = capIntValue(REV, (float)INraw*abs(INraw)/FWD, FWD);	//Exponential function
	return (INraw);
	}


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
			if		(btnSubroutine1) autoRoutine.curr = -1;
			else if	(btnSubroutine2) autoRoutine.curr = -2;
			else if	(btnSubroutine3) autoRoutine.curr = -3;
			else if	(btnSubroutine4) autoRoutine.curr = -4;
			}
		sysInvertDrive = DRV_FWD; //((senAbsGyro+450)%900 + sysInvertDriveOffset) % 4;

		//--Controls--//
		switch(sysInvertDrive)
			{
			case DRV_RHT: //Rotated 0°   (Robot faces driver's right)
				outDrvL = stkDrvStf;
				outDrvR = stkDrvStf;
				outDrvS = stkDrvFwd;
				break;
			case DRV_FWD: //Rotated 90°  (Robot faces away from driver)
				outDrvL = stkDrvFwd;
				outDrvR = stkDrvFwd;
				outDrvS = stkDrvStf;
				break;
			case DRV_LFT: //Rotated 180° (Robot faces driver's left)
				outDrvL = -stkDrvStf;
				outDrvR = -stkDrvStf;
				outDrvS = -stkDrvFwd;
				break;
			case DRV_REV: //Rotated 270° (Robot faces driver)
				outDrvL = -stkDrvFwd;
				outDrvR = -stkDrvFwd;
				outDrvS = -stkDrvStf;
				break;
			}
		outDrvL += stkDrvTrn;
		outDrvR -= stkDrvTrn;
		//--Drive--//
		if (joystickIsMoved(0))
			if (autoScriptTakeover[DRIVE] == STO_TAKEOVER)
				autoRoutine.curr = 0; //Disable script

		//--Lift--//
		static bool tLastLiftPressed=0;
		if (btnLiftUp.curr || btnLiftDown.curr || btnLiftUp2.curr || btnLiftDown2.curr)
			{
			if (autoScriptTakeover[LIFT] == STO_TAKEOVER)
				autoRoutine.curr = 0; //Disable script
			}
		if (1) //(btnDisablePots)
			{
			if (tLastLiftPressed)
				outLift = 15;
			else
				outLift = 0;
			if (btnDisablePots)
				{
				tLastLiftPressed = false;
				outLift = 0;				//Lift Motors Off
				}
			if (btnLiftUp.curr)				//If Lift Up Pressed
				{
				tLastLiftPressed = true;
				outLift = FWD;					//Lift Motors Reverse
				}
			else if (btnLiftDown.curr)		//If Lift Down Pressed
				{
				outLift = REV;					//Lift Motors Forward
				tLastLiftPressed = false;
				}
			else if (btnLiftUp2.curr)				//If Lift Up Pressed
				{
				tLastLiftPressed = true;
				outLift = FWD;					//Lift Motors Reverse
				}
			else if (btnLiftDown2.curr)		//If Lift Down Pressed
				{
				tLastLiftPressed = false;
				outLift = REV;					//Lift Motors Forward
				}
			}
		else
			{
			if (pressed(btnLiftDown))		//If Lift Down Pressed
				{
				liftPresetIndex = capIntValue(128, liftPresetIndex-1, 128+(NO_LIFT_PRESETS-1));
				outLift = liftPresetIndex;
				}
			else if (pressed(btnLiftUp))	//If Lift Up Pressed
				{
				liftPresetIndex = capIntValue(128, liftPresetIndex+1, 128+(NO_LIFT_PRESETS-1));
				outLift = liftPresetIndex;
				}
			else if (pressed(btnLiftDown2))		//If Lift Down Pressed
				{
				liftPresetIndex = capIntValue(128, liftPresetIndex-1, 128+(NO_LIFT_PRESETS-1));
				outLift = liftPresetIndex;
				}
			else if (pressed(btnLiftUp2))	//If Lift Up Pressed
				{
				liftPresetIndex = capIntValue(128, liftPresetIndex+1, 128+(NO_LIFT_PRESETS-1));
				outLift = liftPresetIndex;
				}
			}



		//--Intake--//
		if (btnIntkUp.curr || btnIntkDown.curr || btnIntkUp2.curr || btnIntkDown2.curr)
			{
			if (autoScriptTakeover[INTK] == STO_TAKEOVER)
				autoRoutine.curr = 0; //Disable script
			}

		if (btnIntkUp.curr)				//If Intake Out Pressed
			outIntk = REV;					//Intake Motors Reverse
		else if (btnIntkDown.curr)		//If Intake In Pressed
			outIntk = FWD;					//Intake Motors Forward
		else							//If no Intake buttons Pressed
			outIntk = 0;					//Intake Motors Off

		}
	}
