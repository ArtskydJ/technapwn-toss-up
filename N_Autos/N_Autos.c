#include "N_WrongCompile.c"

void autoTest()
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//D Type,	Left,Right,D Target,	S Type,		Speed,		S Target,Lift,		Intake,	End Type,		Min time,Max time,Action
	auto(DT_G_TURN,	FULL,	FULL,	900,	ST_IN_SPD,	FULL,		0,		0,			0,		ET_DRIV_READY,	800,	1200,	PID);
	auto(DT_G_TURN,	FULL,	FULL,	900,	ST_IN_SPD,	FULL,		0,		0,			0,		ET_DRIV_READY,	800,	1200,	PID);
	auto(DT_IN_ENC,	1450,	1450,	0,		ST_IN_SPD,	FULL,		0,		L_STSH,		0,		ET_FULL_READY,	2100,	3000,	PID);
	auto(DT_IN_SPD,	0,		0,		0,		ST_U_LEFT,	FULL,		600,	L_STSH,		0,		ET_FULL_READY,	2000,	3000,	PID);
	auto(DT_IN_SPD,	0,		0,		0,		ST_IN_SPD,	FULL,		0,		0,			0,		ET_TIME_LIMIT,	3000,	0,		NEXT);
	autoResetEnd();
	}
/*
INdrvType, INdrvLft, INdrvRht, INdrvTarget,		INstrfType, INstrfSpeed, INstrfTarget,			INlift, INintk, INendType, INminTime, INmaxTime, INdelayPID
*/

void autoTest2()
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//D Type,	Left,Right,D Target,	S Type,		Speed,		S Target,Lift,		Intake,	End Type,		Min time,Max time,Action
	auto(DT_IN_SPD,	-100,	-100,	0,		ST_IN_SPD,	20,			0,		0,			0,		ET_TIME_LIMIT,	500,	0,		NEXT);
	auto(DT_IN_SPD,	100,	100,	0,		ST_IN_SPD,	20,			0,		0,			0,		ET_TIME_LIMIT,	800,	0,		NEXT);
	auto(DT_IN_SPD,	1450,	1450,	0,		ST_IN_SPD,	0,			0,		0,			0,		ET_TIME_LIMIT,	2200,	0,		NEXT);
	auto(DT_IN_SPD,	10,		10,		0,		ST_IN_SPD,	40,			0,		0,			0,		ET_TIME_LIMIT,	2200,	0,		NEXT);
	auto(DT_IN_SPD,	0,		0,		0,		ST_IN_SPD,	127,		0,		0,			0,		ET_TIME_LIMIT,	3200,	0,		NEXT);
	autoResetEnd();
	}
