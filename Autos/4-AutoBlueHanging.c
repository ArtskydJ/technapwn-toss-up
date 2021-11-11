//AutoBlueHanging.c
//500 = 1 tile (2 ft)

void autoBlueHang1(void) //Working as of 2014-04-24
	{
	autoResetStart(0, AUTON, 0, 0, 0);
	    //L,    R,      S,      Lift,   Intk,Cata,Tranny,End Type,  Other
	auto(enc1(500),     0,      0,          IN, 0,  0,  DRIV_READY, PID);   //Forward, intake
	auto(enc1(-500),    0,      0,          IN, 0,  0,  DRIV_READY, PID);   //Reverse
	auto(gyro2(90),     0,      0,          0,  0,  0,  DRIV_READY, PID);   //turn 90
	auto(enc1(1020),    0,      0,          0,  0,  0,  DRIV_READY, PID);   //Forward, 1020
	auto(gyro2(90),     0,      lPre(BAR),  0,  0,  0,  DRIV_READY, PID);   //Turn 90
	auto(straight(30),  0,      lPre(BAR),  OUT,0,  0,  TIME_LIMIT, 1800);  //Dump
	auto(enc1(1500),    0,      lPre(BAR),  0,  0,  0,  DRIV_READY, NEXT);  //Forward
	auto(straight(HALF),0,      lPre(BAR),  0,  0,  0,  TIME_LIMIT, 500);   //Forward
	auto(enc1(-500),    0,      lPre(BAR),  0,  0,  0,  DRIV_READY, NEXT);  //Reverse
	auto(gyro2(-30),    0,      lPre(GND),  0,  0,  0,  FULL_READY, PID);   //Drop lift, turn
	auto(enc1(1100),    0,      lPre(GND),  OUT,0,  0,  DRIV_READY, NEXT);  //Forward
	autoResetEnd();
	}


void autoBlueHang2(void) //Working as of 2014-04-25
	{
	autoResetStart(0, AUTON, 0, 0, 0);
	    //L,    R,      S,      Lift,   Intk,Cata,Tranny,End Type,  Other
	auto(straight(50),  0,      0,          IN, 0,  0,  TIME_LIMIT, 150);   //fwd
	auto(enc1(500),     0,      0,          IN, 0,  0,  DRIV_READY, PID);   //Forward, intake
	auto(enc1(-180),    0,      0,          IN, 0,  0,  DRIV_READY, NEXT);  //Reverse
	auto(gyro2(-55),    0,      0,          IN, 0,  0,  DRIV_READY, PID);   //turn
	auto(enc1(-700),    0,      0,          0,  0,  0,  DRIV_READY, NEXT);  //Reverse
	auto(gyro2(-130),   0,      lPre(BMP),  0,  0,  0,  DRIV_READY, PID);   //Turn
	auto(enc1(1000),    0,      lPre(BMP),  0,  0,  0,  DRIV_READY, NEXT);  //Fwd over bump
	auto(enc1(1000),    0,      lPre(GND),  0,  0,  0,  DRIV_READY, NEXT);  //Fwd over bump
	auto(stopped(),     LEFT,   lPre(GND),  0,  0,  0,  TIME_LIMIT, 650);   //strafe into tower
	auto(spd(0,85),     RIGHT,  lPre(GND),  0,  0,  0,  TIME_LIMIT, 210);   //strafe away
	auto(enc1(250),     0,      lPre(GND),  0,  0,  0,  DRIV_READY, NEXT);  //Fwd
	auto(straight(50),  0,      lPre(STS),  0,  0,  0,  TIME_LIMIT, 1800);  //Fwd + lift
	auto(straight(-90), 0,      lPre(STS),  0,  0,  0,  TIME_LIMIT, 200);   //Rev
	auto(stopped(),     0,      lPre(STS),  OUT,0,  0,  TIME_LIMIT, 2000);  //Dump
	auto(spd(-25,REV),  0,      lPre(BMP),  0,  0,  0,  TIME_LIMIT, 800);   //Turn
	autoResetEnd();
	}


