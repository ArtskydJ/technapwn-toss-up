//Constants
static const int AUTO_DRV_SLEW = 3;
static const int OPER_DRV_SLEW = 3;
static const int AUTO_LIFT_SLEW = 8;
static const int OPER_LIFT_SLEW = 8;
static const int AUTO_INTK_SLEW = 10;
static const int OPER_INTK_SLEW = 10;


void initialize()
	{
	initializeAutonomous();

	//--Motor Names--//
	motorName[DRIVE_FL]  = "Frnt L Dr";
	motorName[DRIVE_BL1] = "Back L Dr1";
	motorName[DRIVE_BL2] = "Back L Dr2";
	motorName[DRIVE_FR]  = "Frnt R Dr1";
	motorName[DRIVE_BR1] = "Back R Dr1";
	motorName[DRIVE_BR2] = "Back R Dr2";
	motorName[LIFT_L]    = "L Lift";
	motorName[LIFT_R]    = "R Lift";
	motorName[INTK_L]    = "Intake";
	//motorName[INTK_R]    = "R Intake";

	//--Motor Slew Constants--//
	for (int j=0; j<10; j++)
		slewConstants[DISABLED][j] = 127;					//DISABLED

	slewConstants[OPERATOR][DRIVE_FL]  = OPER_DRV_SLEW;		//OPERATOR
	slewConstants[OPERATOR][DRIVE_BL1] = OPER_DRV_SLEW;
	slewConstants[OPERATOR][DRIVE_BL2] = OPER_DRV_SLEW;
	slewConstants[OPERATOR][DRIVE_FR]  = OPER_DRV_SLEW;
	slewConstants[OPERATOR][DRIVE_BR1] = OPER_DRV_SLEW;
	slewConstants[OPERATOR][DRIVE_BR2] = OPER_DRV_SLEW;
	slewConstants[OPERATOR][LIFT_L]    = OPER_LIFT_SLEW;
	slewConstants[OPERATOR][LIFT_R]    = OPER_LIFT_SLEW;
	slewConstants[OPERATOR][INTK_L]    = OPER_INTK_SLEW;
	//slewConstants[OPERATOR][INTK_R]    = OPER_INTK_SLEW;

	slewConstants[AUTONOMOUS][DRIVE_FL]  = AUTO_DRV_SLEW;		//AUTONOMOUS
	slewConstants[AUTONOMOUS][DRIVE_BL1] = AUTO_DRV_SLEW;
	slewConstants[AUTONOMOUS][DRIVE_BL2] = AUTO_DRV_SLEW;
	slewConstants[AUTONOMOUS][DRIVE_FR]  = AUTO_DRV_SLEW;
	slewConstants[AUTONOMOUS][DRIVE_BR1] = AUTO_DRV_SLEW;
	slewConstants[AUTONOMOUS][DRIVE_BR2] = AUTO_DRV_SLEW;
	slewConstants[AUTONOMOUS][LIFT_L]    = AUTO_LIFT_SLEW;
	slewConstants[AUTONOMOUS][LIFT_R]    = AUTO_LIFT_SLEW;
	slewConstants[AUTONOMOUS][INTK_L]    = AUTO_INTK_SLEW;
	//slewConstants[AUTONOMOUS][INTK_R]    = AUTO_INTK_SLEW;

	//--Encoders--//
	SensorValue[QUAD_LEFT] = 0;
	SensorValue[QUAD_RIGHT] = 0;

	//--Timers--//
	ClearTimer(T1);
	ClearTimer(T2);
	ClearTimer(T3);
	ClearTimer(T4);

	//--Other--//
	writeDebugStreamLine("================");
	sysState.curr=OPERATOR;
	}
