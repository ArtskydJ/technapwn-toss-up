//AutoRedMiddle.c

void autoRedMid1(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,End Type,	Min,	Max,Action
	auto(straight(HALF),0,		0,		IN,	0,	TIME_LIMIT,	250); //Intake pre
	auto(stopped(),				L_BARR,	IN,	0,	TIME_LIMIT,	1200); //Lift Up
	auto(straight(HALF),0,		L_BARR,	0,	0,	TIME_LIMIT,	800); //Lift Up
	auto(straight(REV),	0,		L_BARR,	0,	0,	TIME_LIMIT,	400); //reverse
	auto(gyro2(90),		0,		L_BARR,	0,	0,	DRIV_READY,	PID);  //turn right
	auto(straight(FWD),	0,		L_BARR,	0,	0,	TIME_LIMIT,	700); //fwd
	auto(gyro2(-90),	0,		L_BARR,	0,	0,	DRIV_READY,	PID);  //turn left
	auto(straight(FWD),	0,		L_BARR,	0,	0,	TIME_LIMIT,	300); //forward & hit ball 2
	auto(gyro2(-20),	0,		L_BARR,	0,	0,	DRIV_READY,	PID);  //turn left
	auto(stopped(),				L_BARR,	OUT,0,	TIME_LIMIT,	700); //Lift Down
	auto(straight(REV),	0,		L_BARR,	0,	0,	TIME_LIMIT,	500); //Back away from barrier
	auto(stopped(),				L_GRND,	0,	0,	TIME_LIMIT,	1000); //Lift Down
	autoResetEnd();
	}


void autoRedMid2(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,End Type,	Min,	Max,Action
	auto(straight(HALF),0,		0,		IN,	0,	TIME_LIMIT,	500); //Intake pre
	auto(gyro2(15),		0,		0,		0,	0,	DRIV_READY,	PID);  //turn right
	auto(straight(FWD),	0,		0,		IN,	0,	TIME_LIMIT,	1500); //Fwd
	auto(stopped(),				L_STSH,	IN,	0,	TIME_LIMIT,	1500); //Fwd + Lift
	autoResetEnd();
	}
