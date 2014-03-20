
void scriptEmpty() //Don't need???
	{
	//sysVirtualAuto=false;
	/*autoResetStart(0, SCRIPT, false, false, false);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(0,		0,		0,		0,		0,	DRIV_READY,	0,		0,		0);
	autoResetEnd();		*/
	}


void scriptDescore()
	{
	autoResetStart(0, SCRIPT, STO_TAKEOVER, false, true, false);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(0,		0,		0,		L_STSH,	0,	LIFT_READY,	0,		4000,	NEXT);
	auto(0,		0,		0,		L_GRND,	0,	LIFT_READY,	800,	2000,	NEXT);
	auto(0,		0,		0,		L_STSH,	0,	LIFT_READY,	800,	2000,	NEXT);
	autoResetEnd();
	}


void scriptDescore2()
	{
	autoResetStart(0, SCRIPT, STO_ADD, false, true, false);
		//L,	R,		S,		Lift,	Intk,End Type,	Min,	Max,Action
	auto(0,		0,		0,		L_STSH,	0,	LIFT_READY,	0,		4000,	NEXT);
	auto(0,		0,		0,		L_GRND,	0,	LIFT_READY,	800,	2000,	NEXT);
	auto(0,		0,		0,		L_STSH,	0,	LIFT_READY,	800,	2000,	NEXT);
	autoResetEnd();
	}
