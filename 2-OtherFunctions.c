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

//This function turns 2 motor values into 1 coded value
unsigned int encode(int l, int r)
	{
	ubyte tL = capIntValue(REV, l, FWD) + FWD;
	ubyte tR = capIntValue(REV, r, FWD) + FWD;
	return (tL<<8) + tR;
	}

//This function turns the first coded value back to the original value
int decodeL(unsigned int n)
	{
	unsigned int temp = (n >> 8);
	temp = (temp & 255); //255 = 2^8 = 0000000011111111
	temp = capIntValue(0, temp, 254);
	return temp - 127;
	}

//This function turns the second coded value back to the original value
int decodeR(unsigned int n)
	{
	unsigned int temp = (n & 255); //255 = 2^8 = 0000000011111111
	temp = capIntValue(0, temp, 254);
	return temp - 127;
	}

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



//Autonomous Calculation Functions
//Do not confuse encode() with an encoder!
//----------STRAFE----------
int usStrfL(int n) //Strafe to Left Ultrasonic setpoint
	{ return (n-senLeftUS.curr)*US_STRF_P; }

int usStrfR(int n) //Strafe to Right Ultrasonic setpoint
	{ return (senRightUS.curr-n)*US_STRF_P; }

int encStrf1(int n) //Strafe to Left Encoder setpoint
	{ return (n + (senLeftQSE.curr + senLeftQSE.curr)/2) * ENC_STRF_P; }

//----------DRIVE----------
unsigned int spd(int n, int m) //Separate sides different power
	{ return encode(n,m); }

unsigned int stopped() //Don't move forward or reverse
	{ return encode(0, 0); }

unsigned int straight(int n) //Both sides same power
	{ return encode(n, n); }

unsigned int turn2(int n) //Both sides turn power
	{ return encode(n, -n); }

unsigned int turnL(int n) //Left side turn power
	{ return encode(n, 0); }

unsigned int turnR(int n) //Right side turn power
	{ return encode(0, n); }

unsigned int gyroL(int n) //Left side turn gyro
	{ return encode((n*10 - senGyro.curr)*GYRO_P*2, 0); }

unsigned int gyroR(int n) //Right side turn gyro
	{ return encode(0, -(n*10 - senGyro.curr)*GYRO_P*2); }

unsigned int gyro2(int n) //Both sides turn gyro
	{ return encode(
		(n*10 - senGyro.curr)*GYRO_P,
		-(n*10 - senGyro.curr)*GYRO_P); }

unsigned int enc(int n, int m) //Individual sides encoders
	{ return encode(
		(n-senLeftQSE.curr)*ENC_DRV_P,
		(m-senRightQSE.curr)*ENC_DRV_P); }

unsigned int enc1(int n) //Both sides, one target, two encoders
	{ return encode(
		(n-senLeftQSE.curr)*ENC_DRV_P,
		(n-senRightQSE.curr)*ENC_DRV_P); }

unsigned int enc1Spd(int n, int m) //Both sides, one target, two encoders, custom speed
	{
	/*int tL =
	int tR =*/ return encode(
		capIntValue(-abs(m), (n-senLeftQSE.curr)*ENC_DRV_P, abs(m)),
		capIntValue(-abs(m), (n-senRightQSE.curr)*ENC_DRV_P, abs(m))); }

//----------ULTRASONIC FOLLOW----------
unsigned int usFllwL(int n, int m) //Follow left wall a set distance with left ultrasonic
	{ return encode(
		n - ((float)senLeftUS.curr-m)* US_FLLW_P,
		n + ((float)senLeftUS.curr-m)* US_FLLW_P); }

unsigned int usFllwR(int n, int m) //Follow right wall a set distance with right ultrasonic
	{ return encode(
		n + ((float)senRightUS.curr-m)*US_FLLW_P,
		n - ((float)senRightUS.curr-m)*US_FLLW_P); }

unsigned int usFllwNowL(int n) //Follow left wall at starting distance with left ultrasonic
	{ return encode(
		(n - ((float)diffStepInt(senLeftUS))* US_FLLW_P),
		(n + ((float)diffStepInt(senLeftUS))* US_FLLW_P)); }

unsigned int usFllwNowR(int n) //Follow right wall at starting distance with right ultrasonic
	{ return encode(
		n + ((float)diffStepInt(senRightUS))*US_FLLW_P,
		n - ((float)diffStepInt(senRightUS))*US_FLLW_P); }
