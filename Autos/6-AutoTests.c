void autoTestThings(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(gyro2(90),		0,		0,			0,	0,	0,	DRIV_READY,	PID);
	auto(gyro2(90),		0,		0,			0,	0,	0,	DRIV_READY,	PID);
	auto(enc(1450,1450),0,		lPre(STS),	0,	0,	0,	FULL_READY,	PID);
	auto(stopped(),	usStrfL(18),lPre(STS),	0,	0,	0,	FULL_READY,	PID);
	auto(straight(0),	FWD,	0,			0,	0,	0,	TIME_LIMIT,	3000);
	autoResetEnd();
	}


void autoTestDrive(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(straight(FWD),	0,		0,			0,	0,	0,	TIME_LIMIT,	2000);
	/*auto(straight(100),	20,		0,			0,	0,	0,	TIME_LIMIT,	800);
	auto(enc1(1450),	0,		0,			0,	0,	0,	TIME_LIMIT,	2200);
	auto(straight(10),	40,		0,			0,	0,	0,	TIME_LIMIT,	2200);
	auto(straight(0),	FWD,	0,			0,	0,	0,	TIME_LIMIT,	3200);*/
	autoResetEnd();
	}


void autoTestGyro(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(gyro2(-90),	0,		0,			0,	0,	0,	DRIV_READY,	PID);
	auto(straight(FWD),	0,		0,			0,	0,	0,	TIME_LIMIT,	200);
	//auto(stopped(),				0,			0,	0,	0,	TIME_LIMIT,	1000,	0,	PID);
	//	auto(gyro2(900),	0,		0,			0,	0,	0,	DRIV_READY,	0,		0,	PID);
	autoResetEnd();
	}


void autoTestUltraFollow(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(usFllwL(60,70),0,		0,			0,	0,	0,	TIME_LIMIT,	2000);	//80 spd, 70 cm
	auto(stopped(),		0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	1200);
	auto(usFllwL(60,70),0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	1700);	//80 spd, 70 cm
	auto(stopped(),		0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	1200);
	autoResetEnd();
	}


void autoTestUltraFollow2(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(straight(0),usStrfL(70),0,			0,	0,	0,	DRIV_READY,	PID);	//yeah
//	auto(usFllwR(45,35),0,		0,			0,	0,	0,	TIME_LIMIT,	5500);	//40 spd, 30 cm
//	auto(usFllwNowR(80),0,		0,			0,	0,	0,	TIME_LIMIT,	3500);	//40 spd, x cm
//	auto(straight(5),	0,		0,			0,	0,	0,	TIME_LIMIT,	200);	//pause
//	auto(usFllwR(90, 70),0,		0,			0,	0,	0,	TIME_LIMIT,	3000);	//90 spd, 30 cm

	autoResetEnd();
	}

void autoTestEncStrafe(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(spd(0,0), encStrf1(700), 0,			0,	0,	0,	DRIV_READY,	PID);	//strafe enc
	autoResetEnd();
	}
