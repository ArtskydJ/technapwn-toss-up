//AutoRedHanging.c
//500 = 1 tile (2 ft)

void autoRedHang1(void) //Working as of the Iowa State Championship
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Tranny,End Type,	Other
	auto(enc1(500),		0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//Forward, intake
	auto(enc1(-500),	0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//Reverse
	auto(gyro2(-90),	0,		0,			0,	0,	0,	DRIV_READY,	PID);	//turn 90
	auto(enc1(1020),	0,		0,			0,	0,	0,	DRIV_READY,	PID);	//Forward, push
	auto(gyro2(-90),	0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	PID);	//Turn 90
	auto(straight(30),	0,		lPre(BAR),	OUT,0,	0,	TIME_LIMIT,	1800);	//Dump
	auto(enc1(1500),	0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//Forward
	auto(straight(HALF),0,		lPre(BAR),	0,	0,	0,	TIME_LIMIT,	500);	//Forward
	auto(enc1(-550),	0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(gyro2(35),		0,		lPre(GND),	0,	0,	0,	FULL_READY,	PID);	//Drop lift, turn
	auto(enc1(1100),	0,		lPre(GND),	OUT,0,	0,	DRIV_READY,	NEXT);	//Forward
	autoResetEnd();
	}


void autoRedHang2(void) //Working as of 2014-03-31
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Tranny,End Type,	Other
	auto(straight(50),	0,		0,			IN,	0,	0,	TIME_LIMIT,	150);	//fwd
	auto(enc1(500),		0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//Forward, intake
	auto(enc1(-180),	0,		0,			IN,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(gyro2(55),		0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//turn
	auto(enc1(-700),	0,		0,			0,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(gyro2(130),	0,		lPre(BMP),	0,	0,	0,	DRIV_READY,	PID);	//Turn
	auto(enc1(1000),	0,		lPre(BMP),	0,	0,	0,	DRIV_READY,	NEXT);	//Fwd over bump
	auto(enc1(1000),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Fwd over bump
	auto(stopped(),		RIGHT,	lPre(GND),	0,	0,	0,	TIME_LIMIT,	650);	//strafe into tower
	auto(spd(85,0),		LEFT,	lPre(GND),	0,	0,	0,	TIME_LIMIT,	210);	//strafe away
	auto(enc1(250),		0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Fwd
	auto(straight(50),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	1800);	//Fwd + lift
	auto(straight(-90),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	200);	//Rev
	auto(stopped(),		0,		lPre(STS),	OUT,0,	0,	TIME_LIMIT,	2000);	//Dump
	auto(spd(REV,-25),	0,		lPre(BMP),	0,	0,	0,	TIME_LIMIT,	800);	//Turn
	autoResetEnd();
	}


void autoRedHang3(void) //Not working as of the Iowa State Championship
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Tranny,End Type,	Other
	auto(straight(50),	0,		0,			IN,	0,	0,	TIME_LIMIT,	150);	//fwd
	auto(enc1(500),		0,		0,			IN,	0,	0,	DRIV_READY,	NEXT);	//Forward, intake
	auto(enc1(-160),	0,		0,			IN,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(gyro2(55),		0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//turn
	auto(enc1(-700),	0,		0,			0,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(gyro2(130),	0,		lPre(BMP),	0,	0,	0,	DRIV_READY,	PID);	//Turn
	auto(enc1(800),		0,		lPre(BMP),	0,	0,	0,	DRIV_READY,	NEXT);	//Fwd over bump
	auto(enc1(100),		0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Fwd over bump
	auto(straight(HALF),0,		lPre(GND),	0,	0,	0,	TIME_LIMIT,	1750);	//drive
	auto(straight(50),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	1900);	//Fwd + lift
	auto(straight(-90),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	200);	//Rev
	auto(stopped(),		0,		lPre(STS),	OUT,0,	0,	TIME_LIMIT,	1700);	//Dump
	auto(straight(REV),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	100);	//Rev
	auto(gyro2(-90),	0,		lPre(STS),	0,	0,	0,	DRIV_READY,	NEXT);	//Turn
	auto(enc1(-1900),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//backward + drop lift
	/*if (timerAuto>=1500)
		zeroMotors();*/
	autoResetEnd();
	}
