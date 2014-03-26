//AutoBlueMiddle.c
//500 = 1 tile (2 ft)

void autoBlueMid1(void) //Tested and working on 2014-03-25
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(straight(HALF),0,		0,			IN,	0,	0,	TIME_LIMIT,	250);	//Intake pre
	auto(stopped(),		0,		lPre(BAR),	IN,	0,	0,	TIME_LIMIT,	1200);	//Lift Up
	auto(straight(HALF),0,		lPre(BAR),	0,	0,	0,	TIME_LIMIT,	800);	//Lift Up + hit ball 1
	auto(straight(REV),	0,		lPre(BAR),	0,	0,	0,	TIME_LIMIT,	550);	//reverse
	auto(gyro2(-90),	0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	PID);	//turn right
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	0,	TIME_LIMIT,	850);	//fwd
	auto(gyro2(90),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	PID);	//turn left
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	0,	TIME_LIMIT,	400);	//forward + hit ball 2
	auto(stopped(),		0,		lPre(BAR),	OUT,0,	0,	TIME_LIMIT,	700);	//Lift Down
	auto(straight(REV),	0,		lPre(BAR),	0,	0,	0,	TIME_LIMIT,	300);	//Back away from barrier
	auto(stopped(),		0,		lPre(GND),	0,	0,	0,	TIME_LIMIT,	1000);	//lower lift
	autoResetEnd();
	}


void autoBlueMid2(void) //Tested and working on 2014-03-25
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(enc1(600),		0,		lPre(BAR),	IN,	0,	0,	DRIV_READY,	PID);	//Intake pre, Hit ball 1
	auto(enc1(-400),	0,		30,			0,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(stopped(),usStrfR(100),30,			0,	0,	0,	DRIV_READY,	PID);	//strafe
	auto(straight(HALF),0,		30,			0,	0,	0,	TIME_LIMIT,	1100);	//Forward
	auto(enc1(-600),	0,		0,			0,	0,	0,	DRIV_READY,	PID);	//Reverse
	auto(stopped(),usStrfR(66),	lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//strafe + drop
	auto(enc1(600),		0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Forward
	auto(stopped(),		LEFT,	lPre(GND),	0,	0,	0,	TIME_LIMIT,	800);	//strafe into tower
	auto(spd(0,HALF),	RIGHT,	lPre(GND),	0,	0,	0,	TIME_LIMIT,	300);	//strafe away
	auto(enc1(300),		0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Forward
	auto(straight(80),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	1700);	//Fwd + lift
	auto(straight(-100),0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	200);	//Rev
	auto(stopped(),		0,		lPre(STS),	OUT,0,	0,	TIME_LIMIT,	1200);	//DUMP OUT 3 RED BUCKY
	auto(enc1(-300),	0,		0,			0,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(enc1(-1600),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse + drop lift
	autoResetEnd();
	}
