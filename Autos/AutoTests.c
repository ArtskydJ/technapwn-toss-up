void autoTestThings(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,		Intk,Cata,End Type,	Other
	auto(gyro2(90),		0,		0,			0,	0,	DRIV_READY,	PID);
	auto(gyro2(90),		0,		0,			0,	0,	DRIV_READY,	PID);
	auto(enc(1450,1450),0,		lPre(STS),	0,	0,	FULL_READY,	PID);
	auto(straight(0),	usL(18),lPre(STS),	0,	0,	FULL_READY,	PID);
	auto(straight(0),	FWD,	0,			0,	0,	TIME_LIMIT,	3000);
	autoResetEnd();
	}


void autoTestDrive(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,		Intk,Cata,End Type,	Other
	auto(straight(-100),20,		0,			0,	0,	TIME_LIMIT,	500);
	auto(straight(100),	20,		0,			0,	0,	TIME_LIMIT,	800);
	auto(1450,	1450,	0,		0,			0,	0,	TIME_LIMIT,	2200);
	auto(straight(10),	40,		0,			0,	0,	TIME_LIMIT,	2200);
	auto(straight(0),	FWD,	0,			0,	0,	TIME_LIMIT,	3200);
	autoResetEnd();
	}


void autoTestGyro(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,		Intk,Cata,End Type,	Other
	auto(gyro2(-90),	0,		0,			0,	0,	DRIV_READY,	PID);
	auto(straight(FWD),	0,		0,			0,	0,	TIME_LIMIT,	200);
	//auto(stopped(),				0,			0,	0,	TIME_LIMIT,	1000,	0,	PID);	//	auto(gyro2(900),	0,		0,			0,	0,	DRIV_READY,	0,		0,	PID);
	autoResetEnd();
	}
