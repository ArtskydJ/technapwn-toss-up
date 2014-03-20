void autoTestThings(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(gyro2(900),	0,		0,		0,	DRIV_READY,	800,	1200,	PID);
	auto(gyro2(900),	0,		0,		0,	DRIV_READY,	800,	1200,	PID);
	auto(enc(1450,1450),0,		L_STSH,	0,	FULL_READY,	2100,	3000,	PID);
	auto(straight(0),	usL(18),L_STSH,	0,	FULL_READY,	2000,	3000,	PID);
	auto(straight(0),	FWD,	0,		0,	TIME_LIMIT,	3000,	0,		NEXT);
	autoResetEnd();
	}


void autoTestDrive(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(straight(-100),20,		0,		0,	TIME_LIMIT,	500,	0,		NEXT);
	auto(straight(100),	20,		0,		0,	TIME_LIMIT,	800,	0,		NEXT);
	auto(1450,	1450,	0,		0,		0,	TIME_LIMIT,	2200,	0,		NEXT);
	auto(straight(10),	40,		0,		0,	TIME_LIMIT,	2200,	0,		NEXT);
	auto(straight(0),	FWD,	0,		0,	TIME_LIMIT,	3200,	0,		NEXT);
	autoResetEnd();
	}


void autoTestGyro(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(gyro2(-900),	0,		0,		0,	DRIV_READY,	0,		0,	PID);
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	1000,	0,		NEXT);
//	auto(stopped(),				0,		0,	TIME_LIMIT,	1000,	0,	PID);
//	auto(gyro2(900),	0,		0,		0,	DRIV_READY,	0,		0,	PID);
	autoResetEnd();
	}
