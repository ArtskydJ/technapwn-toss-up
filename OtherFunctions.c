//Functions
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
int capIntValue(int min, int value, int max)
	{
	if (value < min) value = min;
	if (value > max) value = max;
	return value;
	}

	
/* This function calculates the proportional,
integral and derivative values for the specified
T_PID values. (See Definitions.c for T_PID.)
*/
int updatePIDController(T_PID &INPID, int INerror)
	{
	INPID.error.curr = INerror;
	INPID.integral = (INPID.integral * 4 / 5) + INPID.error.curr;
	INPID.derivative = INPID.error.curr - INPID.error.last;
	setLastInt(INPID.error);
	INPID.output = (float)(INPID.error.curr	* INPID.kp)
						+ (INPID.integral	* INPID.ki)
						+ (INPID.derivative	* INPID.kd);
	return (INPID.output);
	}


/* These functions are for the LC types.
(Last-Current types.)
*/
bool changedBool(T_LC_BOOL INLC) //{returns true if the boolean changed
	{return (INLC.last != INLC.curr);}

bool changedInt(T_LC_INT INLC) //{returns true if the integer changed
	{return (INLC.last != INLC.curr);}

bool pressed(T_LC_BOOL INLC) //{returns true if it was just pressed
	{return (!INLC.last && INLC.curr);}

int diffLastInt(T_LC_BOOL INLC) //{returns the difference of last and current value
	{return (INLC.curr - INLC.last);}

int diffStepInt(T_LC_INT INLC) //{returns the difference of step starting and current value
	{return (INLC.stepStart - INLC.last);}

void setLastBool(T_LC_BOOL *INLC) //Sets the last value to the current value
	{INLC->last = INLC->curr;}

void setLastInt(T_LC_INT *INLC) //Sets the last value to the current value
	{INLC->last = INLC->curr;}

void setLastString(T_LC_STRING *INLC) //Sets the last value to the current value
	{INLC->last = INLC->curr;}

void setStepInt(T_LC_INT *INLC) //Sets the step start value to the current value
	{INLC->stepStart = INLC->curr;}

/*void setToZeroBool(T_LC_BOOL *INLC) //Sets the step start value to the current value
	{INLC->last = false;
	INLC->curr = false;}*/

void setToZeroInt(T_LC_INT *INLC)
	//Sets the step start value to the current value
	{INLC->last = 0;
	INLC->curr = 0;}

void slewLCInt(T_LC_INT *INLC, int INnum)
	{
	int diff = INLC->curr - INLC->last;
	if		(diff > INnum) diff = INnum;
	else if (diff < -INnum) diff = -INnum;
	
	INLC->curr += diff;
	}
