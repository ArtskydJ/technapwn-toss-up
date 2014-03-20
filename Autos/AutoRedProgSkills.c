//AutoRedProgSkills.c

void autoRedProgSkills(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,		Intk,Cata,End Type,	Other
	auto(straight(25),	0,		lPre(STS),	OUT,0,	TIME_LIMIT,	1000);	//Forward, dump preload
	auto(straight(25),	0,		lPre(STS),	0,	0,	TIME_LIMIT,	2500);	//Forward, strafe hit ball 1
	auto(straight(REV),	0,		0,			0,	0,	TIME_LIMIT,	500);	//reverse
	auto(gyro2(90),		0,		0,			0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		0,			0,	0,	TIME_LIMIT,	1500);	//fwd
	auto(gyro2(-90),	0,		0,			0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		0,			0,	0,	TIME_LIMIT,	500);	//forward, hit ball 2
	auto(straight(REV),	0,		0,			0,	0,	TIME_LIMIT,	500);	//reverse
	auto(gyro2(90),		0,		0,			0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		0,			0,	0,	TIME_LIMIT,	2000);	//fwd
	auto(gyro2(-90),	0,		0,			0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		0,			0,	0,	TIME_LIMIT,	500);	//forward, hit ball 3
	auto(straight(REV),	0,		0,			0,	0,	TIME_LIMIT,	500);	//reverse
	auto(gyro2(90),		0,		0,			0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		0,			0,	0,	TIME_LIMIT,	1500);	//fwd
	auto(gyro2(-90),	0,		0,			0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		0,			0,	0,	TIME_LIMIT,	500);	//forward, hit ball 4
	autoResetEnd();
	}
