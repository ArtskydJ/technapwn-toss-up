void autoTestThings(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//D Type,D Speed,D Target,S Type,S Speed,S Target,Lift,		Intake,End Type,Min time,Max time,Action
	auto(GYRO_TURN,	FWD,	900,	SPEED,	FWD,	0,		0,			0,	DRIV_READY,	800,	1200,	PID);
	auto(GYRO_TURN,	FWD,	900,	SPEED,	FWD,	0,		0,			0,	DRIV_READY,	800,	1200,	PID);
	auto(ENCODER,	1450,	1450,	SPEED,	FWD,	0,		L_PRE[L_STSH],0,	FULL_READY,	2100,	3000,	PID);
	auto(SPEED,	0,		0,		LEFT_WALL,FWD,		600,	L_PRE[L_STSH],0,	FULL_READY,	2000,	3000,	PID);
	auto(SPEED,	0,		0,		SPEED,	FWD,		0,		0,			0,	TIME_LIMIT,	3000,	0,		NEXT);
	autoResetEnd();
	}


void autoTestDrive(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//D Type,D Speed,D Target,S Type,S Speed,S Target,Lift,		Intake,End Type,Min time,Max time,Action
	auto(SPEED,	-100,	-100,	SPEED,	20,		0,		0,			0,	TIME_LIMIT,	500,	0,		NEXT);
	auto(SPEED,	100,	100,	SPEED,	20,		0,		0,			0,	TIME_LIMIT,	800,	0,		NEXT);
	auto(SPEED,	1450,	1450,	SPEED,	0,		0,		0,			0,	TIME_LIMIT,	2200,	0,		NEXT);
	auto(SPEED,	10,		10,		SPEED,	40,		0,		0,			0,	TIME_LIMIT,	2200,	0,		NEXT);
	auto(SPEED,	0,		0,		SPEED,	FWD,	0,		0,			0,	TIME_LIMIT,	3200,	0,		NEXT);
	autoResetEnd();
	}


void autoTestGyro(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//D Type,D Speed,D Target,S Type,S Speed,S Target,Lift,		Intake,End Type,Min time,Max time,Action
	auto(SPEED,	REV,	FWD,	SPEED,	0,			0,		0,			0,	TIME_LIMIT,	0,		0,		PID);
	auto(SPEED,	FWD,	REV,	SPEED,	0,			0,		0,			0,	TIME_LIMIT,	0,		0,		PID);
	autoResetEnd();
	}
