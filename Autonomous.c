//Constants
static const int NO_TIME_RECORDS = 100;
static const int PID_WAIT_MS = 200;
static const int SENSOR_HIT = 0;
static const int MIN_TIMEOUT = 1;
static const int MAX_TIMEOUT = 2;
static const int PID_ZONE = 20;

//Autonomous
static T_SENSOR_STATUS autoHitTarget;
//static int autoNextCondition;
static bool autoFoundLeft;
static bool autoFoundRight;
static bool autoDriveReady;
static bool autoLiftReady;
static bool autoIntkReady;
static bool autoStrafeReady;
static int autoStep;
static int autoStepCheck;
static int autoStepStatus;

//PID
static T_PID PIDLiftL;
static T_PID PIDLiftR;
//static T_PID PIDIntk; //Continuous intake; don't need.
static T_PID PIDLineFollow;
static T_PID PIDWallFollow;
static T_PID PIDDriveL;
static T_PID PIDDriveR;
static T_PID PIDStrafeEncod;
static T_PID PIDStrafeUltra;
static T_PID PIDGyro;

//Arrays
static unsigned int autoTimeRecord[NO_TIME_RECORDS];


void initializeAutonomous(void)
	{
		//PID Controllers
	PIDLiftL.kp = 0.1;
	PIDLiftL.ki = 0.00;
	PIDLiftL.kd = 0.00;

	PIDLiftR.kp = 0.1;
	PIDLiftR.ki = 0.00;
	PIDLiftR.kd = 0.00;

	/*PIDIntk.kp = 0.1;
	PIDIntk.ki = 0.00;
	PIDIntk.kd = 0.00;*/

	PIDLineFollow.kp = 0.1;
	PIDLineFollow.ki = 0.00;
	PIDLineFollow.kd = 0.00;

	PIDWallFollow.kp = 0.1;
	PIDWallFollow.ki = 0.00;
	PIDWallFollow.kd = 0.00;

	PIDDriveL.kp = 0.6;
	PIDDriveL.ki = 0.00;
	PIDDriveL.kd = 0.00;

	PIDDriveR.kp = 0.6;
	PIDDriveR.ki = 0.00;
	PIDDriveR.kd = 0.00;

	PIDStrafeEncod.kp = 0.6;
	PIDStrafeEncod.ki = 0.00;
	PIDStrafeEncod.kd = 0.00;

	PIDStrafeUltra.kp = 0.6;
	PIDStrafeUltra.ki = 0.00;
	PIDStrafeUltra.kd = 0.00;

	PIDGyro.kp = 2;
	PIDGyro.ki = 0.00;
	PIDGyro.kd = 0.00;

	autoRoutine.curr = 0;
	}


void stateSwitchToAutonomous()
	{
	autoStep = 0;
	autoStepCheck = 0;
	}


void autoNextStep(void)
	{
#ifdef FULL_DEBUG_STREAM
	writeDebugStreamLine("autoNextStep");
#endif
	string msg1,msg2="";
	if (autoStep < NO_TIME_RECORDS)
		autoTimeRecord[autoStep] = time1(T1);
	if (autoStep)
		{
		if (time1(T1)<100)
			sprintf(msg1,"|%d\t\t",time1(T1));
		else
			sprintf(msg1,"|%d\t",time1(T1));
		}
	else
		{
		sprintf(msg1,"|Reset\t",autoStep);
		}
	if		(autoStepStatus==MIN_TIMEOUT)	sprintf(msg2,"Min");
	else if	(autoStepStatus==MAX_TIMEOUT)	sprintf(msg2,"Max");
	writeDebugStreamLine("%s%s\t|%d\t|",msg1,msg2,autoStep);
	autoClockRunning = true;
	autoFoundLeft = false;
	autoFoundRight = false;
	autoDriveReady = false;
	autoLiftReady = false;
	autoIntkReady = false;
	autoHitTarget = NOT_HIT;
	autoStepStatus = SENSOR_HIT;
	autoStep++;
	//autoStepCheck = 0;
	setToZeroInt(senLeftQSE);
	setToZeroInt(senRightQSE);
	SensorValue[QUAD_LEFT] = 0;
	SensorValue[QUAD_RIGHT] = 0;
	setAutoStepsStarts();
	ClearTimer(T1);
	//beep
	}


void autoResetStart(int INgoToStep, T_AUTO_SCRIPT INasType, T_SCRIPT_TAKEOVER INstoType,
					bool INscriptDrive, bool INscriptLift, bool INscriptIntake)
	{
	if (autoStepCheck==autoStep)
		{
		writeDebugStreamLine("+---------------+");
		writeDebugStreamLine("|Routine: %d\t\t|",autoRoutine.curr);
		writeDebugStreamLine("+-----------+---+");
#ifdef FULL_DEBUG_STREAM
		writeDebugStreamLine("autoResetStart as=%d",autoStep);
#endif
		if (autoClockRunning==true || autoStep==0)
			{
			if (INasType==SCRIPT)
				{
				autoScriptTakeover[DRIVE] = (bool)(INstoType * INscriptDrive);
				autoScriptTakeover[LIFT]  = (bool)(INstoType * INscriptLift);
				autoScriptTakeover[INTK]  = (bool)(INstoType * INscriptIntake);
				}
			else
				for (int i=0; i<3; i++)
					autoScriptTakeover[i] = (bool)STO_NONE;
			}
		autoNextStep();
		if (INgoToStep>=2)
			{
			autoStep=INgoToStep;
			writeDebugStreamLine("Skip to\t|%d\t|",INgoToStep);
			}
		zeroMotors();
		setToZeroInt(senLeftQSE);
		setToZeroInt(senRightQSE);
		timerAuto = 0;
		}
	autoStepCheck++;
	}


