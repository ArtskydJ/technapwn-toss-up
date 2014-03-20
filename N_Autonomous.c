void autoNextStep()
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
	setToZero(senLeftQSE);
	setToZero(senRightQSE);
	SensorValue[QUAD_LEFT] = 0;
	SensorValue[QUAD_RIGHT] = 0;
	setAutoStepsStarts();
	ClearTimer(T1);
	//beep
	}


//void autoResetStart(int INgoToStep, int INautoType, int INscriptTakeoverType = (0), bool INscriptDrive = (0), bool INscriptLift = (0), bool INscriptIntake = (0))
void autoResetStart(int INgoToStep, int INautoType, int INscriptTakeoverType, bool INscriptDrive, bool INscriptLift, bool INscriptIntake)
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
			if (INautoType==SCRIPT)
				{
				autoScriptTakeover[DRIVE] = INscriptTakeoverType * INscriptDrive;
				autoScriptTakeover[LIFT]  = INscriptTakeoverType * INscriptLift;
				autoScriptTakeover[INTK]  = INscriptTakeoverType * INscriptIntake;
				}
			else
				for (int i=0; i<3; i++)
					autoScriptTakeover[i] = ST_NONE;
			}
		autoNextStep();
		if (INgoToStep>=2)
			{
			autoStep=INgoToStep;
			writeDebugStreamLine("Skip to\t|%d\t|",INgoToStep);
			}
		zeroMotors();
		setToZero(senLeftQSE);
		setToZero(senRightQSE);
		timerAuto = 0;
		}
	autoStepCheck++;
	}


void autoResetEnd()
	{
	if (autoStepCheck==autoStep || !sysVirtualAuto)
		{
		zeroMotors();
		setToZero(senLeftQSE);
		setToZero(senRightQSE);

		writeDebugStreamLine("+-----------+---+");
		writeDebugStreamLine("|Time: %.1f\t\t|",((float)timerAuto/1000));
		writeDebugStreamLine("+---------------+");
		sysVirtualAuto = false;
		sysLCDBacklight = LCD_BLINK_SLOW;
		autoClockRunning = false;
		autoRoutine.curr = 0;
#ifdef FULL_DEBUG_STREAM
		writeDebugStreamLine("autoResetEnd");
#endif
		}
	}


