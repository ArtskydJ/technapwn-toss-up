//Autonomous.c

//Variables
static T_SENSOR_STATUS autoHitTarget;
static bool autoFoundLeft;
static bool autoFoundRight;
static bool autoDriveReady;
static bool autoLiftReady;
static bool autoIntkReady;
static int autoStep;
static int autoStepCheck;

//Functions
//This function is run when switching from operator/disabled to autonomous.
void stateSwitchToAutonomous()
	{
	autoStep = 0;
	autoStepCheck = 0;
	}


//This function records and resets autonomous variables, and sensor variables
//for in between each autonomous step.
void autoNextStep(void)
	{
	static unsigned int autoTimeRecord[NO_TIME_RECORDS];
#ifdef FULL_DEBUG_STREAM
	writeDebugStreamLine("autoNextStep");
#endif
	string msg1;
	if (autoStep < NO_TIME_RECORDS)
		autoTimeRecord[autoStep] = time1(T1);
	if (autoStep)
		if (time1(T1)<100)  sprintf(msg1,"|%d\t\t",time1(T1));
		else                sprintf(msg1,"|%d\t",time1(T1));
	else                    sprintf(msg1,"|Reset\t");
	writeDebugStreamLine("%s\t|%d\t|",msg1,autoStep);

	//--Autonomous Variables--//
	autoFoundLeft = false;
	autoFoundRight = false;
	autoDriveReady = false;
	autoLiftReady = false;
	autoIntkReady = false;
	autoHitTarget = NOT_HIT;
	autoStep++;

	setToZeroInt(&senGyro);
	setToZeroInt(&senLeftQSE);
	setToZeroInt(&senRightQSE);
	SensorValue[GYRO] = 0;
	SensorValue[QUAD_LEFT] = 0;
	SensorValue[QUAD_RIGHT] = 0;

	//--Sensor Step Starts--//
	setStepInt(&senGyro);
	setStepInt(&senLeftQSE);
	setStepInt(&senRightQSE);
	setStepInt(&senLeftUS);
	setStepInt(&senRightUS);
	setStepInt(&senLineFollow);

	ClearTimer(T1);
	//beep
	}


//This function resets autonomous variables for the beginning of autonomous.
void autoResetStart(int INgoToStep, T_AUTO_SCRIPT INasType,
                    bool INscriptDrive, bool INscriptLift, bool INscriptIntake)
	{
	if (autoStepCheck==autoStep) //If on correct autonomous step
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
				autoScriptTakeover[DRIVE] = INscriptDrive;
				autoScriptTakeover[LIFT]  = INscriptLift;
				autoScriptTakeover[INTK]  = INscriptIntake;
				}
			else
				for (int i=0; i<3; i++)
					autoScriptTakeover[i] = false;
			}
		autoNextStep();
		if (INgoToStep>=2)
			{
			autoStep=INgoToStep;
			writeDebugStreamLine("Skip to\t|%d\t|",INgoToStep);
			}
		timerAuto = 0;
		timerAutoTimeAdd = 0;
		timerTemp = 0;
		autoClockRunning = true;
		}
	autoStepCheck++;
	}


