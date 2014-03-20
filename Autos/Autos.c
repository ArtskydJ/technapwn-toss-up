#define d90   920   //degrees, 90
#define d180  1840  //degrees, 180

void autoRedMid2LargePre(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(stopped(),				L_STSH,	OUT,TIME_LIMIT,	2000,	0,	NEXT); //Forward, dump preload
	auto(straight(FWD),	0,		L_STSH,	0,	TIME_LIMIT,	1500,	0,	NEXT); //Forward, strafe hit ball 1
	auto(straight(REV),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //reverse
	auto(turn2(RIGHT),	0,		0,		0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	1000,	0,	NEXT); //fwd
	auto(turn2(LEFT),	0,		0,		0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //forward, hit ball 2
	autoResetEnd();
	}

void autoBlueMid2LargePre(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(stopped(),				L_STSH,	OUT,TIME_LIMIT,	2000,	0,	NEXT); //Forward, dump preload
	auto(straight(FWD),	0,		L_STSH,	0,	TIME_LIMIT,	1500,	0,	NEXT); //Forward, strafe hit ball 1
	auto(straight(REV),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //reverse
	auto(turn2(LEFT),	0,		0,		0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	1000,	0,	NEXT); //fwd
	auto(turn2(RIGHT),	0,		0,		0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //forward, hit ball 2
	autoResetEnd();
	}

void autoBlueHang2BuckyPre(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(straight(FWD),	0,		L_DRIV,	IN,	TIME_LIMIT,	700,	0,	NEXT); //Forward, intake
	auto(straight(REV),	0,		L_DRIV,	0,	TIME_LIMIT,	2000,	0,	NEXT); //reverse
	auto(turn2(RIGHT),	0,		L_DRIV,	0,	TIME_LIMIT,	d90,	0,	NEXT); //turn right
	auto(straight(FWD),	0,		L_DRIV,	0,	TIME_LIMIT,	1000,	0,	NEXT); //Forward
	auto(turn2(RIGHT),	0,		L_DRIV,	0,	TIME_LIMIT,	d90,	0,	NEXT); //turn right
	auto(straight(FWD),	0,		L_DRIV,	0,	TIME_LIMIT,	4000,	0,	NEXT); //Forward
	auto(stopped(),				L_DRIV,	OUT,TIME_LIMIT,	1500,	0,	NEXT); //dump
	autoResetEnd();
	}

void autoRedHang2BuckyPre(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(straight(FWD),	0,		L_DRIV,	IN,	TIME_LIMIT,	700,	0,	NEXT); //Forward, intake
	auto(straight(REV),	0,		L_DRIV,	0,	TIME_LIMIT,	2000,	0,	NEXT); //reverse
	auto(turn2(LEFT),	0,		L_DRIV,	0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(straight(FWD),	0,		L_DRIV,	0,	TIME_LIMIT,	1000,	0,	NEXT); //Forward
	auto(turn2(LEFT),	0,		L_DRIV,	0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(straight(FWD),	0,		L_DRIV,	0,	TIME_LIMIT,	4000,	0,	NEXT); //Forward
	auto(stopped(),				L_DRIV,	OUT,TIME_LIMIT,	1500,	0,	NEXT); //dump
	autoResetEnd();
	}



void autoBlueProgSkills(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(straight(25),	0,		L_STSH,	OUT,TIME_LIMIT,	1000,	0,	NEXT); //Forward, dump preload
	auto(straight(25),	0,		L_STSH,	0,	TIME_LIMIT,	2500,	0,	NEXT); //Forward, strafe hit ball 1
	auto(straight(REV),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //reverse
	auto(turn2(RIGHT),	0,		0,		0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	1500,	0,	NEXT); //fwd
	auto(turn2(LEFT),	0,		0,		0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //forward, hit ball 2
	auto(straight(REV),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //reverse
	auto(turn2(RIGHT),	0,		0,		0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	2000,	0,	NEXT); //fwd
	auto(turn2(LEFT),	0,		0,		0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //forward, hit ball 3
	auto(straight(REV),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //reverse
	auto(turn2(RIGHT),	0,		0,		0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	1500,	0,	NEXT); //fwd
	auto(turn2(LEFT),	0,		0,		0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(straight(FWD),	0,		0,		0,	TIME_LIMIT,	500,	0,	NEXT); //forward, hit ball 4
	autoResetEnd();
	}
