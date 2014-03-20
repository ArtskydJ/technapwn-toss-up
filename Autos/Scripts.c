
void scriptEmpty() //Don't need???
	{
	//sysVirtualAuto=false;
	/*autoResetStart(0, SCRIPT, false, false, false);
		//L,	R,		S,		Lift,	Intk,Cata,End Type,	Other
	auto(0,		0,		0,		0,		0,	0,	DRIV_READY,	NEXT);
	autoResetEnd();		*/
	}


void scriptDescore()
	{
	autoResetStart(0, SCRIPT, false, true, false);
		//L,	R,		S,		Lift,	Intk,Cata,End Type,	Other
	auto(0,		0,		0,		L_STSH,	0,	0,	LIFT_READY,	NEXT);
	auto(0,		0,		0,		L_GRND,	0,	0,	LIFT_READY,	NEXT);
	auto(0,		0,		0,		L_STSH,	0,	0,	LIFT_READY,	NEXT);
	autoResetEnd();
	}


void scriptDescore2()
	{
	autoResetStart(0, SCRIPT, false, true, false);
		//L,	R,		S,		Lift,	Intk,Cata,End Type,	Other
	auto(0,		0,		0,		L_STSH,	0,	0,	LIFT_READY,	NEXT);
	auto(0,		0,		0,		L_GRND,	0,	0,	LIFT_READY,	NEXT);
	auto(0,		0,		0,		L_STSH,	0,	0,	LIFT_READY,	NEXT);
	autoResetEnd();
	}
