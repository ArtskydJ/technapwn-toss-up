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
static T_LC_BOOL btnIntkIn;
static T_LC_BOOL btnIntkOut;
static T_LC_BOOL btnLiftUp2;
static T_LC_BOOL btnLiftDown2;
static T_LC_BOOL btnIntkIn2;
static T_LC_BOOL btnIntkOut2;
static bool btnInvertDriveModifier;
static bool btnSubroutineModifier;
static T_LC_BOOL btnRhtU;
static T_LC_BOOL btnRhtL;
static T_LC_BOOL btnRhtR;
static T_LC_BOOL btnRhtD;
static char sysInvertDrive = 0;
static char sysInvertDriveOffset = 0;

//Functions
void inputOperator(void)
	{
	//Set Lasts
	setLastBool(&btnLiftUp);
	setLastBool(&btnLiftDown);
	setLastBool(&btnIntkOut);
	setLastBool(&btnIntkIn);
	setLastBool(&btnLiftUp2);
	setLastBool(&btnLiftDown2);
	setLastBool(&btnIntkOut2);
	setLastBool(&btnIntkIn2);
	setLastBool(&btnRhtU);
	setLastBool(&btnRhtD);
	setLastBool(&btnRhtL);
	setLastBool(&btnRhtR);

#ifdef PHYSICAL_ROBOT_TARGET
	//Sticks
	stkDrvFwd =			joystickFilter(vexRT[Ch3]);
	stkDrvStf =			joystickFilter(vexRT[Ch4]);
	stkDrvTrn =			joystickFilter(vexRT[Ch1]);
	stkMtrTest =					  (vexRT[Ch2]);

	//Normal Buttons
	btnLiftUp.curr =			(bool)vexRT[Btn5U];
	btnLiftDown.curr =			(bool)vexRT[Btn5D];
	btnIntkIn.curr =			(bool)vexRT[Btn6U];
	btnIntkOut.curr =			(bool)vexRT[Btn6D];
	btnLiftUp2.curr =			(bool)vexRT[Btn5UXmtr2];
	btnLiftDown2.curr =			(bool)vexRT[Btn5DXmtr2];
	btnIntkIn2.curr =			(bool)vexRT[Btn6UXmtr2];
	btnIntkOut2.curr =			(bool)vexRT[Btn6DXmtr2];

	//Button Modifiers
	btnDisablePots = 			(bool)vexRT[Btn7L];
	//btnSubroutineModifier =	(bool)vexRT[Btn7L];
	//btnInvertDriveModifier =	(bool)vexRT[Btn7R];

	//Function Buttons
	btnRhtU.curr =				(bool)vexRT[Btn8U];
	btnRhtD.curr =				(bool)vexRT[Btn8D];
	btnRhtL.curr =				(bool)vexRT[Btn8L];
	btnRhtR.curr =				(bool)vexRT[Btn8R];
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
			if		(btnRhtU.curr) sysInvertDriveOffset = DRV_FWD;
			else if	(btnRhtD.curr) sysInvertDriveOffset = DRV_REV;
			else if	(btnRhtL.curr) sysInvertDriveOffset = DRV_LFT;
			else if	(btnRhtR.curr) sysInvertDriveOffset = DRV_RHT;
			}
		if (btnSubroutineModifier)
			{						//Negative values are for driver autos
			if		(btnRhtU.curr) autoRoutine.curr = -1;
			else if	(btnRhtR.curr) autoRoutine.curr = -2;
			else if	(btnRhtD.curr) autoRoutine.curr = -3;
			else if	(btnRhtL.curr) autoRoutine.curr = -4;
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
				outLift = 10;
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
				liftPresetIndex--;
			else if (pressed(btnLiftUp))	//If Lift Up Pressed
				liftPresetIndex++;
			else if (pressed(btnLiftDown2))	//If Lift Down Pressed
				liftPresetIndex--;
			else if (pressed(btnLiftUp2))	//If Lift Up Pressed
				liftPresetIndex++;

			liftPresetIndex = capIntValue(L_PRE_START, liftPresetIndex, L_PRE_END);
			outLift = liftPresetIndex;
			}



		//--Intake--//
		if (btnIntkIn.curr || btnIntkOut.curr || btnIntkIn2.curr || btnIntkOut2.curr)
			{
			if (autoScriptTakeover[INTK] == STO_TAKEOVER)
				autoRoutine.curr = 0; //Disable script
			}

		if (btnIntkOut.curr)			//If Intake Out Pressed
			outIntk = OUT;					//Intake Motors Reverse, dump out
		else if (btnIntkIn.curr)		//If Intake In Pressed
			outIntk = IN;					//Intake Motors Forward
		else if (btnIntkOut2.curr)			//If Intake Out Pressed
			outIntk = OUT;					//Intake Motors Reverse, dump out
		else if (btnIntkIn2.curr)		//If Intake In Pressed
			outIntk = IN;					//Intake Motors Forward
		else if (outIntkExtend)			//If no intake buttons are pressed and jaw is up
			outIntk = IN/2;
		else							//If no Intake buttons Pressed
			outIntk = 0;					//Intake Motors Off

		//--Pneumatics--//
		if (pressed(btnRhtR)) outIntkExtend = !outIntkExtend;
		}
	}
