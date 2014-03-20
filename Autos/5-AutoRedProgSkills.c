//AutoRedProgSkills.c



void autoRedProgSkills(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
/*
//From Hanging Zone, grab easy 2
	auto(enc1(500),		0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//Forward + in
	auto(gyro2(-180),	0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//turn 180
	auto(enc1(1400),	0,		lPre(BMP),	IN,	0,	0,	DRIV_READY,	NEXT);	//Forward over bump

//STASH
	auto(gyroL(18),		0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//turn
	auto(enc1(1100),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	PID);	//Forward
	auto(enc1(400),		0,		lPre(STS),	0,	0,	0,	DRIV_READY,	PID);	//Forward + lift
	auto(straight(FWD),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	500);	//Forward
	auto(stopped(),		0,		lPre(STS),	OUT,0,	0,	TIME_LIMIT,	1300);	//dump
	auto(enc1(-150),	0,		lPre(STS),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(enc1(-1150),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse + drop
	auto(gyro2(-18),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	PID);	//turn

//From Hanging Zone, grab 3
	auto(enc1(475),		0,		0,			0,	0,	0,	DRIV_READY,	PID);	//fwd
	auto(stopped(),usStrfR(120),0,			0,	0,	0,	DRIV_READY,	PID);	//strafe
	auto(straight(FWD),	0,		0,			IN,	0,	0,	TIME_LIMIT,	200);	//fwd
	auto(straight(-100),LEFT,	0,			IN,	0,	0,	TIME_LIMIT,	650);	//rev, strafe
	auto(straight(FWD),	0,		0,			IN,	0,	0,	TIME_LIMIT,	400);	//fwd
	auto(straight(-100),LEFT,	0,			IN,	0,	0,	TIME_LIMIT,	650);	//rev, strafe
	auto(straight(FWD),	0,		0,			IN,	0,	0,	TIME_LIMIT,	400);	//fwd
	auto(gyro2(95),		0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//turn
	auto(enc1(1520),	0,		0,			0,	0,	0,	DRIV_READY,	NEXT);	//fwd
	auto(gyro2(95),		0,		0,			0,	0,	0,	DRIV_READY,	PID);	//turn 95
	auto(enc1(450),		0,		lPre(BMP),	0,	0,	0,	DRIV_READY,	NEXT);	//fwd
	auto(straight(35),	0,		lPre(BMP),	0,	0,	0,	TIME_LIMIT,	700);	//bump align
	auto(enc1(650),		0,		lPre(BMP),	0,	0,	0,	DRIV_READY,	NEXT);	//fwd

//STASH
	auto(gyroL(18),		0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//turn
	auto(enc1(1100),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	PID);	//Forward
	auto(enc1(400),		0,		lPre(STS),	0,	0,	0,	DRIV_READY,	PID);	//Forward + lift
	auto(straight(FWD),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	500);	//Forward
	auto(stopped(),		0,		lPre(STS),	OUT,0,	0,	TIME_LIMIT,	1300);	//dump
	auto(enc1(-150),	0,		lPre(STS),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(enc1(-1150),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse + drop
	auto(gyro2(-18),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	PID);	//turn

//From Middle Zone, hit 4 larges
	auto(enc1(550),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//fwd to ball 1
	auto(straight(80),	0,		lPre(BAR),	0,	0,	0,	TIME_LIMIT,	500);	//fwd, was 100spd, 350ms
	auto(enc1(-250),	0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//rev, was -200
	auto(gyro2(94),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	PID);	//turn
	auto(enc1(575),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//fwd to ball 2, 700
	auto(straight(FWD),	LEFT,	lPre(BAR),	0,	0,	0,	TIME_LIMIT,	600);	//strafe in
	auto(straight(FWD),	RIGHT,	lPre(BAR),	0,	0,	0,	TIME_LIMIT,	800);	//strafe out
	auto(enc1(650),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//fwd to ball 3, 1200
	auto(straight(FWD),	LEFT,	lPre(BAR),	0,	0,	0,	TIME_LIMIT,	800);	//strafe in
	auto(straight(FWD),	RIGHT,	lPre(BAR),	0,	0,	0,	TIME_LIMIT,	800);	//strafe out
	auto(enc1(400),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//fwd to ball 4, 1050
	auto(stopped(),		LEFT,	lPre(BAR),	0,	0,	0,	TIME_LIMIT,	350);	//strafe in			*/

//From Middle Zone, grab 3
	auto(straight(HALF),0,		0,			0,	0,	0,	TIME_LIMIT,	500);	//fwd into wall
	auto(enc1(-40),		0,		0,			0,	0,	0,	DRIV_READY,	NEXT);	//rev, was 60
	auto(gyro2(80),		0,		0,			0,	0,	0,	DRIV_READY,	NEXT);	//turn
	auto(straight(REV),	0,		0,			0,	0,	0,	TIME_LIMIT,	400);	//rev
	auto(enc1(200),		0,		0,			0,	0,	0,	DRIV_READY,	NEXT);	//fwd
	auto(enc1(2020),	0,		lPre(GND),	IN,	0,	0,	DRIV_READY,	PID);	//fwd + drop
	auto(stopped(),		RIGHT,	0,			IN,	0,	0,	TIME_LIMIT,	500);	//rev
	auto(enc1(-3080),	0,		lPre(GND),	IN,	0,	0,	DRIV_READY,	NEXT);	//rev to goal zone
	auto(gyro2(180),	0,		lPre(STS),	0,	0,	0,	DRIV_READY,	NEXT);	//turn + lift
	auto(stopped(),usStrfR(71),	lPre(STS),	0,	0,	0,	DRIV_READY,	NEXT);	//strafe
	auto(straight(100),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	500);	//fwd
	auto(stopped(),		0,		lPre(STS),	OUT,0,	0,	TIME_LIMIT,	1200);	//dump

	autoResetEnd();
	}




/*INVERTED STASH
	auto(gyroL(-18),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//turn
	auto(enc1(1100),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	PID);	//Forward
	auto(enc1(400),		0,		lPre(STS),	0,	0,	0,	DRIV_READY,	PID);	//Forward + lift
	auto(straight(FWD),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	500);	//Forward
	auto(stopped(),		0,		lPre(STS),	OUT,0,	0,	TIME_LIMIT,	1300);	//dump
//	auto(enc1(-150),	0,		lPre(STS),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse
//	auto(enc1(-1150),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse + drop
//	auto(gyro2(18),		0,		lPre(GND),	0,	0,	0,	DRIV_READY,	PID);	//turn				*/
