//AutoRedHanging.c

void autoRedHang1(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,		Intk,Cata,End Type,	Other
	auto(straight(50),	0,		0,			IN,	0,	TIME_LIMIT,	1300);	//Forward, intake
	auto(straight(-30),	0,		0,			IN,	0,	TIME_LIMIT,	300);	//intake more
	auto(gyro2(-180),	0,		0,			IN,	0,	DRIV_READY,	PID);	//turn 180
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	500);	//Forward
	auto(stopped(),				lPre(BAR),	OUT,0,	TIME_LIMIT,	1000);	//dump
	auto(straight(REV),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	750);	//Backward
	auto(gyro2(90),		0,		lPre(GND),	0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		lPre(GND),	0,	0,	TIME_LIMIT,	500);	//Forward
	auto(gyro2(120),	0,		lPre(GND),	0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(REV),	0,		lPre(GND),	0,	0,	TIME_LIMIT,	700);	//Forward
	auto(stopped(),				10,			OUT,0,	TIME_LIMIT,	1800);	//dump
	autoResetEnd();
	}
