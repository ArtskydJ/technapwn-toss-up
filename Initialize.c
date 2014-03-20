//Constants
static const int AUTO_DRV_SLEW = 3;
static const int OPER_DRV_SLEW = 3;
static const int AUTO_LIFT_SLEW = 8;
static const int OPER_LIFT_SLEW = 8;
static const int AUTO_INTK_SLEW = 10;
static const int OPER_INTK_SLEW = 10;

//Functions
void initializeOther()
	{
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
	sysState.curr=DISABLED; //Should change to operator later
	}
