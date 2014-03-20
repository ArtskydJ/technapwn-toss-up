//OtherFunctions.c

//Functions
/* This function keeps the loop time of the code constant. The value MIN_LOOP_MS
is the minimum time the loop will take to iterate with it being constant. If the
iteration takes longer than the minimum, then no delay is executed. If the
iteration is faster, than a delay is applied.
 To check how long an iteration normally takes, define MIN_LOOP_MS as 0. Then,
in the debugger, watch sysLooptime.
*/
void constantLoopTime()
	{
	while (time1[T4] < MIN_LOOP_MS)
		{}
	ClearTimer(T4);
	}


/* This function takes a min, and max value, and a pointer to a variable. The
variable is changed so that it is no smaller than the min value, and no larger
than the max value.
*/
int capIntValue(int min, int value, int max)
	{
	if (value < min) value = min;
	if (value > max) value = max;
	return value;
	}


/*This function returns a reversed value for pots
that were installed so that the number goes up
when the arm goes down, etc.
*/
int potReverse(int INpot)
	{
	return (4095-INpot);
	}


/* This function calculates the proportional, integral and derivative values for
the specified T_PID values. (See DefinitionsAndDeclarations.c for T_PID.)
*/
int updatePIDController(T_PID &INPID, int INerror)
	{
	INPID.error.curr = INerror;
	INPID.integral = (INPID.integral * 4 / 5) + INPID.error.curr;
	INPID.derivative = INPID.error.curr - INPID.error.last;
	setLastInt(&INPID.error); //have not tested with ampersand (&)
	INPID.output = (float)(INPID.error.curr	* INPID.kp)
						+ (INPID.integral	* INPID.ki)
						+ (INPID.derivative	* INPID.kd);
	return (INPID.output);
	}


/* This function gets the target motor value, the
previously assigned motor value, and the slew.
*/
int slew(int INtargetValue, int INlastValue, int INslew)
	{
	return capIntValue(-abs(INslew), INtargetValue-INlastValue, abs(INslew));
	}


/* This function returns the delta for the
emulated quadrature shaft encoder with the given
speed of a wheel.
*/
int emulateWheelQSE(int INtimer, int INspeed)
	{
	return ( (float) INspeed * INtimer / (FWD * 2) );
	}


/* This function returns the delta for the
emulated potentiometer position with the given
speed and gearing of a lift.
 INgearing needs a 5 if the gearing is 1:5, a 7
if the gearing is 1:7, etc.
*/
int emulateLiftPot(int INtimer, int INspeed, int INgearing)
	{return (abs(INspeed)>30) ? ((float) INspeed*INtimer / (25*INgearing)) : 0;
	}


/* This function returns the delta for the
emulated gyroscope with the given speed of the
left and right sides.
*/
int emulateGyro(int INtimer, int INleft, int INright)
	{
	INleft =  (abs(INleft)>FWD)  ? sgn(INleft)*FWD  : INleft;
	INright = (abs(INright)>FWD) ? sgn(INright)*FWD : INright;
	return ( (float) INleft - INright ) * INtimer / ( FWD * 2 );
	}


/* These functions are for the LC types. (Last-Current types.)
*/
bool changedBool(T_LC_BOOL INLC) //Returns true if the boolean changed
	{return (INLC.last != INLC.curr);}

bool changedInt(T_LC_INT INLC) //Returns true if the integer changed
	{return (INLC.last != INLC.curr);}

bool changedString(T_LC_STRING INLC) //Returns true if the string changed
	{return strcmp(INLC.last, INLC.curr)==0;}

bool pressed(T_LC_BOOL INLC) //Returns true if it was just pressed
	{return (!INLC.last && INLC.curr);}

int diffLastInt(T_LC_BOOL INLC) //Returns the difference of last and current value
	{return (INLC.curr - INLC.last);}

int diffStepInt(T_LC_INT INLC) //Returns the difference of step starting and current value
	{return (INLC.stepStart - INLC.curr);}

void setLastBool(T_LC_BOOL *INLC) //Sets the last value to the current value
	{INLC->last = INLC->curr;}

void setLastInt(T_LC_INT *INLC) //Sets the last value to the current value
	{INLC->last = INLC->curr;}

void setLastString(T_LC_STRING *INLC) //Sets the last value to the current value
	{INLC->last = INLC->curr;}

void setStepInt(T_LC_INT *INLC) //Sets the step start value to the current value
	{INLC->stepStart = INLC->curr;}

/*void setToZeroBool(T_LC_BOOL *INLC) //Sets the last and current values to 0
	{INLC->last = false;
	INLC->curr = false;}*/

void setToZeroInt(T_LC_INT *INLC) //Sets the last and current values to 0
	{INLC->last = 0;
	INLC->curr = 0;}

void slewLCInt(T_LC_INT *INLC, int INnum)
	{
	int diff = INLC->curr - INLC->last;
	if		(diff > INnum) diff = INnum;
	else if (diff < -INnum) diff = -INnum;
	INLC->curr += diff;
	}
