//AutoBlueMiddle.c

void autoBlueMid1(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,		Intk,Cata,End Type,	Other
	auto(straight(HALF),0,		0,			IN,	0,	TIME_LIMIT,	250);	//Intake pre
	auto(stopped(),				lPre(BAR),	IN,	0,	TIME_LIMIT,	1200);	//Lift Up
	auto(straight(HALF),0,		lPre(BAR),	0,	0,	TIME_LIMIT,	800);	//Lift Up
	auto(straight(REV),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	400);	//reverse
	auto(gyro2(-90),	0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn right
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	700);	//fwd
	auto(gyro2(90),		0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn left
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	300);	//forward & hit ball 2
	auto(gyro2(20),		0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn left
	auto(stopped(),				lPre(BAR),	OUT,0,	TIME_LIMIT,	700);	//Lift Down
	auto(straight(REV),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	500);	//Back away from barrier
	auto(stopped(),				lPre(GND),	0,	0,	TIME_LIMIT,	1000);	//Lift Down
	autoResetEnd();
	}


void autoBlueMid2(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,		Intk,Cata,End Type,	Other
	auto(straight(FWD),	0,		0,			IN,	1,	TIME_LIMIT,	1000);	//Intake pre, Hit ball 1
	auto(straight(REV),	0,		0,			0,	0,	TIME_LIMIT,	600);	//Reverse
	auto(gyro2(-25),	0,		0,			0,	0,	DRIV_READY,	PID);	//turn left 25 deg
	auto(straight(FWD),	0,		0,			0,	0,	TIME_LIMIT,	900);	//Forward
	auto(straight(HALF),0,		lPre(STS),	0,	0,	TIME_LIMIT,	300);	//Forward + Lift
	auto(stopped(),				lPre(STS),	0,	0,	TIME_LIMIT,	1300);	//Lift
	auto(90,	40,		0,		lPre(STS),	0,	0,	TIME_LIMIT,	1200);	//Forward
	auto(90,	40,		0,		lPre(STS),	OUT,0,	TIME_LIMIT,	400);	//dump
	auto(REV,	-90,	0,		0,			0,	0,	TIME_LIMIT,	700);	//Reverse
	auto(stopped(),				lPre(GND),	0,	0,	TIME_LIMIT,	1300);	//Drop lift
	auto(straight(REV),	0,		lPre(GND),	0,	0,	TIME_LIMIT,	1100);	//Reverse + drop lift
	auto(gyro2(-35),	0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn left 35 deg + lift
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	500);	//Forward
	auto(straight(REV),	0,		0,			0,	0,	TIME_LIMIT,	500);	//Reverse
	auto(gyro2(-145),	0,		lPre(GND),	0,	0,	DRIV_READY,	PID);	//turn left 145 deg + drop lift
	autoResetEnd();
	}
