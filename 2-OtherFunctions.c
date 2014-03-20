//OtherFunctions.c

//Functions
//This function keeps the main loop time of the code constant. It does this by
//waiting after each loop iteration until x milliseconds have passed since it
//started the loop iteration. (E.g. Start loop, do stuff, wait, repeat.)
void constantLoopTime()
	{
	while (time1[T4] < MIN_LOOP_MS)
		{}
	ClearTimer(T4);
	}


//This function forces the target between min and max. For example:
//capIntValue(3,1,7) == 3 | capIntValue(3,19,7) == 7 | capIntValue(3,5,7) == 5
int capIntValue(int min, int value, int max)
	{
	if (value < min) value = min;
	if (value > max) value = max;
	return value;
	}


//This function returns a reversed value for pots that were installed backwards.
int potReverse(int INpot)
	{ return (4095-INpot); }


//This function calcs a new motor value with target, previous, and slew values.
//E.g. slew(100, 0, 5) == 5 | slew(100, 15, 5) == 20 | slew(-100,-80,5) == -85
int slew(int INtargetVal, int INlastVal, int INslew)
	{ return (INlastVal + capIntValue(-INslew, INtargetVal-INlastVal, INslew)); }

/*int slew(int INtargetVal, int INlastVal, int INslew)
	{ return capIntValue(-abs(INslew), INtargetVal-INlastVal, abs(INslew)); }*/


//This function returns the delta for the emulated quadrature shaft encoder
//with the given speed of a wheel.
int emulateWheelQSE(int INtimer, int INspeed)
	{ return ( (float) INspeed * INtimer / (FWD * 2) ); }


//This function returns the delta for the emulated potentiometer position with
//the given speed and gearing of a lift. INgearing needs 5 if the gearing is 1:5,
//a 7 if the gearing is 1:7, etc.

int emulateLiftPot(int INtimer, int INspeed, int INgearing)
	{ return (abs(INspeed)>30) ? ((float) INspeed*INtimer / (25*INgearing)) : 0; }


//This function returns the delta for the emulated gyroscope with the given
//speed of the left and right sides.
int emulateGyro(int INtimer, int INleft, int INright)
	{
	INleft =  capIntValue(REV, INleft,  FWD);
	INright = capIntValue(REV, INright, FWD);
	return ( (float) INleft - INright ) * INtimer / ( FWD * 2 );
	}


//These functions are for the LC types. (Last-Current types)
bool changedBool(T_LC_BOOL INLC) //Returns true if the boolean changed
	{ return (INLC.last != INLC.curr); }

bool changedInt(T_LC_INT INLC) //Returns true if the integer changed
	{ return (INLC.last != INLC.curr); }

bool changedString(T_LC_STRING INLC) //Returns true if the string changed
	{ return strcmp(INLC.last, INLC.curr)==0; }

bool pressed(T_LC_BOOL INLC) //Returns true if it was just pressed
	{ return (!INLC.last && INLC.curr); }

int diffLastInt(T_LC_BOOL INLC) //Returns the difference of last and current value
	{ return (INLC.curr - INLC.last); }

int diffStepInt(T_LC_INT INLC) //Returns the difference of step starting and current value
	{ return (INLC.stepStart - INLC.curr); }

void setLastBool(T_LC_BOOL *INLC) //Sets the last value to the current value
	{ INLC->last = INLC->curr; }

void setLastInt(T_LC_INT *INLC) //Sets the last value to the current value
	{ INLC->last = INLC->curr; }

void setLastString(T_LC_STRING *INLC) //Sets the last value to the current value
	{ INLC->last = INLC->curr; }

void setStepInt(T_LC_INT *INLC) //Sets the step start value to the current value
	{ INLC->stepStart = INLC->curr; }

void setToZeroInt(T_LC_INT *INLC) //Sets the last and current values to 0
	{ INLC->last = 0;
	INLC->curr = 0; }
