#include "WrongCompile.c"

#define d90   920   //degrees, 90
#define d180  1840  //degrees, 180

void autoRedMid2LargePre(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
	auto(IN_SPEED,	0,		0,		0,		IN_SPEED,	0,		0,		L_PRE[L_STSH],	OUT,TIME_LIMIT,	2000,	0,	NEXT); //Forward, dump preload
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		L_PRE[L_STSH],	0,	TIME_LIMIT,	1500,	0,	NEXT); //Forward, strafe hit ball 1
	auto(IN_SPEED,	REV,	REV,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,	NEXT); //reverse
	auto(IN_SPEED,	FWD,	REV,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	1000,	0,	NEXT); //fwd
	auto(IN_SPEED,	REV,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,	NEXT); //forward, hit ball 2
	autoResetEnd();
	}

void autoBlueMid2LargePre(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
	auto(IN_SPEED,	0,		0,		0,		IN_SPEED,	0,		0,		L_PRE[L_STSH],	OUT,TIME_LIMIT,	2000,	0,	NEXT); //Forward, dump preload
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		L_PRE[L_STSH],	0,	TIME_LIMIT,	1500,	0,	NEXT); //Forward, strafe hit ball 1
	auto(IN_SPEED,	REV,	REV,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,	NEXT); //reverse
	auto(IN_SPEED,	REV,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	1000,	0,	NEXT); //fwd
	auto(IN_SPEED,	FWD,	REV,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,	NEXT); //forward, hit ball 2
	autoResetEnd();
	}

void autoBlueHang2BuckyPre(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		L_PRE[L_DRIV],	IN,	TIME_LIMIT,	700,	0,	NEXT); //Forward, intake
	auto(IN_SPEED,	REV,	REV,	0,		IN_SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	2000,	0,	NEXT); //reverse
	auto(IN_SPEED,	FWD,	REV,	0,		IN_SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	1000,	0,	NEXT); //Forward
	auto(IN_SPEED,	FWD,	REV,	0,		IN_SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	4000,	0,	NEXT); //Forward
	auto(IN_SPEED,	0,		0,		0,		IN_SPEED,	0,		0,		L_PRE[L_DRIV],	OUT,TIME_LIMIT,	1500,	0,	NEXT); //dump
	autoResetEnd();
	}

void autoRedHang2BuckyPre(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		L_PRE[L_DRIV],	IN,	TIME_LIMIT,	700,	0,	NEXT); //Forward, intake
	auto(IN_SPEED,	REV,	REV,	0,		IN_SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	2000,	0,	NEXT); //reverse
	auto(IN_SPEED,	REV,	FWD,	0,		IN_SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	1000,	0,	NEXT); //Forward
	auto(IN_SPEED,	REV,	FWD,	0,		IN_SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	d90,	0,	NEXT); //turn
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		L_PRE[L_DRIV],	0,	TIME_LIMIT,	4000,	0,	NEXT); //Forward
	auto(IN_SPEED,	0,		0,		0,		IN_SPEED,	0,		0,		L_PRE[L_DRIV],	OUT,TIME_LIMIT,	1500,	0,	NEXT); //dump
	autoResetEnd();
	}



void autoBlueProgSkills(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
	auto(IN_SPEED,	25,		25,		0,		IN_SPEED,	0,		0,		L_PRE[L_STSH],	OUT,TIME_LIMIT,	1000,	0,		NEXT); //Forward, dump preload
	auto(IN_SPEED,	25,		25,		0,		IN_SPEED,	0,		0,		L_PRE[L_STSH],	0,	TIME_LIMIT,	2500,	0,		NEXT); //Forward, strafe hit ball 1
	auto(IN_SPEED,	REV,	REV,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,		NEXT); //reverse
	auto(IN_SPEED,	FWD,	REV,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,		NEXT); //turn
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	1500,	0,		NEXT); //fwd
	auto(IN_SPEED,	REV,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,		NEXT); //turn
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,		NEXT); //forward, hit ball 2
	auto(IN_SPEED,	REV,	REV,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,		NEXT); //reverse
	auto(IN_SPEED,	FWD,	REV,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,		NEXT); //turn
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	2000,	0,		NEXT); //fwd
	auto(IN_SPEED,	REV,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,		NEXT); //turn
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,		NEXT); //forward, hit ball 3
	auto(IN_SPEED,	REV,	REV,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,		NEXT); //reverse
	auto(IN_SPEED,	FWD,	REV,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,		NEXT); //turn
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	1500,	0,		NEXT); //fwd
	auto(IN_SPEED,	REV,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	d90,	0,		NEXT); //turn
	auto(IN_SPEED,	FWD,	FWD,	0,		IN_SPEED,	0,		0,		0,				0,	TIME_LIMIT,	500,	0,		NEXT); //forward, hit ball 4
	autoResetEnd();
	}



////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// TESTS ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////



void autoTest(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//D Type,	Left,Right,D Target,	S Type,		IN_SPEED,		S Target,Lift,	Intake,	End Type,		Min time,Max time,Action
	auto(GYRO_TURN,FWD,	FWD,	900,	IN_SPEED,	FWD,		0,		0,			0,	DRIV_READY,	800,	1200,	PID);
	auto(GYRO_TURN,FWD,	FWD,	900,	IN_SPEED,	FWD,		0,		0,			0,	DRIV_READY,	800,	1200,	PID);
	auto(ENCODER,1450,	1450,	0,		IN_SPEED,	FWD,		0,		L_STSH,		0,	FULL_READY,	2100,	3000,	PID);
	auto(IN_SPEED,	0,		0,		0,		LEFT_WALL,FWD,		600,	L_STSH,		0,	FULL_READY,	2000,	3000,	PID);
	auto(IN_SPEED,	0,		0,		0,		IN_SPEED,	FWD,		0,		0,			0,	TIME_LIMIT,	3000,	0,		NEXT);
	autoResetEnd();
	}
/*
INdrvType, INdrvLft, INdrvRht, INdrvTarget,		INstrfType, INstrfIN_SPEED, INstrfTarget,		INlift, INintk, INendType, INminTime, INmaxTime, INdelayPID
*/

void autoTest2(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//D Type,	Left,Right,D Target,	S Type,		IN_SPEED,		S Target,Lift,	Intake,	End Type,		Min time,Max time,Action
	auto(IN_SPEED,	-100,	-100,	0,		IN_SPEED,	20,			0,		0,			0,	TIME_LIMIT,	500,	0,		NEXT);
	auto(IN_SPEED,	100,	100,	0,		IN_SPEED,	20,			0,		0,			0,	TIME_LIMIT,	800,	0,		NEXT);
	auto(IN_SPEED,	1450,	1450,	0,		IN_SPEED,	0,			0,		0,			0,	TIME_LIMIT,	2200,	0,		NEXT);
	auto(IN_SPEED,	10,		10,		0,		IN_SPEED,	40,			0,		0,			0,	TIME_LIMIT,	2200,	0,		NEXT);
	auto(IN_SPEED,	0,		0,		0,		IN_SPEED,	FWD,		0,		0,			0,	TIME_LIMIT,	3200,	0,		NEXT);
	autoResetEnd();
	}
