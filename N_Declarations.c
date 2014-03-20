/* VARIABLES
 All variables for joystick sticks, buttons,
robot sensors, autonomous values, debugger
values, and general values.
*/
// STICKS
int stkMtrTest;
int stkDrvX;
int stkDrvY;
int stkDrvZ;

// BUTTONS
// SCREEN
T_LC_BOOL btnScreenLeft;
T_LC_BOOL btnScreenCenter;
T_LC_BOOL btnScreenRight;
// JOYSTICK
T_LC_BOOL btnLiftUp;
T_LC_BOOL btnLiftDown;
T_LC_BOOL btnIntkUp;
T_LC_BOOL btnIntkDown;
bool btnInvertDriveModifier;
bool btnInvertDriveFwd;
bool btnInvertDriveLft;
bool btnInvertDriveRev;
bool btnInvertDriveRht;
bool btnSubroutineModifier;
bool btnSubroutine1;
bool btnSubroutine2;
bool btnSubroutine3;
bool btnSubroutine4;
bool btnDisablePots;

// SENSORS
int senLiftLPot;
int senLiftRPot;
int senSelectorPot;
int senPwrExpVoltage;
int senAddToAbsGyro; //Not actually a sensor, but it helps with computation.
int senAbsGyro;
int senLeftEdge;
int senRightEdge;
T_LC_INT senGyro;
T_LC_INT senLeftUS;
T_LC_INT senRightUS;
T_LC_INT senLeftQSE;
T_LC_INT senRightQSE;

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
int timerMaster;
unsigned int timerLCDScroll=0;
unsigned int timerLCDBacklight=0;
unsigned int timerAuto=0;
unsigned int timerRobotIdle=0;

// LCD MENU
T_LC_INT menuItem;
int menuScrStr=0;
int menuScrChar=0;
int menuDisplayPos;
bool menuItemActivated=false;
int menuChecklistItem=0;

//Sound
int sndIndexLift;
int sndIndexIntk;

//Autonomous
int  autoHitTarget;
//int autoNextCondition;
bool autoFoundLeft;
bool autoFoundRight;
bool autoDriveReady;
bool autoLiftReady;
bool autoIntkReady;
bool autoStrafeReady;
bool autoClockRunning = false;
int  autoStep;
int  autoStepCheck;
int  autoStepStatus;
T_LC_INT autoRoutine;

//System
bool sysAutoMode = false;
bool sysDisabledMode = false;
int  sysError = ERR_NONE;
int  sysLCDBacklight=LCD_ALWAYS_ON;
//bool sysVirtualAuto = false;
bool sysMotorTest = false;
bool sysMotorsEnabled = true;
char sysInvertDrive = false;
char sysInvertDriveOffset=DRV_FWD;
T_LC_INT sysState;
int  sysLooptime;

//Other
T_LC_STRING topLCDLine = "";
T_LC_STRING bottomLCDLine = "";

//PID
T_PID PIDLiftL;
T_PID PIDLiftR;
//T_PID PIDIntk; //Continuous intake; don't need.
T_PID PIDLineFollow;
T_PID PIDWallFollow;
T_PID PIDDriveL;
T_PID PIDDriveR;
T_PID PIDStrafeEncod;
T_PID PIDStrafeUltra;
T_PID PIDGyro;

//--Arrays--//
bool autoScriptTakeover[3]={0,0,0};
short mtrTarget[10]={0,0,0,0,0,0,0,0,0,0};
short mtrSlewed[10]={0,0,0,0,0,0,0,0,0,0};
short mtrTestEnabled[10]={0,0,0,0,0,0,0,0,0,0};
char slewConstants[3][10];

string batteryLevel[3];
string motorName[10];
const string autoName[NO_AUTO_ROUTINES][NO_AUTO_NAME_STRS]={
	//Names of each of our Autonomous routines
	"NONE | ","NONE | ","NONE | ",		//1
	"NONE | ","NONE | ","NONE | ",		//2
	"NONE | ","NONE | ","NONE | ",		//3
	"NONE | ","NONE | ","NONE | ",		//4
	"NONE | ","NONE | ","NONE | ",		//5
	"NONE | ","NONE | ","NONE | ",		//6
	"NONE | ","NONE | ","NONE | ",		//7
	"NONE | ","NONE | ","NONE | ",		//8
	"NONE | ","NONE | ","NONE | ",		//9
	"NONE | ","NONE | ","NONE | ",		//10
	"NONE | ","NONE | ","NONE | ",		//11
	"NONE | ","NONE | ","NONE | "};	//12
const string menuChecklist[NO_CHECKLIST_ITEMS*2]={
	"      ",	"Batteries in",
	"      ",	"Batts charged",
	" Power",	"Ex + Cortex on",
	"      ",	"Joy plugged in",
	"  Joy ",	"lights green",
	" Line ",	"followers down",
	"      ",	"Robot aligned",
	"      ",	"Correct auton",
	"      ",	"Preload in",
	" Robot",	"fits in 18\""};
const string menuItemName[NO_MENU_ITEMS]={
	"Time:",			//1 (case 0:)
	"Checklist:",
	"Dis/Enable Mtrs",
	"Battery Levels:",
	"Motor Test:",
	"Motor Test:",
	"Analog Value:",
	"Digital Value:"};
	/*
	"Left-Line Tile:",
	"Left-Line Line:",
	"Right-Line Tile:",
	"Right-Line Line:"};
	*/
unsigned int autoTimeRecord[NO_TIME_RECORDS];