void auto(int INdrvLft, int INdrvRht, int INdrvStrafe, int INlift, int INintk, int INendType, int INminTime, int INmaxTime, int INdelayPID)
	{
	if (autoStepCheck==autoStep)
		{
#ifdef FULL_DEBUG_STREAM
		writeDebugStreamLine("dl=%d dr=%d ds=%d l=%d i=%d et=%d mn=%d mx=%d dp=%d",
			INdrvLft,INdrvRht,INdrvStrafe,INlift,INintk,INendType,INminTime,INmaxTime,INdelayPID);
#endif
		//--Initialize--//
		outDrvL = 0;
		outDrvR = 0;
		outDrvS = 0;
		//--Set Outputs--//
		outLift = INlift;
		if (abs(INlift)<=127)					autoLiftReady = true;
		else if (abs(PIDLift.error) < PID_ZONE)	autoLiftReady = true;
		outIntk = INintk;
		if (abs(INintk)<=127)					autoIntkReady = true;
		else if (abs(PIDIntk.error) < PID_ZONE)	autoIntkReady = true;

		// INdrvType  is defined as INdrvLft
		// INdrvSpeed is defined as INdrvRht
		// INdrvType  is defined as INdrvLft
		switch (INdrvType) 
			{
			case CNTR_LINE:											//Follow Line
				updatePIDController(PIDLineFollow,0); //Change 0 to (senLineCenter-LINE_TILE_AVG) or something
				outDrvL = INdrvSpeed - PIDLineFollow.output;
				outDrvR = INdrvSpeed + PIDLineFollow.output;
				break;
			case GYRO_BOTH:											//Gyro turn both
				updatePIDController(PIDGyro, INdrvTarget-diffStep(senGyro));
				outDrvL = -PIDGyro.output; capValue(-INdrvSpeed,outDrvL,INdrvSpeed);
				outDrvR =  PIDGyro.output; capValue(-abs(INdrvSpeed),outDrvR,abs(INdrvSpeed));
				if (abs(PIDGyro.error) < PID_ZONE) autoDriveReady = true;
				break;
			case GYRO_LEFT:											//Gyro turn left
				updatePIDController(PIDGyro, INdrvTarget-diffStep(senGyro));
				outDrvL = PIDGyro.output; capValue(-abs(INdrvSpeed),outDrvL,abs(INdrvSpeed));
				outDrvR = 0;
				if (abs(PIDGyro.error) < PID_ZONE) autoDriveReady = true;
				break;
			case GYRO_RIHT:											//Gyro turn right
				updatePIDController(PIDGyro, INdrvTarget-diffStep(senGyro));
				outDrvL = 0;
				outDrvR = PIDGyro.output; capValue(-abs(INdrvSpeed),outDrvR,abs(INdrvSpeed));
				if (abs(PIDGyro.error) < PID_ZONE) autoDriveReady = true;
				break;
			case LEFT_WALL:											//Follow Left Wall
				updatePIDController(PIDWallFollow, INdrvTarget-senLeftUS.curr);
				outDrvL = INdrvSpeed - PIDWallFollow.output;
				outDrvR = INdrvSpeed + PIDWallFollow.output;
				break;
			case RIHT_WALL:											//Follow Right Wall
				updatePIDController(PIDWallFollow, INdrvTarget-senRightUS.curr);
				outDrvL = INdrvSpeed - PIDWallFollow.output;
				outDrvR = INdrvSpeed + PIDWallFollow.output;
				break;
			}

		if (abs(INdrvLft)<=127 && abs(INdrvRht)<=127)				//DRIVE SPEED		INdrvType = INdrvLft
			{
			outDrvL = INdrvLft;
			outDrvR = INdrvRht;
			autoDriveReady = true;
			}
		else if (INdrvType>=MAX_TYPES || INdrvType<-127)			//DRIVE ENCODER		INdrvType = INdrvLft
			{
			updatePIDController(PIDDriveL,INdrvLft - diffStep(senLeftQSE));
			updatePIDController(PIDDriveL,INdrvRht - diffStep(senRightQSE));
			outDrvL = PIDDriveL.output;
			outDrvR = PIDDriveR.output;
			if (abs(PIDDriveL.error)<PID_ZONE && abs(PIDDriveR.error)<PID_ZONE) autoDriveReady = true;
			}

		if (INdrvStrafe!=0)											//Normal strafing (gyro)
			{
			
			int tBit0 = (INdrvStrafe & (1 << 14)) != 0;	//Take the first and second bit
			int tBit1 = (INdrvStrafe & (1 << 15)) != 0;
			int tStrafeType = tBit0 * 2 + tBit1;		//Turn them into numbers 0-3
			INdrvStrafe |= (1 << 14);					//Delete the extra data (otherwise it conflicts)
			INdrvStrafe |= (1 << 15);
			int tStrafeTarget;
			if		(tStrafeType == STRF_ENC)	tStrafeTarget = INdrvStrafe - diffStep(senLeftQSE);
			else if (tStrafeType == STRF_L_US)	tStrafeTarget = INdrvStrafe - senLeftUS.curr; 
			else if (tStrafeType == STRF_R_US)	tStrafeTarget = INdrvStrafe - senRightUS.curr;
			updatePIDController(PIDGyro, diffStep(senGyro));
			outDrvL -= PIDGyro.output;
			outDrvR += PIDGyro.output;
			if (abs(INdrvStrafe)<=127)								//STRAFE SPEED
				{
				outDrvS = INdrvStrafe;
				autoStrafeReady = true;
				}
			else													//STRAFE ENDPOINT
				{
				outDrvS = updatePIDController(PIDDriveStrafe,tStrafeTarget);
				if (abs(PIDDriveStrafe.error)<PID_ZONE) autoStrafeReady = true;
				}
			}
		else
			{
			outDrvS = 0;
			autoStrafeReady = true;
			}

		if (senLeftEdge > EDGE_LINE_UP)		autoFoundLeft = true;	//Found Left Edge
		if (senRightEdge > EDGE_LINE_UP)	autoFoundRight = true;	//Found Right Edge

		if (INendType==TWO_EDG_LN)
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
				case TIME_LIMIT: if (time1(T1)>=INminTime)								autoHitTarget=INdelayPID;break;
				case DRIV_READY: if (autoDriveReady && autoStrafeReady)					autoHitTarget=INdelayPID;break;
				case LIFT_READY: if (autoLiftReady)										autoHitTarget=INdelayPID;break;
				case FULL_READY: if (autoDriveReady && autoLiftReady && autoStrafeReady)autoHitTarget=INdelayPID;break;
				case ONE_EDG_LN: if (autoFoundLeft || autoFoundRight)					autoHitTarget=INdelayPID;break;
				case TWO_EDG_LN: if (autoFoundLeft && autoFoundRight)					autoHitTarget=INdelayPID;break;
				case SCREEN_BTN: if (nLCDButtons)										autoHitTarget=INdelayPID;break;
			//	case FRONT_LINE: if (SenRightLine>RightLineFolPosi)						autoHitTarget=INdelayPID;break;
				default://nothing
				}
			}
		if (autoHitTarget==PID   && time1(T2)>=PID_WAIT_MS)							{autoHitTarget=NEXT;} //PID timeout
		if (time1(T1)>=INmaxTime && INmaxTime!=0)									{autoHitTarget=NEXT; autoStepStatus=MAX_TIMEOUT;} //Max Time timeout
		if (time1(T1)<=INminTime && autoHitTarget==NEXT	&& INendType!=TIME_LIMIT)	{autoStepStatus=MIN_TIMEOUT;} //Min Time timeout
		if (time1(T1)>=INminTime && autoHitTarget==NEXT)							{autoNextStep();} //Go to next step
		} // if (!RESET_AUTO)
	autoStepCheck++;
	}


void processAutonomous()
	{
	if (sysError==ERR_NONE)
		{
		autoStepCheck = 0;
		switch (autoRoutine.curr) //Scripts
			{
			case -2: scriptEmpty();		break;
			case -1: scriptDescore();	break;
			}
		if (sysState.curr == AUTONOMOUS)
			{
			switch (autoRoutine.curr) //Scripts
				{
				case 1: autoTest();	break; //2
				case 2: scriptEmpty();	break;
				case 3: scriptEmpty();	break;
				}
			}
#ifdef FULL_DEBUG_STREAM
		if (autoRoutine.curr==0)
			writeDebugStreamLine("no routine");
#endif
		}
	else
		{
		zeroMotors(); //If there is an error (low battery) then beep and stop.
		}
	}
