//AutoBlueHanging.c
//500 = 1 tile (2 ft)

void autoBlueHang1(void) //Working as of the Iowa State Championship
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(enc1(500),		0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//Forward, intake
	auto(enc1(-500),	0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//Reverse
	auto(gyro2(90),		0,		0,			0,	0,	0,	DRIV_READY,	PID);	//turn 90
	auto(enc1(1020),	0,		0,			0,	0,	0,	DRIV_READY,	PID);	//Forward, 1020
	auto(gyro2(90),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	PID);	//Turn 90
	auto(straight(30),	0,		lPre(BAR),	OUT,0,	0,	TIME_LIMIT,	1800);	//Dump
	auto(enc1(1500),	0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//Forward
	auto(straight(HALF),0,		lPre(BAR),	0,	0,	0,	TIME_LIMIT,	500);	//Forward
	auto(enc1(-500),	0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(gyro2(-30),	0,		lPre(GND),	0,	0,	0,	FULL_READY,	PID);	//Drop lift, turn
	auto(enc1(1100),	0,		lPre(GND),	OUT,0,	0,	DRIV_READY,	NEXT);	//Forward
	autoResetEnd();
	}


void autoBlueHang2(void) //Not yet tested (should work; this is a mirror of the red version)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(enc1(500),		0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//Forward, intake
	auto(enc1(-180),	0,		0,			IN,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(gyro2(-45),	0,		0,			0,	0,	0,	DRIV_READY,	PID);	//turn
	auto(enc1(-760),	0,		0,			0,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(gyro2(-135),	0,		lPre(BMP),	0,	0,	0,	DRIV_READY,	PID);	//Turn
	auto(enc1(1000),	0,		lPre(BMP),	0,	0,	0,	DRIV_READY,	NEXT);	//Fwd over bump
	auto(enc1(1000),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Fwd over bump
	auto(stopped(),		LEFT,	lPre(GND),	0,	0,	0,	TIME_LIMIT,	850);	//strafe into tower
	auto(spd(0,85),		RIGHT,	lPre(GND),	0,	0,	0,	TIME_LIMIT,	380);	//strafe away
	auto(enc1(300),		0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Fwd
	auto(straight(HALF),0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	1600);	//Fwd + lift
	auto(straight(-100),0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	200);	//Rev
	auto(stopped(),		0,		lPre(STS),	OUT,0,	0,	TIME_LIMIT,	2000);	//Dump

	//usStrfL(100)
	autoResetEnd();
	}
