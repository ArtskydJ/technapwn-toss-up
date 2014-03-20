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


void autoRedHang2(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(enc1(500),		0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//Forward, intake
	auto(enc1(-150),	0,		0,			IN,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(gyro2(-90),	0,		0,			0,	0,	0,	DRIV_READY,	PID);	//turn 90
	auto(enc1(1550),	0,		0,			0,	0,	0,	DRIV_READY,	NEXT);	//Forward, 1020
	auto(gyro2(-90),	0,		0,			0,	0,	0,	DRIV_READY,	PID);	//Turn 90
	auto(enc1(1700),	0,		lPre(GND),	IN,	0,	0,	DRIV_READY,	NEXT);	//Fwd over bump
	auto(straight(50),0,		lPre(BMP),	0,	0,	0,	TIME_LIMIT,	550);	//Fwd into barrier
	auto(stopped(),		0,		lPre(GND),	0,	0,	0,	TIME_LIMIT,	200);	//drop lift
	auto(enc1(100),		0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Fwd under barrier
	auto(stopped(),	usStrfR(30),0,			0,	0,	0,	DRIV_READY,	NEXT);	//Strafe
	auto(enc1(600),		0,		0,			0,	0,	0,	DRIV_READY,	NEXT);	//Forward
	auto(spd(0,0),encStrf1(900),lPre(STS),	0,	0,	0,	DRIV_READY,	NEXT);	//Strafe
	auto(straight(FWD),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	500);	//Forward
	auto(straight(-20),	0,		lPre(STS),	OUT,0,	0,	TIME_LIMIT,	1000);	//Dump

	//usStrfL(100)
	autoResetEnd();
	}
