//AutoRedProgSkills.c

#define LONG

void autoRedProgSkills(void)
	{
	//SUBJECT TO CHANGE:
	//0 = beginning
	//14 = into wall by ladder (if LONG)
	//34 = stash (if LONG)
	autoResetStart(0, AUTON, 0, 0, 0);
		//L,	R,		S,		Lift,	Intk,Cata,Load,End Type,	Other
//From Hanging Zone, grab easy 2
	auto(enc1(500),		0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//Forward + in
	auto(gyro2(-180),	0,		0,			IN,	0,	0,	DRIV_READY,	PID);	//turn 180
	auto(enc1(1400),	0,		lPre(BMP),	IN,	0,	0,	DRIV_READY,	NEXT);	//Forward over bump
	auto(enc1(1300),	0,		lPre(GND),	IN,	0,	0,	DRIV_READY,	NEXT);	//Forward, drop lift

//STASH - (can this be done more effectively in the same amount of time?)
	auto(stopped(),usStrfL(72),	lPre(STS),	0,	0,	0,	DRIV_READY,	PID);	//strafe
	auto(straight(FWD),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	800);	//Forward
	auto(stopped(),		0,		lPre(STS),	OUT,0,	0,	TIME_LIMIT,	1300);	//dump
	auto(straight(FWD),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	300);	//Forward, align
	auto(gyroR(45),		0,		lPre(STS),	0,	0,	0,	DRIV_READY,	NEXT);	//turn away from stash
	auto(enc1(-510),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse

#ifdef LONG
	auto(gyro2(135),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	PID);	//turn
	auto(straight(FWD),	0,		lPre(GND),	0,	0,	0,	TIME_LIMIT,	600);	//Forward under bar
	auto(enc1(2150),	0,		lPre(BMP),	0,	0,	0,	DRIV_READY,	NEXT);	//Forward over bump
	auto(straight(HALF),0,		lPre(BAR),	0,	0,	0,	TIME_LIMIT,	1000);	//Forward into wall
	auto(straight(REV),	0,		lPre(BAR),	0,	0,	0,	TIME_LIMIT,	350);	//Reverse from wall

//From Hanging Zone, grab 3
	auto(stopped(),usStrfR(123),lPre(GND),	0,	0,	0,	DRIV_READY,	PID);	//strafe, was 120
	auto(straight(FWD),	0,		0,			IN,	0,	0,	TIME_LIMIT,	200);	//fwd
	auto(straight(-100),LEFT,	0,			IN,	0,	0,	TIME_LIMIT,	650);	//rev, strafe
	auto(straight(FWD),	0,		0,			IN,	0,	0,	TIME_LIMIT,	400);	//fwd
	auto(straight(-100),LEFT,	0,			IN,	0,	0,	TIME_LIMIT,	650);	//rev, strafe
	auto(straight(FWD),	0,		0,			IN,	0,	0,	TIME_LIMIT,	400);	//fwd
	auto(straight(-100),LEFT,	0,			IN,	0,	0,	TIME_LIMIT,	650);	//rev, strafe
	auto(enc1(-1300),	0,		lPre(BMP),	0,	0,	0,	DRIV_READY,	NEXT);	//rev
	auto(enc1(-1300),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//rev
	auto(gyro2(90),		0,		0,			0,	0,	0,	DRIV_READY,	PID);	//turn 90
	auto(enc1(920),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//fwd
	auto(gyro2(90),		0,		0,			0,	0,	0,	DRIV_READY,	PID);	//turn 90

//STASH - (can this be done more effectively in the same amount of time?)
	auto(stopped(),usStrfL(72),	lPre(STS),	0,	0,	0,	DRIV_READY,	PID);	//strafe
	auto(straight(FWD),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	800);	//Forward
	auto(stopped(),		0,		lPre(STS),	OUT,0,	0,	TIME_LIMIT,	1300);	//dump
	auto(straight(FWD),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	300);	//Forward, align
	auto(gyroR(45),		0,		lPre(STS),	0,	0,	0,	DRIV_READY,	NEXT);	//turn away from stash
	auto(enc1(-510),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//Reverse

#endif //ifdef LONG, line 25

	auto(gyro2(-45),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//turn
	auto(enc1(-1100),	0,		lPre(GND),	0,	0,	0,	DRIV_READY,	NEXT);	//reverse past bar
//From Middle Zone, hit 4 larges
	auto(stopped(),		0,		lPre(BAR),	0,	0,	0,	LIFT_READY,	NEXT);	//lift
	auto(enc1(400),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//fwd to ball 1
	auto(straight(80),	0,		lPre(BAR),	0,	0,	0,	TIME_LIMIT,	500);	//fwd, WAS 100spd, 350ms
	auto(enc1(-200),	0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//rev, WAS -200, -300
	auto(gyro2(97),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	PID);	//turn
	auto(enc1(600),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//fwd to ball 2, 700
	auto(straight(FWD),	LEFT,	lPre(BAR),	0,	0,	0,	TIME_LIMIT,	600);	//strafe in
	auto(straight(FWD),	RIGHT,	lPre(BAR),	0,	0,	0,	TIME_LIMIT,	600);	//strafe out
	auto(enc1(760),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//fwd to ball 3, 1200
	auto(straight(FWD),	LEFT,	lPre(BAR),	0,	0,	0,	TIME_LIMIT,	800);	//strafe in
	auto(straight(FWD),	RIGHT,	lPre(BAR),	0,	0,	0,	TIME_LIMIT,	1000);	//strafe out
	auto(enc1(400),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//fwd to ball 4, 1050

//From Middle Zone, grab 3
	auto(straight(HALF),0,		lPre(BAR),	0,	0,	0,	TIME_LIMIT,	600);	//fwd into wall
	auto(enc1(-40),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//rev, WAS -60
	auto(gyro2(85),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//turn, WAS 80
	auto(straight(REV),	0,		0,			0,	0,	0,	TIME_LIMIT,	600);	//rev, hit ball
	auto(straight(FWD),	0,		0,			0,	0,	0,	TIME_LIMIT,	200);	//fwd from bar
	auto(enc1(2210),	0,		lPre(GND),	IN,	0,	0,	DRIV_READY,	NEXT);	//fwd + intake
	auto(straight(-100),RIGHT,	0,			IN,	0,	0,	TIME_LIMIT,	500);	//rev
	auto(enc1(-3080),	0,		lPre(GND),	IN,	0,	0,	DRIV_READY,	NEXT);	//rev to goal zone
	auto(gyro2(180),	0,		lPre(STS),	0,	0,	0,	DRIV_READY,	NEXT);	//turn + lift
	auto(stopped(),usStrfR(71),	lPre(STS),	0,	0,	0,	DRIV_READY,	NEXT);	//strafe
	auto(straight(100),	0,		lPre(STS),	0,	0,	0,	TIME_LIMIT,	500);	//fwd
	auto(stopped(),		0,		lPre(STS),	OUT,0,	0,	TIME_LIMIT,	1200);	//dump

	autoResetEnd();
	}


/*  Corner blue hang zone ball needs more intake time or more fwd b4 strafe away
 *  Push large blue back farther?
 *  Add preload fling?
 *  Change both 510 reverse-after-dumps to 450s?
 *  Add code to stop it @ 60 sec
 */







#if (0) //LINES 69 - 74
	auto(enc1(400),		0,		lPre(BAR),	0,	0,	0,	DRIV_READY,	NEXT);	//fwd to ball 4, 1050
	auto(stopped(),		LEFT,	lPre(BAR),	0,	0,	0,	TIME_LIMIT,	350);	//strafe in
//*/

//----------Merge "strafe in" and "fwd into wall" into 1 step----------

//From Middle Zone, grab 3
	auto(straight(HALF),0,		0,			0,	0,	0,	TIME_LIMIT,	500);	//fwd into wall
	auto(enc1(-40),		0,		0,			0,	0,	0,	DRIV_READY,	NEXT);	//rev, WAS -60
#endif //if (0), line 87
