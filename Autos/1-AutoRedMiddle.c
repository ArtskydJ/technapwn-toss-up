//AutoRedMiddle.c

void autoRedMid1(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,		Intk,Cata,End Type,	Other
	auto(straight(HALF),0,		0,			IN,	0,	TIME_LIMIT,	250);	//Intake pre
	auto(stopped(),				lPre(BAR),	IN,	0,	TIME_LIMIT,	1200);	//Lift Up
	auto(straight(HALF),0,		lPre(BAR),	0,	0,	TIME_LIMIT,	800);	//Lift Up + hit ball 1
	auto(straight(REV),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	550);	//reverse
	auto(gyro2(90),		0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn right
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	850);	//fwd
	auto(gyro2(-90),	0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn left
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	400);	//forward + hit ball 2
	auto(stopped(),				lPre(BAR),	OUT,0,	TIME_LIMIT,	700);	//Lift Down
	auto(straight(REV),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	300);	//Back away from barrier
	auto(gyro2(-160),	0,		lPre(GND),	0,	0,	DRIV_READY,	PID);	//turn left
	autoResetEnd();
	}


void autoRedMid2(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,		Intk,Cata,End Type,	Other
	auto(straight(FWD),	0,		0,			IN,	1,	TIME_LIMIT,	950);	//Intake pre, Hit ball 1
	auto(straight(REV),	0,		0,			0,	0,	TIME_LIMIT,	600);	//Reverse
	auto(gyro2(30),		0,		0,			0,	0,	DRIV_READY,	PID);	//turn right
	auto(straight(FWD),	0,		0,			0,	0,	TIME_LIMIT,	1000);	//Forward
	auto(straight(HALF),0,		lPre(STS),	0,	0,	TIME_LIMIT,	600);	//Forward + Lift
	auto(stopped(),				lPre(STS),	0,	0,	TIME_LIMIT,	1000);	//Lift
	auto(0,		FWD,	0,		lPre(STS),	0,	0,	TIME_LIMIT,	450);	//Turn
	auto(HALF,	HALF,	0,		lPre(STS),	OUT,0,	TIME_LIMIT,	1000);	//fwd + dump
	auto(-90,	REV,	0,		0,			0,	0,	TIME_LIMIT,	900);	//Reverse
	auto(stopped(),				lPre(GND),	0,	0,	TIME_LIMIT,	1200);	//Drop lift
	auto(straight(REV),	0,		lPre(GND),	0,	0,	TIME_LIMIT,	1200);	//Reverse + drop lift
	auto(gyro2(25),		0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn right 35 deg + lift
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	650);	//Forward
	auto(straight(REV),	0,		0,			0,	0,	TIME_LIMIT,	650);	//Reverse
	auto(gyro2(145),	0,		lPre(GND),	0,	0,	DRIV_READY,	PID);	//turn right 145 deg + drop lift
	autoResetEnd();
	}
