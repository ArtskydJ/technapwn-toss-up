//Operator.c

//Constants
static const int JOYSTICK_DEAD_ZONE = 10;
static const int LIFT_DISABLE_RANGE = 20;

//Variables
static bool btnDisablePots1; //Joystick 1
static bool btnSubroutineModifier1;
static int stkMtrTest1;
static int stkDrvFwd1;
static int stkDrvTrn1;
static int stkDrvStf1;
static T_LC_BOOL btnLiftU1,	btnLiftD1;
static T_LC_BOOL btnIntkI1,	btnIntkO1;
static T_LC_BOOL btnLftU1,	btnLftD1,	btnLftL1,	btnLftR1;
static T_LC_BOOL btnRhtU1,	btnRhtD1,	btnRhtL1,	btnRhtR1;

static bool btnDisablePots2; //Joystick 2
static T_LC_BOOL btnLiftU2,	btnLiftD2;
static T_LC_BOOL btnIntkI2,	btnIntkO2;
static T_LC_BOOL btnLftU2,	btnLftL2,	btnLftR2,	btnLftD2;
static T_LC_BOOL btnRhtU2,	btnRhtL2,	btnRhtR2,	btnRhtD2;

//Functions
void inputOperator(void)
	{
	//Set Lasts
	setLastBool(&btnLiftU1);
	setLastBool(&btnLiftD1);
	setLastBool(&btnIntkO1);
	setLastBool(&btnIntkI1);
	setLastBool(&btnLftU1);
	setLastBool(&btnLftD1);
	setLastBool(&btnLftL1);
	setLastBool(&btnLftR1);
	setLastBool(&btnRhtU1);
	setLastBool(&btnRhtD1);
	setLastBool(&btnRhtL1);
	setLastBool(&btnRhtR1);
	setLastBool(&btnLiftU2); //Joystick 2
	setLastBool(&btnLiftD2);
	setLastBool(&btnIntkO2);
	setLastBool(&btnIntkI2);
	setLastBool(&btnLftU2);
	setLastBool(&btnLftD2);
	setLastBool(&btnLftL2);
	setLastBool(&btnLftR2);
	setLastBool(&btnRhtU2);
	setLastBool(&btnRhtD2);
	setLastBool(&btnRhtL2);
	setLastBool(&btnRhtR2);

#ifdef PHYSICAL_ROBOT_TARGET
	//Sticks
	stkDrvFwd1 =		joystickFilter(vexRT[Ch3]); //Joystick 1
	stkDrvStf1 =		joystickFilter(vexRT[Ch4]);
	stkDrvTrn1 =		joystickFilter(vexRT[Ch1]);
	stkMtrTest1 =					  (vexRT[Ch2]);

	//Shoulder Buttons
	btnLiftU1.curr =	(bool)vexRT[Btn5U]; //Joystick 1
	btnLiftD1.curr =	(bool)vexRT[Btn5D];
	btnIntkI1.curr =	(bool)vexRT[Btn6U];
	btnIntkO1.curr =	(bool)vexRT[Btn6D];
	btnLiftU2.curr =	(bool)vexRT[Btn5UXmtr2]; //Joystick 2
	btnLiftD2.curr =	(bool)vexRT[Btn5DXmtr2];
	btnIntkI2.curr =	(bool)vexRT[Btn6UXmtr2];
	btnIntkO2.curr =	(bool)vexRT[Btn6DXmtr2];

	//Button Modifiers
	btnDisablePots1 = 			(bool)vexRT[Btn7L]; //Joystick 1
	btnDisablePots2 = 			(bool)vexRT[Btn7LXmtr2]; //Joystick 2
	//btnSubroutineModifier1 =	(bool)vexRT[Btn7L]; //Joystick 1
	//btnInvertDriveModifier1 =	(bool)vexRT[Btn7R];

	//Action Buttons
	btnLftU1.curr =		(bool)vexRT[Btn7U]; //Joystick 1
	btnLftD1.curr =		(bool)vexRT[Btn7D];
	btnLftL1.curr =		(bool)vexRT[Btn7L];
	btnLftR1.curr =		(bool)vexRT[Btn7R];
	btnRhtU1.curr =		(bool)vexRT[Btn8U];
	btnRhtD1.curr =		(bool)vexRT[Btn8D];
	btnRhtL1.curr =		(bool)vexRT[Btn8L];
	btnRhtR1.curr =		(bool)vexRT[Btn8R];
	btnLftU2.curr =		(bool)vexRT[Btn7UXmtr2]; //Joystick 2
	btnLftD2.curr =		(bool)vexRT[Btn7DXmtr2];
	btnLftL2.curr =		(bool)vexRT[Btn7LXmtr2];
	btnLftR2.curr =		(bool)vexRT[Btn7RXmtr2];
	btnRhtU2.curr =		(bool)vexRT[Btn8UXmtr2];
	btnRhtD2.curr =		(bool)vexRT[Btn8DXmtr2];
	btnRhtL2.curr =		(bool)vexRT[Btn8LXmtr2];
	btnRhtR2.curr =		(bool)vexRT[Btn8RXmtr2];
#endif
	}


//This function returns true if the joysticks are moved from their deadzones.
bool joystickIsMoved(bool checkStkTrn)
	{ return (stkDrvStf1 + stkDrvFwd1 + (stkDrvTrn1 * checkStkTrn)) != 0; }


