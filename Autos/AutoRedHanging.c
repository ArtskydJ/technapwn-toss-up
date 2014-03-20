//AutoRedHanging.c

void autoRedHang1(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,		Intk,Cata,End Type,	Other
	auto(straight(HALF),0,		0,			IN,	0,	TIME_LIMIT,	1100);	//Forward, intake
	auto(straight(-30),	0,		0,			IN,	0,	TIME_LIMIT,	200);	//intake more
	auto(gyro2(-90),	0,		0,			0,	0,	DRIV_READY,	PID);	//turn left
	auto(straight(FWD),	0,		0,			0,	0,	TIME_LIMIT,	450);	//Forward
	auto(gyro2(-90),	0,		0,			0,	0,	DRIV_READY,	PID);	//turn left
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	400);	//Forward
	auto(gyro2(30),		0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn 30 deg right
	auto(stopped(),				0,			OUT,0,	TIME_LIMIT,	1300);	//dump
	auto(gyro2(90),		0,		0,			0,	0,	DRIV_READY,	PID);	//turn right
	auto(straight(FWD),	0,		lPre(GND),	0,	0,	TIME_LIMIT,	900);	//Forward
	auto(gyro2(-60),	0,		lPre(GND),	0,	0,	DRIV_READY,	PID);	//turn 60 deg left
	auto(straight(FWD),	0,		10,			0,	0,	TIME_LIMIT,	300);	//Forward
	auto(turn2(20),		LEFT,	10,			0,	0,	TIME_LIMIT,	1700);	//Strafe and slightly turn right
	autoResetEnd();
	}
