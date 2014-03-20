/* The following function is run every time the
autonomous step advances. It sets the starting
values of each sensor for that step, for checking
the difference between them.
 For example, the starting gyro value is stored.
When the robot turns, it calculates the differ-
ence between the current value and the step-start
value, so it knows how far it has turned.
*/
void setAutoStepsStarts()
	{
	//--Sensors--//
	setStep(senGyro);
	setStep(senLeftQSE);
	setStep(senRightQSE);
	setStep(senLeftUS);
	setStep(senRightUS);
	}

/* This function sets the last-step values to the
current-step values and saves them for when the
current-step values are overwritten.
*/
void setAllLasts()
	{
	//--Sensors--//
	setLast(senGyro);
	setLast(senLeftQSE);
	setLast(senRightQSE);
	setLast(senLeftUS);
	setLast(senRightUS);
	//--Buttons--//
	setLast(btnScreenLeft);
	setLast(btnScreenCenter);
	setLast(btnScreenRight);
	setLast(btnLiftUp);
	setLast(btnLiftDown);
	//--System--//
	setLast(sysState);
	setLast(autoRoutine);
	//--Other--//
	setLast(menuItem);
	setLast(topLCDLine);
	setLast(bottomLCDLine);
	}

/* This function keeps the loop time of the code
constant. The value MIN_LOOP_MS is the minimum
time the loop will take to iterate with it being
constant. If the iteration takes longer than the
minimum, then no delay is executed. If the
iteration is faster, than a delay is applied.
 To check how long an iteration normally takes,
define MIN_LOOP_MS as 0. Then, in the debugger,
watch sysLooptime.
*/
void constantLoopTime()
	{
	sysLooptime=time1[T4];
	while (time1[T4] < MIN_LOOP_MS)
		{}
	ClearTimer(T4);
	}

/* This function gets the target motor value, the
previously assigned motor value, and the slew.
*/
float slew(int INtargetValue, int INlastValue, float INslew)
	{
	int diff = INtargetValue-INlastValue;
	if		(diff >  INslew) diff = INslew;
	else if (diff < -INslew) diff =-INslew;
	return diff;
	}

/* This function checks how far the potentiometer
is turned and compares it to the max number
allowed. Then it returns the corresponding value.
 For example, if you want 10 numbers, then you
input 10 and it will return a number from 0 - 9,
depending on how far the potentiometer is turned.
*/
int potPosition(int INMaxVal)
	{
	int n=(float)INMaxVal*senSelectorPot/4096;
	capValue(0,n,INMaxVal-1);
	return n;
	}

/* This function is similar to potPosition, but
it returns 0, 1 or 2 depending on how close the
potentiometer is to a "border". 0 and 2 are
borders, while 1 is centered. This function only
returns the how far the pot is from a border, not
what number it is currently on.
*/
int potCentered(int INMaxVal)
	{
	int n=(float)3*INMaxVal*senSelectorPot/4096;
	return n%3;
	}

/* This function calculates the proportional,
integral and derivative values for the specified
T_PID values. (See Definitions.c for T_PID.)
*/
int updatePIDController(T_PID &INPID, int INerror)
	{
	INPID.error = INerror;
	INPID.integral = (INPID.integral * 4 / 5) + INPID.error;
	INPID.derivative = INPID.error - INPID.lastError;
	INPID.lastError = INPID.error;
	INPID.output = (float)(INPID.error		* INPID.kp)
						+ (INPID.integral	* INPID.ki)
						+ (INPID.derivative	* INPID.kd);
	return (INPID.output);
	}


/* This function takes the raw joystick value and
returns a scaled value.
*/
int joystickFilter(int INraw)
	{
	if (abs(INraw) < JOYSTICK_DEAD_ZONE)	//Dead Zone
		INraw=0;
	INraw = (float)INraw*abs(INraw)/127;	//Exponential function
	capValue(-127,INraw,127);				//Make sure the numbers are within desired range
	return (INraw);
	}


/* This function sets all motor targets to 0.
*/
void zeroMotors()
	{
	outLift = 0;
	outDrvX = 0;
	outDrvY = 0;
	outDrvZ = 0;
	for (int j=0; j<10; j++)
		mtrTarget[j] = 0;
	}

/* This function checks the voltage on the cortex
and power expander. It also checks if the robot
has been idle for over a minute. If one of these
is true, then sysError is set.
*/
void processErrors()
	{
#if (_TARGET=="Robot") //Gives the low battery error when emulated.
	sysError = ERR_NONE;
	//if (senPwrExpVoltage<7200)		sysError = ERR_LOW_POW_EX; //power expander voltage is not x1000
	#ifdef PRACTICE //Practice
		if (timerRobotIdle>=60000)		sysError = ERR_ROBOT_IDLE;
	#else
		if (nAvgBatteryLevel<7000)		sysError = ERR_LOW_CORTEX;
	#endif
#endif
	}

/* This function checks if the joysticks are
moved from their deadzones.
*/
bool joystickIsMoved(bool checkStkZ)
	{
	return (stkDrvX+stkDrvY+(stkDrvZ*checkStkZ))!=0;
	}