//This function takes the raw joystick value and returns a scaled down
//exponetial value. This gives the driver more precise control, when needed.
int joystickFilter(int INraw)
	{
	if (abs(INraw) < JOYSTICK_DEAD_ZONE)	//Dead Zone
		INraw=0;
	INraw = capIntValue(REV, (float)INraw*abs(INraw)/FWD, FWD);	//Exponential function
	return (INraw);
	}

//This function reads the previously set game pad variables and sets the output
//variables accordingly.
void processOperator()
	{
	if (sysMotorTest)
		sysMotorTest = !joystickIsMoved(0);
	else
		{
		//--Settings--//
		if (btnSubroutineModifier1)
			{						//Negative values are for scripts
			if		(btnRhtU1.curr) autoRoutine.curr = -1;
			else if	(btnRhtR1.curr) autoRoutine.curr = -2;
			else if	(btnRhtD1.curr) autoRoutine.curr = -3;
			else if	(btnRhtL1.curr) autoRoutine.curr = -4;
			}

		//--Drive--//
		outDrvL = stkDrvFwd1 + stkDrvTrn1;
		outDrvR = stkDrvFwd1 - stkDrvTrn1;
		outDrvS = stkDrvStf1;

		//--Lift--//
		if (btnDisablePots1 || btnDisablePots2 || autoScriptTakeover[LIFT])
			{
			sysDisableLift = false;
			if		(btnLiftU1.curr)	outLift =  UP;		//If lift up is pressed, run lift motors up
			else if (btnLiftD1.curr)	outLift =  DOWN;	//If lift down is pressed, run lift motors down
			else if (btnLftU1.curr)		outLift =  HALF;	//If lift up is pressed, run lift motors up
			else if (btnLftD1.curr)		outLift = -HALF;	//If lift down is pressed, run lift motors down
			else if (btnLiftU2.curr)	outLift =  UP;		//If lift up is pressed, run lift motors up
			else if (btnLiftD2.curr)	outLift =  DOWN;	//If lift down is pressed, run lift motors down
			else if (btnLftU2.curr)		outLift =  HALF;	//If lift up is pressed, run lift motors up
			else if (btnLftD2.curr)		outLift = -HALF;	//If lift down is pressed, run lift motors down
			else						sysDisableLift = true;	//If no lift buttons are pressed, shut off lift motors
			}
		else
			{
			bool tBtnPressed = true;
			if		(pressed(btnLiftU1))	liftPresetIndex = STS; //If Lift Down 1 pressed, previous preset
			else if (pressed(btnLiftD1))	liftPresetIndex = GND; //If Lift Up   1 pressed, next preset
			else if (pressed(btnLiftU2))	liftPresetIndex = STS; //If Lift Down 2 pressed, previous preset
			else if (pressed(btnLiftD2))	liftPresetIndex = GND; //If Lift Up   2 pressed, next preset
			else if (pressed(btnLftU1))		liftPresetIndex = BAR; //If Lift Down 2 pressed, previous preset
			else if (pressed(btnLftD1))		liftPresetIndex = BMP; //If Lift Up   2 pressed, next preset
			else if (pressed(btnLftU2))		liftPresetIndex = BAR; //If Lift Down 2 pressed, previous preset
			else if (pressed(btnLftD2))		liftPresetIndex = BMP; //If Lift Up   2 pressed, next preset
			else							tBtnPressed = false;   //If no buttons are pressed, set variable
			if (tBtnPressed)				sysDisableLift = false;

			liftPresetIndex = capIntValue(0, liftPresetIndex, NO_LIFT_PRESETS-1);
			outLift = lPre(liftPresetIndex);

			if (liftPresetIndex == (short)GND)
				if (-outLift < LIFT_DISABLE_RANGE) //outLift was abs(outLift)
					outLift = 0; //sysDisableLift = true;
			}
		if (sysDisableLift)
			outLift = 0;

		//--Intake--//
		if		(btnIntkO1.curr)	outIntk = OUT; //If intake out 1 pressed, intake motors dump out
		else if (btnIntkI1.curr)	outIntk = IN;  //If intake in  1 pressed, intake motors intake in
		else if (btnIntkO2.curr)	outIntk = OUT; //If intake out 2 pressed, intake motors dump out
		else if (btnIntkI2.curr)	outIntk = IN;  //If intake in  2 pressed, intake motors intake in
		else						outIntk = 0;   //If no intake buttons pressed, intake motors off

		//--Pneumatics--//
		outCatapult = btnRhtR1.curr || btnRhtR2.curr;

		outLoader = btnRhtD1.curr || btnRhtD2.curr;

		//--Script Takeover Checking and Applying Outputs--//
		if (autoScriptTakeover[DRIVE] && (outDrvL != 0 || outDrvR != 0 || outDrvS != 0) )
			autoRoutine.curr = 0; //If drive is being moved manually, disable script

		if (autoScriptTakeover[LIFT] && outLift != 0)
			autoRoutine.curr = 0; //If lift is being moved manually, disable script

		if (autoScriptTakeover[INTK] && outIntk != 0)
			autoRoutine.curr = 0; //If intake is being moved manually, disable script
		}
	}