void autoBlueHang3(void) //Tested and working on 2014-04-25
	{
	autoResetStart(0, AUTON, 0, 0, 0);
	    //L,    R,      S,      Lift,   Intk,Cata,Tranny,End Type,  Other
	auto(straight(80),  0,      0,          IN, 0,  0,  TIME_LIMIT, 150);   //fwd
	auto(enc1(500),     0,      0,          IN, 0,  0,  DRIV_READY, PID);   //Forward, intake
	auto(enc1(-180),    0,      0,          IN, 0,  0,  DRIV_READY, NEXT);  //Reverse
	auto(gyro2(-55),    0,      0,          IN, 0,  0,  DRIV_READY, PID);   //turn
	auto(enc1(-700),    0,      0,          0,  0,  0,  DRIV_READY, NEXT);  //Reverse
	auto(gyro2(-130),   0,      lPre(BMP),  0,  0,  0,  DRIV_READY, PID);   //Turn
	auto(enc1(1300),    0,      lPre(BMP),  0,  0,  0,  DRIV_READY, NEXT);  //Fwd over bump
	auto(gyro2(-40),    0,      lPre(BAR),  0,  0,  0,  DRIV_READY, PID);   //Turn
	auto(straight(FWD), 0,      lPre(BAR),  0,  0,  0,  TIME_LIMIT, 250);   //Fwd into ball
	auto(enc1(-250),    0,      lPre(BAR),  0,  0,  0,  DRIV_READY, NEXT);  //rev
	auto(stopped(),     LEFT,   lPre(GND),  0,  0,  0,  TIME_LIMIT, 1200);  //strafe away
	auto(enc1(1900),    0,      lPre(GND),  0,  0,  0,  DRIV_READY, NEXT);  //Fwd
	auto(gyro2(140),    0,      lPre(GND),  0,  0,  0,  DRIV_READY, NEXT);  //Turn
	auto(enc1(-750),    0,      lPre(GND),  0,  0,  0,  DRIV_READY, NEXT);  //REV
	autoResetEnd();
	}


void autoBlueHang4(void) //Not working as of the Iowa State Championship
	{
	autoResetStart(0, AUTON, 0, 0, 0);
	    //L,    R,      S,      Lift,   Intk,Cata,Tranny,End Type,  Other
	auto(straight(50),  0,      0,          IN, 0,  0,  TIME_LIMIT, 150);   //fwd
	auto(enc1(500),     0,      0,          IN, 0,  0,  DRIV_READY, NEXT);  //Forward, intake
	auto(enc1(-160),    0,      0,          IN, 0,  0,  DRIV_READY, NEXT);  //Reverse
	auto(gyro2(-55),    0,      0,          IN, 0,  0,  DRIV_READY, PID);   //turn
	auto(enc1(-700),    0,      0,          0,  0,  0,  DRIV_READY, NEXT);  //Reverse
	auto(gyro2(-130),   0,      lPre(BMP),  0,  0,  0,  DRIV_READY, PID);   //Turn
	auto(enc1(800),     0,      lPre(BMP),  0,  0,  0,  DRIV_READY, NEXT);  //Fwd over bump
	auto(enc1(100),     0,      lPre(GND),  0,  0,  0,  DRIV_READY, NEXT);  //Fwd over bump
	auto(straight(HALF),0,      lPre(GND),  0,  0,  0,  TIME_LIMIT, 1750);  //drive
	auto(straight(50),  0,      lPre(STS),  0,  0,  0,  TIME_LIMIT, 1900);  //Fwd + lift
	auto(straight(-90), 0,      lPre(STS),  0,  0,  0,  TIME_LIMIT, 200);   //Rev
	auto(stopped(),     0,      lPre(STS),  OUT,0,  0,  TIME_LIMIT, 1700);  //Dump
	auto(straight(REV), 0,      lPre(STS),  0,  0,  0,  TIME_LIMIT, 100);   //Rev
	auto(gyro2(90),     0,      lPre(STS),  0,  0,  0,  DRIV_READY, NEXT);  //Turn
	auto(enc1(-1900),   0,      lPre(GND),  0,  0,  0,  DRIV_READY, NEXT);  //backward
	/*if (timerAuto>=1500)
	    zeroMotors();*/
	autoResetEnd();
	}
