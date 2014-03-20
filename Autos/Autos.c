#define d90   920   //degrees, 90
#define d180  1840  //degrees, 180

void autoRedMid2LargePre(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//D Type,D Speed,D Target,S Type,S Speed,S Target,Lift,		Intake,End Type,Min time,Max time,Action
	auto(SPEED,	0,		0,		SPEED,	0,		0,		L_PRE[L_STSH],	OUT,TIME_LIMIT,	2000,	0,	NEXT); //Forward, dump preload
	auto(SPEED,	FWD,	FWD,	SPEED,	0,		0,		L_PRE[L_STSH],	0,	TIME_LIMIT,	1500,	0,	NEXT); //Forward, strafe hit ball 1
	auto(SPEED,	REV,	REV,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,	NEXT); //reverse
	auto(SPEED,	FWD,	REV,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(SPEED,	FWD,	FWD,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	1000,	0,	NEXT); //fwd
	auto(SPEED,	REV,	FWD,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(SPEED,	FWD,	FWD,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,	NEXT); //forward, hit ball 2
	autoResetEnd();
	}

void autoBlueMid2LargePre(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//D Type,D Speed,D Target,S Type,S Speed,S Target,Lift,		Intake,End Type,Min time,Max time,Action
	auto(SPEED,	0,		0,		SPEED,	0,		0,		L_PRE[L_STSH],	OUT,TIME_LIMIT,	2000,	0,	NEXT); //Forward, dump preload
	auto(SPEED,	FWD,	FWD,	SPEED,	0,		0,		L_PRE[L_STSH],	0,	TIME_LIMIT,	1500,	0,	NEXT); //Forward, strafe hit ball 1
	auto(SPEED,	REV,	REV,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,	NEXT); //reverse
	auto(SPEED,	REV,	FWD,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(SPEED,	FWD,	FWD,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	1000,	0,	NEXT); //fwd
	auto(SPEED,	FWD,	REV,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(SPEED,	FWD,	FWD,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,	NEXT); //forward, hit ball 2
	autoResetEnd();
	}

void autoBlueHang2BuckyPre(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//D Type,D Speed,D Target,S Type,S Speed,S Target,Lift,		Intake,End Type,Min time,Max time,Action
	auto(SPEED,	FWD,	FWD,	SPEED,	0,		0,		L_PRE[L_DRIV],	IN,	TIME_LIMIT,	700,	0,	NEXT); //Forward, intake
	auto(SPEED,	REV,	REV,	SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	2000,	0,	NEXT); //reverse
	auto(SPEED,	FWD,	REV,	SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(SPEED,	FWD,	FWD,	SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	1000,	0,	NEXT); //Forward
	auto(SPEED,	FWD,	REV,	SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(SPEED,	FWD,	FWD,	SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	4000,	0,	NEXT); //Forward
	auto(SPEED,	0,		0,		SPEED,	0,		0,		L_PRE[L_DRIV],	OUT,TIME_LIMIT,	1500,	0,	NEXT); //dump
	autoResetEnd();
	}

void autoRedHang2BuckyPre(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//D Type,D Speed,D Target,S Type,S Speed,S Target,Lift,		Intake,End Type,Min time,Max time,Action
	auto(SPEED,	FWD,	FWD,	SPEED,	0,		0,		L_PRE[L_DRIV],	IN,	TIME_LIMIT,	700,	0,	NEXT); //Forward, intake
	auto(SPEED,	REV,	REV,	SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	2000,	0,	NEXT); //reverse
	auto(SPEED,	REV,	FWD,	SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(SPEED,	FWD,	FWD,	SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	1000,	0,	NEXT); //Forward
	auto(SPEED,	REV,	FWD,	SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(SPEED,	FWD,	FWD,	SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	4000,	0,	NEXT); //Forward
	auto(SPEED,	0,		0,		SPEED,	0,		0,		L_PRE[L_DRIV],	OUT,TIME_LIMIT,	1500,	0,	NEXT); //dump
	autoResetEnd();
	}



void autoBlueProgSkills(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//D Type,D Speed,D Target,S Type,S Speed,S Target,Lift,		Intake,End Type,Min time,Max time,Action
	auto(SPEED,	25,		0,		SPEED,	0,		0,		L_PRE[L_STSH],	OUT,TIME_LIMIT,	1000,	0,		NEXT); //Forward, dump preload
	auto(SPEED,	25,		0,		SPEED,	0,		0,		L_PRE[L_STSH],	0,	TIME_LIMIT,	2500,	0,		NEXT); //Forward, strafe hit ball 1
	auto(SPEED,	REV,	0,		SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,		NEXT); //reverse
	auto(SPEED,	0,		RIGHT,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,		NEXT); //turn
	auto(SPEED,	FWD,	0,		SPEED,	0,		0,		0,				0,	TIME_LIMIT,	1500,	0,		NEXT); //fwd
	auto(SPEED,	0,		LEFT,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,		NEXT); //turn
	auto(SPEED,	FWD,	0,		SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,		NEXT); //forward, hit ball 2
	auto(SPEED,	REV,	0,		SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,		NEXT); //reverse
	auto(SPEED,	0,		RIGHT,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,		NEXT); //turn
	auto(SPEED,	FWD,	0,		SPEED,	0,		0,		0,				0,	TIME_LIMIT,	2000,	0,		NEXT); //fwd
	auto(SPEED,	0,		LEFT,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,		NEXT); //turn
	auto(SPEED,	FWD,	0,		SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,		NEXT); //forward, hit ball 3
	auto(SPEED,	REV,	0,		SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,		NEXT); //reverse
	auto(SPEED,	0,		RIGHT,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,		NEXT); //turn
	auto(SPEED,	FWD,	0,		SPEED,	0,		0,		0,				0,	TIME_LIMIT,	1500,	0,		NEXT); //fwd
	auto(SPEED,	0,		LEFT,	SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,		NEXT); //turn
	auto(SPEED,	FWD,	0,		SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,		NEXT); //forward, hit ball 4
	autoResetEnd();
	}
