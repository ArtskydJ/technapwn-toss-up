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
		int tDrvL, tDrvR, tDrvS, tLift, tIntk;
		//--Settings--//
		if (btnSubroutineModifier)
			{						//Negative values are for driver autos
			if		(btnRhtU.curr) autoRoutine.curr = -1;
			else if	(btnRhtR.curr) autoRoutine.curr = -2;
			else if	(btnRhtD.curr) autoRoutine.curr = -3;
			else if	(btnRhtL.curr) autoRoutine.curr = -4;
			}

		//--Drive--//
		tDrvL = stkDrvFwd + stkDrvTrn;
		tDrvR = stkDrvFwd - stkDrvTrn;
		tDrvS = stkDrvStf;

		//--Lift--//
		if (1)				//Replace from here...
			{
			if (btnDisablePots)
				tLift = 0;	//...To here...

//		if (btnDisablePots || autoScriptTakeover[LIFT]==STO_ADD)
//			{				//...With these! (when the lift gets a potentiometer)
			if (btnLiftUp.curr)				//If lift up is pressed
				tLift = UP;						//Run lift motors up
			else if (btnLiftDown.curr)		//If lift down is pressed
				tLift = DOWN;					//Run lift motors down
			else if (btnLiftUp2.curr)		//If lift up is pressed
				tLift = UP;						//Run lift motors up
			else if (btnLiftDown2.curr)		//If lift down is pressed
				tLift = DOWN;					//Run lift motors down
			else							//If no lift buttons are pressed
				tLift = (tLift>0) ? HOLD : 0;	//Run lift motors at hold or 0
			}
		else
			{
			if (pressed(btnLiftDown))		//If Lift Down Pressed
				liftPresetIndex--;				//Previous preset
			else if (pressed(btnLiftUp))	//If Lift Up Pressed
				liftPresetIndex++;				//Next preset
			else if (pressed(btnLiftDown2))	//If Lift Down Pressed
				liftPresetIndex--;				//Previous preset
			else if (pressed(btnLiftUp2))	//If Lift Up Pressed
				liftPresetIndex++;				//Next preset

			liftPresetIndex = capIntValue(L_PRE_START, liftPresetIndex, L_PRE_END);
			tLift = liftPresetIndex;
			}

		//--Intake--//
		if (btnIntkOut.curr)			//If intake out 1 pressed
			tIntk = OUT;					//Intake motors dump out
		else if (btnIntkIn.curr)		//If intake in 1 pressed
			tIntk = IN;						//Intake motors intake in
		else if (btnIntkOut2.curr)		//If intake out 2 pressed
			tIntk = OUT;					//Intake motors dump out
		else if (btnIntkIn2.curr)		//If intake in 2 pressed
			tIntk = IN;						//Intake motors intake in
		else if (outIntkExtend)			//If no intake buttons are pressed and jaw is up
			tIntk = IN*3/4;					//Intake motors slow intake in
		else							//If no intake buttons pressed and jaw is down
			tIntk = 0;						//Intake motors off


		//--Pneumatics--//
		if (pressed(btnRhtR))
			outIntkExtend = !outIntkExtend;


		//--Script Takeover Checking and Applying Outputs--//
		if (tDrvL != 0 || tDrvR != 0 || tDrvS != 0) //If drive is being moved manually
			{
			switch (autoScriptTakeover[DRIVE])
				{
				case STO_ADD:	//Add to outputs
					outDrvL += tDrvL;
					outDrvR += tDrvR;
					outDrvS += tDrvS;
					break;
				case STO_TAKEOVER:
					autoRoutine.curr = 0; //Disable script
					//No break statement (purposeful)
				case STO_NONE:
					outDrvL = tDrvL;
					outDrvR = tDrvR;
					outDrvS = tDrvS;
					break;
				}
			}
		if (tLift != 0 && tLift != HOLD) //If lift is being moved manually
			{
			switch (autoScriptTakeover[LIFT])
				{
				case STO_ADD:	//Add to outputs
					//outLift += tLift; //Will not work with target positions
					break;
				case STO_TAKEOVER:
					autoRoutine.curr = 0; //Disable script
					//No break statement (purposeful)
				case STO_NONE:
					outLift = tLift;
					break;
				}
			}
		if (tIntk != 0) //If intake is being moved manually
			{
			switch (autoScriptTakeover[INTK])
				{
				case STO_ADD:	//Add to outputs
					outIntk += tIntk;
					break;
				case STO_TAKEOVER:
					autoRoutine.curr = 0; //Disable script
					//No break statement (purposeful)
				case STO_NONE:
					outIntk = tIntk;
					break;
				}
			}
		}
	}
