
void scriptEmpty() //Don't need???
	{
	//sysVirtualAuto=false;
	/*autoResetStart(0, SCRIPT, false, false, false);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(0,		0,		0,		0,			0,	0,	0,	DRIV_READY,	NEXT);
	autoResetEnd();		*/
	}


void scriptDescore()
	{
	autoResetStart(0, SCRIPT, false, true, false);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(spd(0, 0),		0,		lPre(STS),	0,	0,	0,	LIFT_READY,	NEXT);
	auto(spd(0, 0),		0,		lPre(GND),	0,	0,	0,	LIFT_READY,	NEXT);
	auto(spd(0, 0),		0,		lPre(STS),	0,	0,	0,	LIFT_READY,	NEXT);
	autoResetEnd();
	}


void scriptDescore2()
	{
	autoResetStart(0, SCRIPT, false, true, false);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
	auto(spd(0, 0),		0,		lPre(STS),	0,	0,	0,	LIFT_READY,	NEXT);
	auto(spd(0, 0),		0,		lPre(GND),	0,	0,	0,	LIFT_READY,	NEXT);
	auto(spd(0, 0),		0,		lPre(STS),	0,	0,	0,	LIFT_READY,	NEXT);
	autoResetEnd();
	}
