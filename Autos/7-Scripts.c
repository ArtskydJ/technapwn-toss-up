void scriptHang()
	{
	autoResetStart(0, SCRIPT, true, true, false);
		//L,	R,		S,		Lift,	Intk,Cata,Tranny,End Type,	Other
	//auto(straight(HALF),0,	lPre(STS),	0,	0,	0,	TIME_LIMIT,	100);	//Drive into bar
	//auto(straight(REV),	0,	lPre(GND),	0,	0,	1,	TIME_LIMIT,	5000);	//Hang
	auto(straight(REV),	0,		0,			0,	0,	1,	TIME_LIMIT,	5000);	//Hang
	autoResetEnd();
	}
