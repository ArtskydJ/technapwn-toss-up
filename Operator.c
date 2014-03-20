//Operator.c

//Constants
static const int JOYSTICK_DEAD_ZONE = 10;

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
static bool btnSubroutineModifier;
static T_LC_BOOL btnRhtU;
static T_LC_BOOL btnRhtL;
static T_LC_BOOL btnRhtR;
static T_LC_BOOL btnRhtD;
static bool disableLift = true;

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
	{ return (stkDrvStf + stkDrvFwd + (stkDrvTrn * checkStkTrn)) != 0; }


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
		if (btnSubroutineModifier)
			{						//Negative values are for driver autos
			if		(btnRhtU.curr) autoRoutine.curr = -1;
			else if	(btnRhtR.curr) autoRoutine.curr = -2;
			else if	(btnRhtD.curr) autoRoutine.curr = -3;
			else if	(btnRhtL.curr) autoRoutine.curr = -4;
			}

		//--Drive--//
		outDrvL = stkDrvFwd + stkDrvTrn;
		outDrvR = stkDrvFwd - stkDrvTrn;
		outDrvS = stkDrvStf;

		//--Lift--//
		if (btnDisablePots || autoScriptTakeover[LIFT])
			{
			if		(btnLiftUp.curr)	outLift = UP;		//If lift up is pressed, run lift motors up
			else if (btnLiftDown.curr)	outLift = DOWN;		//If lift down is pressed, run lift motors down
			else if (btnLiftUp2.curr)	outLift = UP;		//If lift up is pressed, run lift motors up
			else if (btnLiftDown2.curr)	outLift = DOWN;		//If lift down is pressed, run lift motors down
			else						disableLift = true;	//If no lift buttons are pressed, shut off lift motors
			}
		else
			{
			bool tBtnPressed = true;
			if		(pressed(btnLiftDown))	liftPresetIndex--; //If Lift Down 1 pressed, previous preset
			else if (pressed(btnLiftUp))	liftPresetIndex++; //If Lift Up   1 pressed, next preset
			else if (pressed(btnLiftDown2))	liftPresetIndex--; //If Lift Down 2 pressed, previous preset
			else if (pressed(btnLiftUp2))	liftPresetIndex++; //If Lift Up   2 pressed, next preset
			else							tBtnPressed=false; //If no buttons are pressed, set variable
			if (tBtnPressed)
				disableLift = false;

			liftPresetIndex = capIntValue(0, liftPresetIndex, NO_LIFT_PRESETS);
			outLift = L_PRE(liftPresetIndex);
			}
		if (disableLift)					outLift = 0;

		//--Intake--//
		if		(btnIntkOut.curr)	outIntk = OUT; //If intake out 1 pressed, intake motors dump out
		else if (btnIntkIn.curr)	outIntk = IN;  //If intake in  1 pressed, intake motors intake in
		else if (btnIntkOut2.curr)	outIntk = OUT; //If intake out 2 pressed, intake motors dump out
		else if (btnIntkIn2.curr)	outIntk = IN;  //If intake in  2 pressed, intake motors intake in
		else						outIntk = 0;   //If no intake buttons pressed and jaw is down, intake motors off

		//--Pneumatics--//
		outCatapult = btnRhtR.curr

		//--Script Takeover Checking and Applying Outputs--//
		if (autoScriptTakeover[DRIVE] && (outDrvL != 0 || outDrvR != 0 || outDrvS != 0) )
			autoRoutine.curr = 0; //If drive is being moved manually, Disable script

		if (autoScriptTakeover[LIFT] && outLift != 0) 
			autoRoutine.curr = 0; //If lift is being moved manually, Disable script

		if (autoScriptTakeover[INTK] && outIntk != 0) 
			autoRoutine.curr = 0; //If intake is being moved manually, Disable script
		}
	}
