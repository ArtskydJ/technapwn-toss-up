static int stkMtrTest;
static int stkDrvX;
static int stkDrvY;
static int stkDrvZ;
static T_LC_BOOL btnLiftUp;
static T_LC_BOOL btnLiftDown;
static T_LC_BOOL btnIntkUp;
static T_LC_BOOL btnIntkDown;
static bool btnDisablePots;
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


void inputOperator()
	{
#if (_TARGET=="Robot")
	//Sticks
	stkDrvX =			joystickFilter(vexRT[Ch4]);
	stkDrvY =			joystickFilter(vexRT[Ch3]);
	stkDrvZ =			joystickFilter(vexRT[Ch1]);
	stkMtrTest =					  (vexRT[Ch2]);

	//Normal Buttons
	btnLiftUp.curr =			(bool)vexRT[Btn5U];
	btnLiftDown.curr =			(bool)vexRT[Btn5D];
	btnIntkUp.curr =			(bool)vexRT[Btn6U];
	btnIntkDown.curr =			(bool)vexRT[Btn6D];

	//Button Modifiers
	btnDisablePots = 			(bool)vexRT[Btn7D];
	btnSubroutineModifier =		(bool)vexRT[Btn7L];
	btnInvertDriveModifier =	(bool)vexRT[Btn7R];

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


void setOperatorLasts(void)
	{
	setLast(btnLiftUp);
	setLast(btnLiftDown);
	setLast(btnIntkUp);
	setLast(btnIntkDown);
	}


/* This function checks if the joysticks are
moved from their deadzones.
*/
bool joystickIsMoved(bool checkStkZ)
	{
	return (stkDrvX + stkDrvY + (stkDrvZ * checkStkZ)) != 0;
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
			if		(btnSubroutine1) {/*sysVirtualAuto=true;*/ autoRoutine.curr = -1;}
			else if	(btnSubroutine2) {/*sysVirtualAuto=true;*/ autoRoutine.curr = -2;}
			else if	(btnSubroutine3) {/*sysVirtualAuto=true;*/ autoRoutine.curr = -3;}
			else if	(btnSubroutine4) {/*sysVirtualAuto=true;*/ autoRoutine.curr = -4;}
			}
		sysInvertDrive = DRV_FWD; //((senAbsGyro+450)%900 + sysInvertDriveOffset) % 4;

		//--Controls--//
		switch(sysInvertDrive)
			{
			case DRV_RHT: //Rotated 0°   (Robot faces driver's right)
				outDrvX = stkDrvY;
				outDrvY = stkDrvX; break;
			case DRV_FWD: //Rotated 90°  (Robot faces away from driver)
				outDrvX = stkDrvX;
				outDrvY = stkDrvY; break;
			case DRV_LFT: //Rotated 180° (Robot faces driver's left)
				outDrvX = -stkDrvY;
				outDrvY = -stkDrvX; break;
			case DRV_REV: //Rotated 270° (Robot faces driver)
				outDrvX = -stkDrvX;
				outDrvY = -stkDrvY; break;
			}
		outDrvZ = stkDrvZ;
		//--Drive--//
		if (joystickIsMoved(0))
			if (autoScriptTakeover[DRIVE] == STO_TAKEOVER)
				autoRoutine.curr = 0; //Disable script

		//--Lift--//
		if (btnLiftUp.curr || btnLiftDown.curr)
			{
			if (autoScriptTakeover[LIFT] == STO_TAKEOVER)
				autoRoutine.curr = 0;
			}
		if (btnLiftUp.curr)				//If Lift Up Pressed
			outLift = FWD;					//Lift Motors Reverse
		else if (btnLiftDown.curr)		//If Lift Down Pressed
			outLift = REV;					//Lift Motors Forward
		else if (abs(outLift) <= FWD || btnDisablePots)	//If a speed setting and no lift buttons pressed OR disablePots is pressed
			outLift = 0;					//Lift Motors Off


		//--Intake--//
		if (btnIntkUp.curr || btnIntkDown.curr)
			{
			if (autoScriptTakeover[INTK] == STO_TAKEOVER)
				autoRoutine.curr = 0;
			}

		if (btnIntkUp.curr)				//If Intake Out Pressed
			outIntk = REV;					//Intake Motors Reverse
		else if (btnIntkDown.curr)		//If Intake In Pressed
			outIntk = FWD;					//Intake Motors Forward
		else							//If no Intake buttons Pressed
			outIntk = 0;					//Intake Motors Off

		}
	}
