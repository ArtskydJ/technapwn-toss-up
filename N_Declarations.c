/* GLOBAL VARIABLES
 All variables for joystick sticks, buttons,
robot sensors, autonomous values, debugger
values, and general values.
*/


/* OUTPUT VARIABLES
 These variables are written-to, processed and
read-from, to help assign motor values.
*/
int outDrvX;
int outDrvY;
int outDrvZ;
int outLift;
int outIntk;


/* FAKE TIMERS
 The loop iteration time is added to these every
step. The default ROBOTC firmware has only 4
timers, but this allows us to have as many as we
want.
*/
unsigned int timerLCDScroll		= 0;
unsigned int timerLCDBacklight	= 0;
unsigned int timerAuto			= 0;
unsigned int timerRobotIdle		= 0;
unsigned int timerEmulateSpeed	= 0;

T_LC_INT autoRoutine;
bool autoClockRunning = false;

//^^^^^^^^^^^^^^^^DEFINITELY GLOBAL!!!

// SENSORS
int senSelectorPot;
int senPwrExpVoltage;
int senAddToAbsGyro; //Not actually a sensor, but it helps with computation.
int senAbsGyro;
int senLeftEdge;
int senRightEdge;
T_LC_INT senLiftLPot;
T_LC_INT senLiftRPot;
T_LC_INT senGyro;
T_LC_INT senLeftUS;
T_LC_INT senRightUS;
T_LC_INT senLeftQSE;
T_LC_INT senRightQSE;


//System
bool sysAutoMode = false;
bool sysDisabledMode = false;
T_ERROR sysError = ERR_NONE;
int  sysLCDBacklight=LCD_ALWAYS_ON;
//bool sysVirtualAuto = false;
bool sysMotorTest = false;
bool sysMotorsEnabled = true;
T_LC_INT sysState;
int  sysLooptime;


//--Arrays--//
bool autoScriptTakeover[3]={0,0,0};
short mtrTestEnabled[10]={0,0,0,0,0,0,0,0,0,0};
char slewConstants[3][10];

string batteryLevel[3];
string motorName[10];
