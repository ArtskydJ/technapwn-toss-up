//AutoRedProgSkills.c

void autoRedProgSkills(void)
	{
	//SUBJECT TO CHANGE:
	//0 = beginning
	//13 = first stash
	//17 = get large
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
//From Hanging Zone, grab easy 2, stash them
	auto(enc1(500),		0,		lPre(GND),	IN,	0,	0,	DRIV_READY,	PID);	//Forward, INTAKE 2 RED
	auto(straight(-100),LEFT,	lPre(GND),	IN,	0,	0,	TIME_LIMIT,	300);	//Rev + strafe
	auto(enc1(-1500),	0,		lPre(BMP),	IN,	0,	0,	DRIV_READY,	NEXT);	//Rev over bump
	auto(straight(REV),	0,		lPre(STS),	IN,	0,	0,	TIME_LIMIT,	450);	//Rev + lift
	auto(straight(REV),	0,		0,			0,	0,	0,	TIME_LIMIT,	450);	//Rev, HIT LARGE BALL 1
	auto(enc1(200),		0,		0,			0,	0,	0,	DRIV_READY,	NEXT);	//Fwd from bar
	auto(enc1(-1200),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Rev to goal zone
	auto(enc1(80),		0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Fwd from ball
	auto(gyro2(-180),	0,		lPre(STS),	0,	0,	0,	DRIV_READY,	PID);	//Turn + lift
	auto(stopped(),usStrfL(72),	lPre(STS),	0,	0,	0,	DRIV_READY,	PID);	//Strafe
	auto(straight(100),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	1000);	//Fwd
	auto(straight(REV),0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	250);	//Rev
	auto(stopped(),		0,		lPre(STS),	OUT,0,	0,	TIME_LIMIT,	1200);	//DUMP OUT 3 RED BUCKY

//Go and throw a large ball
	auto(enc1(-320),	0,		lPre(STS),	OUT,0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(gyro2(-177),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	PID);	//Turn + drop
	auto(enc1(500),		0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Fwd under bar
	auto(spd(0,90),		LEFT,	lPre(GND),	0,	0,	0,	TIME_LIMIT,	700);	//strafe into tower
	auto(spd(0,0),		RIGHT,	lPre(GND),	0,	0,	0,	TIME_LIMIT,	450);	//strafe away
	auto(enc1(2250),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Forward
	auto(straight(60),	0,		lPre(GND),	OUT,0,	0,	TIME_LIMIT,	900);	//Forward into large
	auto(enc1(-350),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(stopped(),encStrf1(-400),lPre(GND),0,	0,	0,	DRIV_READY,	NEXT);	//Strafe
	auto(enc1Spd(-1600,90),0,	lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(enc1(-200),	0,		lPre(GND),	0,	1,	0,	DRIV_READY,	NEXT);	//REV + THROW
	auto(gyro2(-95),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	PID);	//Turn

//From Middle Zone, grab 3
	auto(enc1(1600),	0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//Forward
	auto(straight(FWD),	0,		lPre(BAR),	0,	0,	0,	TIME_LIMIT,	800);	//Fwd to wall
	auto(enc1(-40),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//Rev from wall
	auto(gyro2(85),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//Turn
	auto(straight(REV),	0,		0,			0,	0,	0,	TIME_LIMIT,	1400);	//Rev, HIT LARGE BALL 4
	auto(straight(FWD),	0,		0,			0,	0,	0,	TIME_LIMIT,	200);	//Fwd from bar
	auto(enc1(2210),	0,		lPre(GND),	IN,	0,	0,	DRIV_READY,	NEXT);	//Fwd, INTAKE 2 BLUE
	auto(stopped(),		0,		lPre(GND),	IN,	0,	0,	TIME_LIMIT,	400);	//Intake longer
	auto(straight(-100),RIGHT,	0,			IN,	0,	0,	TIME_LIMIT,	500);	//Rev + strafe
	auto(enc1(-3080),	0,		0,			IN,	0,	0,	DRIV_READY,	NEXT);	//Rev to goal zone
	auto(enc1(120),		0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Fwd from ball
	auto(gyro2(180),	0,		lPre(STS),	0,	0,	0,	DRIV_READY,	PID);	//Turn + lift
	auto(stopped(),usStrfR(74),	lPre(STS),	0,	0,	0,	DRIV_READY,	PID);	//Strafe
	auto(straight(100),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	1100);	//Fwd
	auto(straight(-100),0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	250);	//Rev
	auto(stopped(),		0,		lPre(STS),	OUT,0,	0,	TIME_LIMIT,	1200);	//DUMP OUT 3 BLUE BUCKY

//Go and throw a large ball
	auto(enc1(-320),	0,		lPre(STS),	OUT,0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(gyro2(177),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	PID);	//Turn + drop
	auto(enc1(500),		0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Fwd under bar
	auto(spd(90,0),		RIGHT,	lPre(GND),	0,	0,	0,	TIME_LIMIT,	700);	//strafe into tower
	auto(stopped(),		LEFT,	lPre(GND),	0,	0,	0,	TIME_LIMIT,	450);	//strafe away
	auto(enc1(2250),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Forward
	auto(straight(60),	0,		lPre(GND),	OUT,0,	0,	TIME_LIMIT,	900);	//Forward into large
	auto(enc1(-350),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(stopped(),encStrf1(400),lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Strafe
	auto(enc1Spd(-1600,90),0,	lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse
	auto(enc1(-200),	0,		lPre(GND),	0,	1,	0,	DRIV_READY,	NEXT);	//REV + THROW

	auto(stopped(),		0,		lPre(GND),	0,	0,	0,	TIME_LIMIT, 100);	//Lower catapult

//Go to red starting tile
	/*auto(gyro2(76),		0,		lPre(GND),	0,	0,	0,	DRIV_READY,	PID);	//Turn
	auto(enc1(2200),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Fwd
	auto(gyro2(-76),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	PID);	//Turn*/

	if (timerAuto>=5990) outCatapult = true;

	autoResetEnd();
	}
