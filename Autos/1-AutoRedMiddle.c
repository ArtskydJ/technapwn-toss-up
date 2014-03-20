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
	auto(enc1(600),		0,		lPre(BAR),	IN,	0,	DRIV_READY,	PID);	//Intake pre, Hit ball 1
	auto(enc1(-400),	0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//Reverse
	auto(0,	0,	usStrfL(100),	lPre(BAR),	0,	0,	DRIV_READY,	PID);	//strafe
	auto(straight(HALF),0,		lPre(BAR),	0,	0,	TIME_LIMIT,	1100);	//Forward
	auto(enc1(-500),	0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//Reverse
	auto(0,	0,	usStrfL(68),	lPre(GND),	0,	0,	DRIV_READY,	PID);	//strafe + drop
	auto(enc1(1100),	0,		lPre(GND),	0,	0,	DRIV_READY,	PID);	//Forward
	auto(stopped(),				lPre(STS),	0,	0,	TIME_LIMIT,	1000);	//Lift
	auto(straight(FWD),0,		lPre(STS),	0,	0,	TIME_LIMIT,	600);	//fwd
	auto(stopped(),				lPre(STS),	OUT,0,	TIME_LIMIT,	1000);	//fwd + dump
	auto(enc1(-300),	0,		0,			0,	0,	DRIV_READY,	NEXT);	//Reverse
	//auto(stopped(),				lPre(GND),	0,	0,	TIME_LIMIT,	700);	//Wait, Drop lift
	auto(enc1(-1600),	0,		lPre(GND),	0,	0,	DRIV_READY,	PID);	//Reverse + drop lift
	auto(gyro2(145),	0,		lPre(GND),	0,	0,	DRIV_READY,	PID);	//turn right 145 deg + drop lift
	autoResetEnd();
	}


void autoRedMid3(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,		Intk,Cata,End Type,	Other
	auto(stopped(),				HALF,		IN,	0,	TIME_LIMIT,	100);	//lift
	auto(0,	0,	usStrfR(110),	5,			IN,	0,	DRIV_READY,	PID);	//strafe
	auto(gyro2(180),	0,		5,			0,	0,	DRIV_READY,	PID);	//turn right

	autoResetEnd();
	}
