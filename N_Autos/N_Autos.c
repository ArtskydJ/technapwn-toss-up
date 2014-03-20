#include "N_WrongCompile.c"

void autoTest()
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//Left/Type,Rht/Spd,Straf/Targt,Lift,		Intake,	End Type,	Min time,Max time,Action
	auto(GYRO_BOTH,	FULL,	900,		0,			0,		DRIV_READY,	800,	1200,	PID);
	auto(GYRO_BOTH,	FULL,	900,		0,			0,		DRIV_READY,	800,	1200,	PID);
	auto(1450,		1450,	0,			L_STASH,	0,		FULL_READY,	2100,	3000,	PID);
	auto(0,			0,		L_US(600),	L_STASH,	0,		FULL_READY,	2000,	3000,	PID);
	auto(0,			0,		127,			0,			0,		TIME_LIMIT,	3000,	0,		NEXT);
	autoResetEnd();
	}


void autoTest2()
	{
	autoResetStart(0, AUTON, 0, 0, 0, 0);
		//Left/Type,Rht/Spd,Straf/Targt,Lift,	Intake,	End Type,	Min time,Max time,Action
	auto(-100,		-100,	20,		0,			0,		TIME_LIMIT,	500,	0,		NEXT);
	auto(100,		100,	20,		0,			0,		TIME_LIMIT,	800,	0,		NEXT);
	auto(1450,		1450,	0,		0,			0,		TIME_LIMIT,	2200,	0,		NEXT);
	auto(10,		10,		40,		0,			0,		TIME_LIMIT,	2200,	0,		NEXT);
	auto(0,			0,		127,	0,			0,		TIME_LIMIT,	3200,	0,		NEXT);
	autoResetEnd();
	}
