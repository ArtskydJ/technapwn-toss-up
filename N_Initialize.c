void initialize()
	{
	//--Structs--//
	//PID Controllers
	PIDLiftL.kp = 0.1;
	PIDLiftL.ki = 0.00;
	PIDLiftL.kd = 0.00;

	PIDLiftR.kp = 0.1;
	PIDLiftR.ki = 0.00;
	PIDLiftR.kd = 0.00;

	/*PIDIntk.kp = 0.1;
	PIDIntk.ki = 0.00;
	PIDIntk.kd = 0.00;*/

	PIDLineFollow.kp = 0.1;
	PIDLineFollow.ki = 0.00;
	PIDLineFollow.kd = 0.00;

	PIDWallFollow.kp = 0.1;
	PIDWallFollow.ki = 0.00;
	PIDWallFollow.kd = 0.00;

	PIDDriveL.kp = 0.6;
	PIDDriveL.ki = 0.00;
	PIDDriveL.kd = 0.00;

	PIDDriveR.kp = 0.6;
	PIDDriveR.ki = 0.00;
	PIDDriveR.kd = 0.00;

	PIDStrafeEncod.kp = 0.6;
	PIDStrafeEncod.ki = 0.00;
	PIDStrafeEncod.kd = 0.00;

	PIDStrafeUltra.kp = 0.6;
	PIDStrafeUltra.ki = 0.00;
	PIDStrafeUltra.kd = 0.00;

	PIDGyro.kp = 2;
	PIDGyro.ki = 0.00;
	PIDGyro.kd = 0.00;

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
	autoRoutine.curr = 0;
	}
