//Constants
static const int MIN_LOOP_MS = 5;
static const int JOYSTICK_DEAD_ZONE = 10;

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
	setStepInt(&senGyro);
	setStepInt(&senLeftQSE);
	setStepInt(&senRightQSE);
	setStepInt(&senLeftUS);
	setStepInt(&senRightUS);
	}

/* This function sets the last-step values to the
current-step values and saves them for when the
current-step values are overwritten.
*/
void setAllLasts()
	{
	setLCDLasts();
	setOperatorLasts();

	//--Sensors--//
	setLastInt(&senGyro);
	setLastInt(&senLeftQSE);
	setLastInt(&senRightQSE);
	setLastInt(&senLeftUS);
	setLastInt(&senRightUS);

	//--System--//
	setLastInt(&sysState);
	setLastInt(&autoRoutine);
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


/* This function takes a min, and max value, and
a pointer to a variable. The variable is changed
so that it is no smaller than the min value, and
no larger than the max value.
*/
void capIntValue(int min,int &value,int max)
	{
	int temp = value;
	temp = (temp<min) ? (min):(temp);
	temp = (temp>max) ? (max):(temp);
	value = temp; //not sure if this is ok
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
	capIntValue(0, n, INMaxVal-1);
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
	capIntValue(-127, INraw, 127);				//Make sure the numbers are within desired range
	return (INraw);
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
	//if (timerRobotIdle>=60000)		sysError = ERR_ROBOT_IDLE;
	if (nAvgBatteryLevel<1000)		sysError = ERR_LOW_CORTEX;
#endif
	}


void updateBatteryString(void)
	{
	StringFormat(batteryLevel[0], "Main:%1.2f | Powe", (float)nAvgBatteryLevel/1000);
	StringFormat(batteryLevel[1], "r Expander:%1.2f ", (float)senPwrExpVoltage/70);		//70 45.6 280 or 182.4
	StringFormat(batteryLevel[2], "| Backup:%1.2f | ", (float)BackupBatteryLevel/1000);
	}


/* This function returns the delta for the
emulated quadrature shaft encoder with the given
speed of a wheel.
*/
int emulateWheelQSE(int INspeed)
	{
	return ( (float) INspeed * timerEmulateSpeed / (127 * 2) );
	}


/* This function returns the delta for the
emulated potentiometer position with the given
speed and gearing of a lift.
 INgearing needs a 5 if the gearing is 1:5, a 7
if the gearing is 1:7, etc.
*/
int emulateLiftPot(int INspeed, int INgearing)
	{
	return ( (float) INspeed * timerEmulateSpeed / (25*INgearing) );
	}


/* These functions are for the LC types.
(Last-Current types.)
*/
bool changedBool(T_LC_BOOL INLC)
	{ //Returns true if the boolean changed
	return (INLC.last != INLC.curr);
	}

bool changedInt(T_LC_INT INLC)
	{ //Returns true if the integer changed
	return (INLC.last != INLC.curr);
	}

bool pressed(T_LC_BOOL INLC)
	{ //Returns true if it was just pressed
	return (!INLC.last && INLC.curr);
	}

int diffLastInt(T_LC_BOOL INLC)
	{ //Returns the difference of last and current value
	return (INLC.curr - INLC.last);
	}

int diffStepInt(T_LC_INT INLC)
	{ //Returns the difference of step starting and current value
	return (INLC.stepStart - INLC.last);
	}

void setLastBool(T_LC_BOOL *INLC)
	{ //Sets the last value to the current value
	INLC->last = INLC->curr;
	}

void setLastInt(T_LC_INT *INLC)
	{ //Sets the last value to the current value
	INLC->last = INLC->curr;
	}

void setLastString(T_LC_STRING *INLC)
	{ //Sets the last value to the current value
	INLC->last = INLC->curr;
	}

void setStepInt(T_LC_INT *INLC)
	{ //Sets the step start value to the current value
	INLC->stepStart = INLC->curr;
	}

/*void setToZeroBool(T_LC_BOOL *INLC)
	{ //Sets the step start value to the current value
	INLC->last = false;
	INLC->curr = false;
	}*/

void setToZeroInt(T_LC_INT *INLC)
	{ //Sets the step start value to the current value
	INLC->last = 0;
	INLC->curr = 0;
	}

void fixIrregularityInt(T_LC_INT *INLC, int INnum)
	{
	INLC->curr += slew(INLC->curr, INLC->last, INnum);
	}

int InchesToTicks(int n)
	{
	return ((float)n*360/(3.14*4));
	}
