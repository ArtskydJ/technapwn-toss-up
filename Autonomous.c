//Variables
static T_SENSOR_STATUS autoHitTarget;
//static int autoNextCondition;
static bool autoFoundLeft;
static bool autoFoundRight;
static bool autoDriveReady;
static bool autoLiftReady;
static bool autoIntkReady;
static int autoStep;
static int autoStepCheck;
static int autoStepStatus;

//Functions
void stateSwitchToAutonomous()
	{
	autoStep = 0;
	autoStepCheck = 0;
	}

void setAutoStepsStarts()
	{
	//--Sensors--//
	setStepInt(&senGyro);
	setStepInt(&senLeftQSE);
	setStepInt(&senRightQSE);
	setStepInt(&senLeftUS);
	setStepInt(&senRightUS);
	}


void autoNextStep(void)
	{
	static unsigned int autoTimeRecord[NO_TIME_RECORDS];
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
	setToZeroInt(senLeftQSE);
	setToZeroInt(senRightQSE);
	SensorValue[QUAD_LEFT] = 0;
	SensorValue[QUAD_RIGHT] = 0;
	SensorValue[GYRO] = 0;
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
		writeDebugStreamLine("|Routine: %2d\t|",autoRoutine.curr);
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
		timerAuto = 0;
		}
	autoStepCheck++;
	}


void autoResetEnd(void)
	{
	if (autoStepCheck==autoStep)
		{
		zeroMotors();
		setToZeroInt(senLeftQSE);
		setToZeroInt(senRightQSE);

		writeDebugStreamLine("+-----------+---+");
		writeDebugStreamLine("|Time: %.1f\t\t|",((float)timerAuto/1000));
		writeDebugStreamLine("+---------------+");
		sysLCDBacklight = LCD_BLINK_SLOW;
		autoClockRunning = false;
		autoRoutine.curr = 0;
		sysAutoMode = false;
#ifdef FULL_DEBUG_STREAM
		writeDebugStreamLine("autoResetEnd");
#endif
		}
	}


void auto(int INspdL, int INspdR, int INspdS, int INlift, int INintk,
		T_END INendType, int INminTime, int INmaxTime, T_SENSOR_STATUS INdelayPID)
	{
	if (autoStepCheck==autoStep)
		{
#ifdef FULL_DEBUG_STREAM
		writeDebugStreamLine("1 lft=%d rht=%d str=%d lift=%d intk=%d end=%d min=%d max=%d pid=%d",
			INspdL, INspdR, INspdS, INlift, INintk, INendType, INminTime, INmaxTime, INdelayPID);
#endif
		//--Set Outputs--//
		outDrvL = INspdL;
		outDrvR = INspdR;
		outDrvS = INspdS;
		outLift = INlift;
		outIntk = INintk;
		if (outDrvS != 0)
			{
			outDrvL += (diffStepInt(senGyro) - senGyro.curr) * GYRO_P;
			outDrvR -= (diffStepInt(senGyro) - senGyro.curr) * GYRO_P;
			}
		if (abs(outDrvL)<PID_ZONE && abs(outDrvR)<PID_ZONE && abs(outDrvS)<PID_ZONE)
			autoDriveReady=true;
		if (abs(INlift)<=127)							autoLiftReady = true;
		//else if (abs(PIDLift.error.curr) < PID_ZONE)	autoLiftReady = true; //Will not be able to sense lift height finish...
		if (abs(INintk)<=127)							autoIntkReady = true;
		//else if (abs(PIDIntk.error.curr) < PID_ZONE)	autoIntkReady = true;


		if (senLeftEdge > LINE_EDGE)  autoFoundLeft = true;  //Found Left Edge
		if (senRightEdge > LINE_EDGE) autoFoundRight = true; //Found Right Edge

		if (INendType == TWO_EDG_LN)
			{
			if (autoFoundLeft)  outDrvL=0;
			if (autoFoundRight) outDrvR = 0;
			}

		if (autoHitTarget==NOT_HIT)
			{
			ClearTimer(T2); //Timer for PID wait
			switch(INendType) // This code asks "What type of target condition are we looking for? Have we met it?"
				{
				case TIME_LIMIT: if (time1(T1)>=INminTime)				autoHitTarget = INdelayPID; break;
				case DRIV_READY: if (autoDriveReady)					autoHitTarget = INdelayPID; break;
				case LIFT_READY: if (autoLiftReady)						autoHitTarget = INdelayPID; break;
				case FULL_READY: if (autoDriveReady && autoLiftReady)
																		autoHitTarget = INdelayPID; break;
				case ONE_EDG_LN: if (autoFoundLeft || autoFoundRight)	autoHitTarget = INdelayPID; break;
				case TWO_EDG_LN: if (autoFoundLeft && autoFoundRight)	autoHitTarget = INdelayPID; break;
				case SCREEN_BTN: if (changedBool(btnScreenCenter))		autoHitTarget = INdelayPID; break;
				default://nothing
				}
			}
		if (autoHitTarget==PID   && time1(T2)>=PID_WAIT_MS) //PID timeout
			autoHitTarget=NEXT;

		if (time1(T1)>=INmaxTime && INmaxTime!=0 && INendType!=TIME_LIMIT) //Max Time timeout
			{
			autoHitTarget=NEXT;
			autoStepStatus=MAX_TIMEOUT;
			}
		if (time1(T1)<=INminTime && autoHitTarget==NEXT	&& INendType!=TIME_LIMIT) //Min Time timeout
			autoStepStatus=MIN_TIMEOUT;

		if (time1(T1)>=INminTime && autoHitTarget==NEXT) //Go to next step
			autoNextStep();

		}
	autoStepCheck++;
	}


void processScripts(void)
	{
	if (sysError==ERR_NONE)
		{
		autoStepCheck = 0;
		switch (autoRoutine.curr) //Scripts
			{
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
			case 01: autoBlueMid1();  break;
			case 02: autoRedMid1();   break;
			case 03: autoBlueHang1(); break;
			case 04: autoRedHang1();  break;
			case 05:                          break;
			case 06:                          break;
			case 07:                          break;
			case 08:                          break;
			case 09: autoTestThings();        break;
			case 10: autoTestDrive();         break;
			case 11: autoTestGyro();          break;
			case 12: autoBlueProgSkills();    break;
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


/* This function takes a number of inches and
converts.
*/
int InchesToTicks(int n)
	{
	return ((float)n*360/(3.14*4));
	}
