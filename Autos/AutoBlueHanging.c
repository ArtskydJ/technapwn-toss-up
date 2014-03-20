//AutoBlueHanging.c

void autoBlueHang1(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,End Type,	Min,	Max,Action
	auto(stopped(),				UP,		0,	0,	TIME_LIMIT,	500); //Jerk lift
	auto(straight(50),	0,		DOWN,	IN,	0,	TIME_LIMIT,	500); //Forward, intake
	auto(straight(50),	0,		0,		IN,	0,	TIME_LIMIT,	1100); //Forward, intake
	auto(stopped(),				10,		IN,	0,	TIME_LIMIT,	200); //intake more
	auto(gyro2(90),		0,		10,		0,	0,	DRIV_READY,	PID);  //turn
	auto(straight(FWD),	0,		10,		0,	0,	TIME_LIMIT,	750); //Forward
	auto(gyro2(90),		0,		10,		0,	0,	DRIV_READY,	PID);  //turn
	auto(straight(FWD),	0,		UP,		0,	0,	TIME_LIMIT,	700); //Forward
	auto(gyro2(-300),	0,		60,		0,	0,	DRIV_READY,	PID);  //turn
	auto(stopped(),				10,		OUT,0,	TIME_LIMIT,	1300); //dump
	//auto(straight(REV),0,		-10,	0,	0,	TIME_LIMIT,	250); //Reverse
	auto(gyro2(-900),	0,		10,		0,	0,	DRIV_READY,	PID);  //turn
	auto(straight(FWD),	0,		10,		0,	0,	TIME_LIMIT,	900); //Forward
	auto(gyro2(600),	0,		10,		0,	0,	DRIV_READY,	PID);  //turn
	auto(straight(FWD),	0,		10,		0,	0,	TIME_LIMIT,	300); //Forward
	auto(turn2(-40),	RIGHT,	10,		0,	0,	TIME_LIMIT,	1700);  //Strafe
	autoResetEnd();
	}
