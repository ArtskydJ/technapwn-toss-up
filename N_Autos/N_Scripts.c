#include "N_WrongCompile.c"

void scriptEmpty() //Don't need???
	{
	sysVirtualAuto=false;
	/*autoResetStart(0, SCRIPT, false, false, false);
		//Left/Type,Rht/Spd,Straf/Targt,Lift,		Intake,	End Type,	Min time,Max time,Action
	auto(0,			0,		0,			0,			0,		DRIV_READY,	0,		0,		0);
	autoResetEnd();*/
	}


void scriptDescore()
	{
	autoResetStart(0, SCRIPT, ST_TAKEOVER, false, true, false);
		//Left/Type,Rht/Spd,Straf/Targt,Lift,		Intake,	End Type,	Min time,Max time,Action
	auto(0,			0,		0,			L_STASH,	0,		LIFT_READY,	0,		4000,	NEXT);
	auto(0,			0,		0,			L_BARRIER,	0,		LIFT_READY,	800,	2000,	NEXT);
	auto(0,			0,		0,			L_STASH,	0,		LIFT_READY,	800,	2000,	NEXT);
	autoResetEnd();
	}


void scriptDescore2()
	{
	autoResetStart(0, SCRIPT, ST_ADD, false, true, false);
		//Left/Type,Rht/Spd,Straf/Targt,Lift,		Intake,	End Type,	Min time,Max time,Action
	auto(0,			0,		0,			L_STASH,	0,		LIFT_READY,	0,		4000,	NEXT);
	auto(0,			0,		0,			L_BARRIER,	0,		LIFT_READY,	800,	2000,	NEXT);
	auto(0,			0,		0,			L_STASH,	0,		LIFT_READY,	800,	2000,	NEXT);
	autoResetEnd();
	}