//This function resets autonomous variables for the end of autonomous.
void autoResetEnd(void)
	{
	if (autoStepCheck==autoStep) //If on correct autonomous step
		{
		zeroMotors();
		setToZeroInt(&senGyro);
		setToZeroInt(&senLeftQSE);
		setToZeroInt(&senRightQSE);

		writeDebugStreamLine("+-----------+---+");
		writeDebugStreamLine("|Time: %.1f\t\t|",((float)timerAuto/100));
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


//This function is used in autonomous routines
void auto(unsigned long INspeeds, int INspdS, int INlift, int INintk, bool INcata, bool INtranny, T_END INendType, int INextra)
	{
	if (autoStepCheck==autoStep) //If on correct autonomous step
		{
#ifdef FULL_DEBUG_STREAM
		writeDebugStreamLine("1 lft=%d rht=%d stf=%d lift=%d intk=%d cata=%d end=%d pid=%d",
			decodeL(INspeeds), decodeR(INspeeds), INspdS, INlift, INintk, INcata, INtranny, INendType, INextra);
#endif
		//--Set Outputs--//
		outDrvL = decodeL(INspeeds);
		outDrvR = decodeR(INspeeds);
		outDrvS = INspdS;
		outLift = INlift;
		outIntk = INintk;
		//outDescorer = INdescorer;

		outTranny = INtranny;
		//outLoader = INload;
		//outBrake = INbrake;
		outCatapult = INcata;

		if (outDrvS != 0 && outDrvL==outDrvR)
			{
			outDrvL += (diffStepInt(senGyro)) * GYRO_STRF_P; // + outDrvS/6;
			outDrvR -= (diffStepInt(senGyro)) * GYRO_STRF_P; // - outDrvS/6;
			}
		if (abs(outDrvL) < P_DEAD_ZONE &&
			abs(outDrvR) < P_DEAD_ZONE &&
			abs(outDrvS) < P_DEAD_ZONE)	autoDriveReady= true; //Works
		if (abs(INlift)  < P_DEAD_ZONE)	autoLiftReady = true; //Might work
		if (abs(INintk)  < P_DEAD_ZONE)	autoIntkReady = true; //Might work


		if (senLeftEdge > LINE_EDGE)  autoFoundLeft = true;  //Found Left Edge
		if (senRightEdge > LINE_EDGE) autoFoundRight = true; //Found Right Edge

		if (INendType == TWO_EDG_LN)
			{
			if (autoFoundLeft)  outDrvL = 0;
			if (autoFoundRight) outDrvR = 0;
			}

		if (autoHitTarget==NOT_HIT)
			{
			bool tHitTarget = false;
			ClearTimer(T2); //Timer for PID wait
			switch(INendType) // This code asks "What type of target condition...
				{             // ...are we looking for? Have we met it?"
				case TIME_LIMIT: tHitTarget = (time1(T1)>=INextra); break;
				case DRIV_READY: tHitTarget = autoDriveReady; break;
				case LIFT_READY: tHitTarget = autoLiftReady; break;
				case FULL_READY: tHitTarget = (autoDriveReady && autoLiftReady); break;
				case ONE_EDG_LN: tHitTarget = (autoFoundLeft || autoFoundRight); break;
				case TWO_EDG_LN: tHitTarget = (autoFoundLeft && autoFoundRight); break;
				case SCREEN_BTN: tHitTarget = (changedBool(btnScreenCenter)); break;
				}
			if (tHitTarget)
				autoHitTarget = (INextra == (short)PID) ? PID : NEXT; //If INextra is PID, then PID, else, NEXT
			}
		if (autoHitTarget==PID && time1(T2)>=PID_WAIT_MS) autoHitTarget=NEXT;
		if (INendType!=TIME_LIMIT && INendType!=SCREEN_BTN && time1(T1)>=TIMEOUT_MS) autoHitTarget=NEXT;
		if (autoHitTarget==NEXT) autoNextStep();
		}
	autoStepCheck++;
	}


//This runs the current script, if active
void processScripts(void)
	{
	autoStepCheck = 0;
	switch (autoRoutine.curr) //Scripts
		{
		case -1: scriptHang(); break; //Scripts were not really tested :(
		}
	}


//This runs the current autonomous routine.
void processAutonomous(void)
	{
	if (sysError==ERR_NONE)
		{
		autoStepCheck = 0;
		switch (autoRoutine.curr) //Routines
			{
			case 01: autoRedMid1();         break; //Red...
			case 02: autoRedMid2();         break;
			case 03: autoRedMid3();         break;
			case 04: autoRedHang1();        break;
			case 05: autoRedHang2();        break;
			case 06: autoRedHang3();        break;
			case 07: autoBlueMid1();        break; //Blue...
			case 08: autoBlueMid2();        break;
			case 09: autoBlueMid3();        break;
			case 10: autoBlueHang1();       break;
			case 11: autoBlueHang2();       break;
			case 12: autoBlueHang3();       break;
			case 13:                        break; //None
			case 14: scriptHang();          break; //Other...
			case 15: autoCurrentTest();     break;
			case 16: autoRedProgSkills();   break;
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


//This function takes a number of inches and converts it to encoder ticks. (Assumes a 4 inch wheel)
int InchesToTicks(int n)
	{ return ((float)n*360/(3.14*4)); }
