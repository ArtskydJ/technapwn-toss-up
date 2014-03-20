//AutoRedProgSkills.c

void autoRedProgSkillsOld(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,		Intk,Cata,End Type,	Other
	auto(straight(FWD),	0,		lPre(BAR),	IN,	0,	TIME_LIMIT,	500);	//Forward, dump preload
	auto(stopped(),				lPre(BAR),	0,	0,	TIME_LIMIT,	750);	//raise
	auto(straight(REV),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	750);	//reverse
	auto(gyro2(90),		0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	1200);	//fwd
	auto(gyro2(-90),	0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	750);	//forward, hit ball 2
	auto(straight(REV),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	750);	//reverse
	auto(gyro2(90),		0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	1500);	//fwd
	auto(gyro2(-90),	0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	750);	//forward, hit ball 3
	auto(straight(REV),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	750);	//reverse
	auto(gyro2(90),		0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	1200);	//fwd
	auto(gyro2(-90),	0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	750);	//forward, hit ball 4
	autoResetEnd();
	}


void autoRedProgSkills(void)
	{
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,		Intk,Cata,End Type,	Other
	auto(straight(FWD),	0,		0,			IN,	1,	TIME_LIMIT,	950);	//Intake pre, Hit ball 1
	auto(straight(REV),	0,		0,			0,	0,	TIME_LIMIT,	600);	//Reverse
	auto(gyro2(35),		0,		0,			0,	0,	DRIV_READY,	PID);	//turn right
	auto(straight(FWD),	0,		0,			0,	0,	TIME_LIMIT,	1000);	//Forward
	auto(straight(HALF),0,		lPre(STS),	0,	0,	TIME_LIMIT,	600);	//Forward + Lift
	auto(stopped(),				lPre(STS),	0,	0,	TIME_LIMIT,	1000);	//Lift
	auto(0,		FWD,	0,		lPre(STS),	0,	0,	TIME_LIMIT,	450);	//Turn
	auto(HALF,	HALF,	0,		lPre(STS),	OUT,0,	TIME_LIMIT,	1000);	//fwd + dump preload
	auto(-90,	REV,	0,		0,			0,	0,	TIME_LIMIT,	900);	//Reverse
	auto(stopped(),				lPre(GND),	0,	0,	TIME_LIMIT,	1250);	//Drop lift
	auto(straight(REV),	0,		lPre(GND),	0,	0,	TIME_LIMIT,	1200);	//Reverse + drop lift
	auto(gyro2(25),		0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn right + lift
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	650);	//Forward hit ball 2

	auto(straight(REV),	0,		0,			0,	0,	TIME_LIMIT,	750);	//Reverse
	auto(gyro2(55),		0,		lPre(GND),	0,	0,	DRIV_READY,	PID);	//turn right + drop lift
	auto(straight(FWD),	0,		lPre(GND),	0,	0,	TIME_LIMIT,	1800);	//Forward toward blue
	auto(gyro2(-90),	0,		lPre(BAR),	0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	750);	//forward, hit ball 3

	auto(straight(REV),	0,		lPre(BAR),	0,	0,	TIME_LIMIT,	1200);	//reverse
	auto(gyro2(90),		0,		lPre(GND),	0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		lPre(GND),	IN,	0,	TIME_LIMIT,	1050);	//Forward toward blue
	auto(gyro2(-90),	0,		lPre(GND),	0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(-50),	0,		lPre(GND),	0,	0,	TIME_LIMIT,	600);	//reverse into bump
	auto(straight(FWD),	0,		lPre(GND),	0,	1,	TIME_LIMIT,	1000);	//forward, hit ball 4

	auto(straight(REV),	0,		lPre(GND),	0,	0,	TIME_LIMIT,	600);	//reverse
	auto(gyro2(-35),	0,		0,			0,	0,	DRIV_READY,	PID);	//turn left
	auto(straight(FWD),	0,		0,			0,	0,	TIME_LIMIT,	1050);	//Forward
	auto(straight(HALF),0,		lPre(STS),	0,	0,	TIME_LIMIT,	600);	//Forward + Lift
	auto(stopped(),				lPre(STS),	0,	0,	TIME_LIMIT,	1000);	//Lift
	auto(FWD,	0,		0,		lPre(STS),	0,	0,	TIME_LIMIT,	450);	//Turn
	auto(HALF,	HALF,	0,		lPre(STS),	OUT,0,	TIME_LIMIT,	1000);	//fwd + dump blue

	autoResetEnd();
	}
