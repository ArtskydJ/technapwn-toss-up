//Autos.c

//Functions
void autoRedMid1(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(stopped(),				UP,		0,	TIME_LIMIT,	1000,	0,	NEXT); //Lift Up
	auto(straight(FWD),	0,		UP,		0,	TIME_LIMIT,	1000,	0,	NEXT); //Forward & hit ball 1
	auto(straight(REV),	0,		10,		0,	TIME_LIMIT,	500,	0,	NEXT); //reverse
	auto(gyro2(90),		0,		10,		0,	DRIV_READY,	0,		0,	PID);  //turn right
	auto(straight(FWD),	0,		10,		0,	TIME_LIMIT,	1000,	0,	NEXT); //fwd
	auto(gyro2(-90),	0,		10,		0,	DRIV_READY,	0,		0,	PID);  //turn left
	auto(straight(HALF),0,		10,		OUT,TIME_LIMIT,	800,	0,	NEXT); //forward & hit ball 2
	autoResetEnd();
	}

void autoBlueMid1(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(stopped(),				UP,		0,	TIME_LIMIT,	1000,	0,	NEXT); //Lift Up
	auto(straight(FWD),	0,		UP,		0,	TIME_LIMIT,	1000,	0,	NEXT); //Forward & hit ball 1
	auto(straight(REV),	0,		10,		0,	TIME_LIMIT,	500,	0,	NEXT); //reverse
	auto(gyro2(-90),	0,		10,		0,	DRIV_READY,	0,		0,	PID);  //turn left
	auto(straight(FWD),	0,		10,		0,	TIME_LIMIT,	1000,	0,	NEXT); //fwd
	auto(gyro2(90),		0,		10,		0,	DRIV_READY,	0,		0,	PID);  //turn right
	auto(straight(HALF),0,		10,		OUT,TIME_LIMIT,	800,	0,	NEXT); //forward & hit ball 2
	autoResetEnd();
	}

void autoRedHang1(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(stopped(),				UP,		0,	TIME_LIMIT,	500,	0,	NEXT); //Jerk lift
	auto(straight(50),	0,		DOWN,	IN,	TIME_LIMIT,	500,	0,	NEXT); //Forward, intake
	auto(straight(50),	0,		0,		IN,	TIME_LIMIT,	1100,	0,	NEXT); //Forward, intake
	auto(stopped(),				10,		IN,	TIME_LIMIT,	200,	0,	NEXT); //intake more
	auto(gyro2(-90),	0,		10,		0,	DRIV_READY,	0,		0,	PID);  //turn left
	auto(straight(FWD),	0,		10,		0,	TIME_LIMIT,	750,	0,	NEXT); //Forward
	auto(gyro2(-90),	0,		10,		0,	DRIV_READY,	0,		0,	PID);  //turn left
	auto(straight(FWD),	0,		UP,		0,	TIME_LIMIT,	700,	0,	NEXT); //Forward
	auto(gyro2(30),		0,		60,		0,	DRIV_READY,	0,		0,	PID);  //turn 30 deg right
	auto(stopped(),				10,		OUT,TIME_LIMIT,	1300,	0,	NEXT); //dump
	//auto(straight(REV),0,		-10,	0,	TIME_LIMIT,	250,	0,	NEXT); //Reverse
	auto(gyro2(90),		0,		10,		0,	DRIV_READY,	0,		0,	PID);  //turn right
	auto(straight(FWD),	0,		10,		0,	TIME_LIMIT,	900,	0,	NEXT); //Forward
	auto(gyro2(-60),	0,		10,		0,	DRIV_READY,	0,		0,	PID);  //turn 60 deg left
	auto(straight(FWD),	0,		10,		0,	TIME_LIMIT,	300,	0,	NEXT); //Forward
	auto(turn2(20),		LEFT,	10,		0,	TIME_LIMIT,	1400,	0,	PID);  //Strafe and slightly turn right
	autoResetEnd();
	}


void autoBlueHang1(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(stopped(),				UP,		0,	TIME_LIMIT,	500,	0,	NEXT); //Jerk lift
	auto(straight(50),	0,		DOWN,	IN,	TIME_LIMIT,	500,	0,	NEXT); //Forward, intake
	auto(straight(50),	0,		0,		IN,	TIME_LIMIT,	1100,	0,	NEXT); //Forward, intake
	auto(stopped(),				10,		IN,	TIME_LIMIT,	200,	0,	NEXT); //intake more
	auto(gyro2(90),		0,		10,		0,	DRIV_READY,	0,		0,	PID);  //turn
	auto(straight(FWD),	0,		10,		0,	TIME_LIMIT,	750,	0,	NEXT); //Forward
	auto(gyro2(90),		0,		10,		0,	DRIV_READY,	0,		0,	PID);  //turn
	auto(straight(FWD),	0,		UP,		0,	TIME_LIMIT,	700,	0,	NEXT); //Forward
	auto(gyro2(-300),	0,		60,		0,	DRIV_READY,	0,		0,	PID);  //turn
	auto(stopped(),				10,		OUT,TIME_LIMIT,	1300,	0,	NEXT); //dump
	//auto(straight(REV),0,		-10,	0,	TIME_LIMIT,	250,	0,	NEXT); //Reverse
	auto(gyro2(-900),	0,		10,		0,	DRIV_READY,	0,		0,	PID);  //turn
	auto(straight(FWD),	0,		10,		0,	TIME_LIMIT,	900,	0,	NEXT); //Forward
	auto(gyro2(600),	0,		10,		0,	DRIV_READY,	0,		0,	PID);  //turn
	auto(straight(FWD),	0,		10,		0,	TIME_LIMIT,	300,	0,	NEXT); //Forward
	auto(turn2(-40),	RIGHT,	10,		0,	TIME_LIMIT,	1400,	0,	PID);  //Strafe
	autoResetEnd();
	}


void autoBlueProgSkills(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(straight(25),	0,		L_STSH,	OUT,TIME_LIMIT,	1000,	0,	NEXT); //Forward, dump preload
	auto(straight(25),	0,		L_STSH,	0,	TIME_LIMIT,	2500,	0,	NEXT); //Forward, strafe hit ball 1
	auto(straight(REV),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //reverse
	auto(gyro2(90),		0,		0,		0,	DRIV_READY,	0,		0,	PID);  //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	1500,	0,	NEXT); //fwd
	auto(gyro2(-90),	0,		0,		0,	DRIV_READY,	0,		0,	PID);  //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //forward, hit ball 2
	auto(straight(REV),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //reverse
	auto(gyro2(90),		0,		0,		0,	DRIV_READY,	0,		0,	PID);  //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	2000,	0,	NEXT); //fwd
	auto(gyro2(-90),	0,		0,		0,	DRIV_READY,	0,		0,	PID);  //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //forward, hit ball 3
	auto(straight(REV),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //reverse
	auto(gyro2(90),		0,		0,		0,	DRIV_READY,	0,		0,	PID);  //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	1500,	0,	NEXT); //fwd
	auto(gyro2(-90),	0,		0,		0,	DRIV_READY,	0,		0,	PID);  //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //forward, hit ball 4
	autoResetEnd();
	}
