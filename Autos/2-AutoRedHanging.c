//AutoRedHanging.c
//500 = 1 tile (2 ft)

void autoRedHang1(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(enc1(500),		0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//Forward, intake
	auto(enc1(-500),	0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//Reverse
	auto(gyro2(-90),	0,		0,			0,	0,	0,	DRIV_READY,	PID);	//turn 90
	auto(enc1(1020),	0,		0,			0,	0,	0,	DRIV_READY,	PID);	//Forward, push
	auto(gyro2(-90),	0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	PID);	//Turn 90
	auto(straight(30),	0,		lPre(BAR),	OUT,0,	0,	TIME_LIMIT,	1800);	//Dump
	auto(enc1(900),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	PID);	//Forward
	auto(stopped(),		0,		lPre(GND),	0,	0,	0,	LIFT_READY,	NEXT);	//Drop lift
	autoResetEnd();
	}