void autoResetEnd(void)
	{
	if (autoStepCheck==autoStep /*|| !sysVirtualAuto*/)
		{
		zeroMotors();
		setToZeroInt(senLeftQSE);
		setToZeroInt(senRightQSE);

		writeDebugStreamLine("+-----------+---+");
		writeDebugStreamLine("|Time: %.1f\t\t|",((float)timerAuto/1000));
		writeDebugStreamLine("+---------------+");
		//sysVirtualAuto = false;
		sysLCDBacklight = LCD_BLINK_SLOW;
		autoClockRunning = false;
		autoRoutine.curr = 0;
#ifdef FULL_DEBUG_STREAM
		writeDebugStreamLine("autoResetEnd");
#endif
		}
	}


void auto(T_DRIVE INdrvType, int INdrvLft, int INdrvRht, int INdrvTarget,
		T_STRAFE INstrfType, int INstrfSpeed, int INstrfTarget,
		int INlift, int INintk, T_END INendType, int INminTime, int INmaxTime, T_SENSOR_STATUS INdelayPID)
	{
	if (autoStepCheck==autoStep)
		{
#ifdef FULL_DEBUG_STREAM
		writeDebugStreamLine("1 dtp=%d dl=%d dr=%d dtg=%d\n2 stp=%d ss=%d stg=%d3 \nl=%d i=%d et=%d min=%d max=%d pid=%d",
			INdrvType, INdrvLft, INdrvRht, INdrvTarget,
			INstrfType, INstrfSpeed, INstrfTarget,
			INlift, INintk, INendType, INminTime, INmaxTime, INdelayPID);
#endif
		//--Initialize--//
		outDrvL = 0;
		outDrvR = 0;
		outDrvS = 0;
		//--Set Outputs--//
		outLift = INlift;
		if (abs(INlift)<=127)					autoLiftReady = true;
		else if (abs(PIDLiftL.error) < PID_ZONE
			&& abs(PIDLiftR.error) < PID_ZONE)	autoLiftReady = true;
		outIntk = INintk;
		/*if (abs(INintk)<=127)					autoIntkReady = true;
		else if (abs(PIDIntk.error) < PID_ZONE)	autoIntkReady = true;*/

		switch (INdrvType) //Driving
			{
			case DT_IN_SPD:
				outDrvL = INdrvLft;
				outDrvR = INdrvRht;
				autoDriveReady = true;
				break;
			case DT_IN_ENC:
				updatePIDController(PIDDriveL,INdrvLft - diffStepInt(senLeftQSE));
				updatePIDController(PIDDriveL,INdrvRht - diffStepInt(senRightQSE));
				outDrvL = PIDDriveL.output;
				outDrvR = PIDDriveR.output;
				capIntValue(-abs(INdrvTarget), outDrvL, abs(INdrvTarget));
				capIntValue(-abs(INdrvTarget), outDrvR, abs(INdrvTarget));
				if (abs(PIDDriveL.error)<PID_ZONE && abs(PIDDriveR.error)<PID_ZONE) autoDriveReady = true;
				break;
			case DT_C_LINE:											//Follow Line
				updatePIDController(PIDLineFollow,0); //Change 0 to (senLineCenter-LINE_TILE_AVG) or something
				outDrvL = INdrvLft - PIDLineFollow.output;
				outDrvR = INdrvRht + PIDLineFollow.output;
				break;
			case DT_G_TURN:											//Gyro turn
				updatePIDController(PIDGyro, INdrvTarget-diffStepInt(senGyro));
				outDrvL = -PIDGyro.output;
				outDrvR =  PIDGyro.output;
				capIntValue(-abs(INdrvLft), outDrvL, abs(INdrvLft));
				capIntValue(-abs(INdrvRht), outDrvR, abs(INdrvRht));
				if (abs(PIDGyro.error) < PID_ZONE) autoDriveReady = true;
				break;
			case DT_LEFT_W:											//Follow Left Wall
				updatePIDController(PIDWallFollow, INdrvTarget-senLeftUS.curr);
				outDrvL = INdrvLft - PIDWallFollow.output;
				outDrvR = INdrvRht + PIDWallFollow.output;
				break;
			case DT_RIHT_W:											//Follow Right Wall
				updatePIDController(PIDWallFollow, INdrvTarget-senRightUS.curr);
				outDrvL = INdrvLft - PIDWallFollow.output;
				outDrvR = INdrvRht + PIDWallFollow.output;
				break;
			}

		switch (INstrfType) //Strafing (with auto gyro align)
			{
			case ST_IN_SPD:											//Speed
				outDrvS = INstrfSpeed;
				autoStrafeReady = true;
				break;
			case ST_IN_ENC:											//Encoder distance
				outDrvS = updatePIDController(PIDStrafeEncod, INstrfTarget - diffStepInt(senLeftQSE));
				capIntValue((-abs(INstrfSpeed)), outDrvS, abs(INstrfSpeed));
				if (abs(PIDStrafeEncod.error)<PID_ZONE) autoStrafeReady = true;
				break;
			case ST_U_LEFT:											//L Ultra distance
				outDrvS = updatePIDController(PIDStrafeUltra, INstrfTarget - senLeftUS.curr);
				capIntValue((-abs(INstrfSpeed)), outDrvS, abs(INstrfSpeed));
				if (abs(PIDStrafeUltra.error)<PID_ZONE) autoStrafeReady = true;
				break;
			case ST_U_RIHT:											//R Ultra distance
				outDrvS = updatePIDController(PIDStrafeUltra, INstrfTarget - senRightUS.curr);
				capIntValue((-abs(INstrfSpeed)), outDrvS, abs(INstrfSpeed));
				if (abs(PIDStrafeUltra.error)<PID_ZONE) autoStrafeReady = true;
				break;
			}

		if (outDrvS != 0)
			{
			updatePIDController(PIDGyro, diffStepInt(senGyro));
			outDrvL -= PIDGyro.output;
			outDrvR += PIDGyro.output;
			}


		if (senLeftEdge > EDGE_LINE_UP)		autoFoundLeft = true;	//Found Left Edge
		if (senRightEdge > EDGE_LINE_UP)	autoFoundRight = true;	//Found Right Edge

		if (INendType == ET_TWO_EDG_LN)
			{
			if (autoFoundLeft)	outDrvL = BRAKE;
			if (autoFoundRight)	outDrvR = BRAKE;
			}

		if (autoHitTarget==NOT_HIT)
			{
			if (INdelayPID<NEXT) INdelayPID=NEXT;
			if (INdelayPID>PID)  INdelayPID=PID;
			ClearTimer(T2); //Timer for PID wait
			switch(INendType) // This code asks what type of target condition are we looking for? Have we met it?
				{
				case ET_TIME_LIMIT: if (time1(T1)>=INminTime)								autoHitTarget=INdelayPID;break;
				case ET_DRIV_READY: if (autoDriveReady && autoStrafeReady)					autoHitTarget=INdelayPID;break;
				case ET_LIFT_READY: if (autoLiftReady)										autoHitTarget=INdelayPID;break;
				case ET_FULL_READY: if (autoDriveReady && autoLiftReady && autoStrafeReady)	autoHitTarget=INdelayPID;break;
				case ET_ONE_EDG_LN: if (autoFoundLeft || autoFoundRight)					autoHitTarget=INdelayPID;break;
				case ET_TWO_EDG_LN: if (autoFoundLeft && autoFoundRight)					autoHitTarget=INdelayPID;break;
				case ET_SCREEN_BTN: if (nLCDButtons)										autoHitTarget=INdelayPID;break;
			//	case ET_FRONT_LINE: if (SenRightLine>RightLineFolPosi)						autoHitTarget=INdelayPID;break;
				default://nothing
				}
			}
		if (autoHitTarget==PID   && time1(T2)>=PID_WAIT_MS)								{autoHitTarget=NEXT;} //PID timeout
		if (time1(T1)>=INmaxTime && INmaxTime!=0)										{autoHitTarget=NEXT; autoStepStatus=MAX_TIMEOUT;} //Max Time timeout
		if (time1(T1)<=INminTime && autoHitTarget==NEXT	&& INendType!=ET_TIME_LIMIT)	{autoStepStatus=MIN_TIMEOUT;} //Min Time timeout
		if (time1(T1)>=INminTime && autoHitTarget==NEXT)								{autoNextStep();} //Go to next step
		} // if (!RESET_AUTO)
	autoStepCheck++;
	}


void processScripts(void)
	{
	if (sysError==ERR_NONE)
		{
		autoStepCheck = 0;
		switch (autoRoutine.curr) //Scripts
			{
			case -2: scriptEmpty();		break;
			case -1: scriptDescore();	break;
			}
		}
	}


void processAutonomous(void)
	{
	if (sysError==ERR_NONE)
		{
		autoStepCheck = 0;
		switch (autoRoutine.curr) //Routines
			{
			case 1: autoTest();	break; //2
			case 2: scriptEmpty();	break;
			case 3: scriptEmpty();	break;
			}
#ifdef FULL_DEBUG_STREAM
		if (autoRoutine.curr==0 && changed(sysState))
			writeDebugStreamLine("No Routine");
#endif
		}
	else
		{
		zeroMotors(); //If there is an error (low battery) then beep and stop.
		}
	}
