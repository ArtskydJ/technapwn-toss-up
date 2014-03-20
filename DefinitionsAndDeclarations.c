//DefinitionsAndDeclarations.c

#define AUTON_BEEP
#define SOUND_EFFECTS
//#define   FULL_DEBUG_STREAM
//#define PHYSICAL_ROBOT_TARGET //Uncomment to fake a physical robot to the emulator
#if (_TARGET=="Robot")
	#ifndef PHYSICAL_ROBOT_TARGET
		#define PHYSICAL_ROBOT_TARGET
	#endif
#endif
#define START_WITH_OUTPUTS_ENABLED  true

//Line Following
#define LINE_EDGE     2500   //For edge sensors
#define LINE_PERCENT  0.2    //0=tile 1=tape
#define LINE_LO       1200   //Left Tile
#define LINE_HI       1960   //Left Tape
#define LINE_TARGET   LINE_LO + ((float)LINE_PERCENT * (LINE_HI - LINE_LO))

//State
#define DISABLED     0
#define OPERATOR     1
#define AUTONOMOUS   2

//Proportional Constants
#define LIFT_P        (float)1.0
#define LINE_P        (float)0.1
#define WALL_P        (float)0.1
#define ENCODER_P     (float)1.0
#define SONAR_P       (float)0.6
#define GYRO_P        (float)0.2

//Autonomous - Functions
#define straight(n)   (n),  (n)
#define turn2(n)      (n),  -(n)
#define turnL(n)      (n),  0
#define turnR(n)      0,    (n)
#define gyro2(n)      ((n)*10-senGyro.curr)*GYRO_P, (-(n)*10+senGyro.curr)*GYRO_P
#define strafe(n)     0,    0,    (n)
#define stopped()     0,    0,    0
#define enc(n,m)      (n-senLeftQSE.curr)*ENCODER_P, ((m)-senRightQSE.curr)*ENCODER_P
#define usL(n)        (n-senLeftUS.curr)*SONAR_P
#define usR(n)        (n-senRightUS.curr)*SONAR_P
#define L_CST(n)      (n-senLiftPot.curr)*LIFT_P
#define L_PRE(n)      (sysLiftPresets[n]-senLiftPot.curr)*LIFT_P

//Autonomous - Presets
#define UP      127
#define DOWN   -127
#define FWD     127
#define REV    -127
#define IN     -127
#define OUT     127
#define LEFT   -127
#define RIGHT   127
#define FULL    127
#define HALF    64
#define FOLLOW  100
#define BRAKE   5  //Drive brake power

//Output - Slew
#define AUTO_DRV_SLEW     2
#define OPER_DRV_SLEW     2
#define AUTO_LIFT_SLEW    8
#define OPER_LIFT_SLEW    8
#define AUTO_INTK_SLEW    20
#define OPER_INTK_SLEW    20

//Autonomous
#define NO_TIME_RECORDS   100
#define PID_WAIT_MS       350
#define SENSOR_HIT        0
#define MIN_TIMEOUT       1
#define MAX_TIMEOUT       2
#define P_DEAD_ZONE       20
#define NO_AUTO_ROUTINES  12
#define MIN_LOOP_MS       5

////////////////////////////////////////////////////////////////////////////////

//Structs
typedef struct
	{
	bool curr;
	bool last;
	} T_LC_BOOL;

typedef struct
	{
	int curr;
	int last;
	int stepStart;
	} T_LC_INT;

typedef struct
	{
	string curr;
	string last;
	} T_LC_STRING;

typedef struct
	{
	float kp;
	float ki;
	float kd;
	T_LC_INT error;
	int integral;
	int derivative;
	int output;
	} T_PID;

//Enums
typedef enum {
	NOT_HIT = -1,
	NEXT = 0,
	PID = 1
	} T_SENSOR_STATUS;

typedef enum {
	TIME_LIMIT = 0,	//Time Limit
	DRIV_READY,	//Finished using Drive (including strafe)
	LIFT_READY,	//Finished using Lift
	FULL_READY,	//Finished using Drive and Lift
	ONE_EDG_LN,	//Cross Line
	TWO_EDG_LN,	//Line up on white line
	SCREEN_BTN	//Screen Button
	} T_END;

typedef enum {
	DRIVE = 0,
	LIFT,
	INTK,
	NO_SUBSYSTEMS
	} T_SUBSYSTEM;

typedef enum {
	ERR_NONE = 0,
	ERR_LOW_CORTEX,
	ERR_LOW_POW_EX,
	ERR_ROBOT_IDLE
	} T_ERROR;

typedef enum {
	M_AUTON = 0,
	M_ENABLE_OUT,
	M_CHECKLIST,
	M_BATTERY,
	M_MTR_TEST,
	M_ANALOG,
	M_DIGITAL,
	M_MOTOR,
	M_VOLUME,
	M_NO_ITEMS
	} T_MENU_ITEMS;

typedef enum {
	LCD_ALWAYS_OFF = 0,
	LCD_ALWAYS_ON,
	LCD_BLINK_SLOW,
	LCD_BLINK_FAST,
	LCD_TIMEOUT
	} T_BACKLIGHT;

typedef enum {
	SCRIPT,
	AUTON
	} T_AUTO_SCRIPT;

typedef enum {
	L_GRND = 0,
	L_BARR,
	L_STSH,
	NO_LIFT_PRESETS
	} T_LIFT_PRESETS;

////////////////////////////////////////////////////////////////////////////////

//Constants
const int sysLiftPresets[NO_LIFT_PRESETS] = {1655,2395,3055};

//System Variables
bool sysAutoMode = false;
bool sysDisabledMode = false;
bool autoClockRunning = false;
bool sysMotorTest = false;
bool sysOutputsEnabled = START_WITH_OUTPUTS_ENABLED;
int  sysLCDBacklight=LCD_ALWAYS_ON;
T_ERROR sysError = ERR_NONE;
T_LC_INT autoRoutine;
T_LC_INT sysState;
bool btnDisablePots;
int liftPresetIndex = L_BARR;

//Output Variables
int outDrvL;
int outDrvR;
int outDrvS;
int outLift;
int outIntk;
bool outCatapult;
//bool outBrake;

//Sensor Variables
int senSelectorPot;
//int senPwrExpVoltage;
int senLeftEdge;
int senRightEdge;
T_LC_INT senLiftPot;
T_LC_INT senGyro;
T_LC_INT senLeftUS;
T_LC_INT senRightUS;
T_LC_INT senLeftQSE;
T_LC_INT senRightQSE;

//LCD Buttons
T_LC_BOOL btnScreenLeft;
T_LC_BOOL btnScreenCenter;
T_LC_BOOL btnScreenRight;

//Timer Variables
unsigned int timerElapsedTime	= 0;
unsigned int timerLCDScroll		= 0;
unsigned int timerLCDBacklight	= 0;
unsigned int timerAuto			= 0;
unsigned int timerRobotIdle		= 0;

//Other
bool autoScriptTakeover[NO_SUBSYSTEMS]={0,0,0};
short mtrTestEnabled[10]={0,0,0,0,0,0,0,0,0,0};

////////////////////////////////////////////////////////////////////////////////

//Function Prototypes
void autoResetStart(int INgoToStep, T_AUTO_SCRIPT INasType,
					bool INscriptDrive, bool INscriptLift, bool INscriptIntake);
void autoResetEnd(void);
void auto(int INspdL, int INspdR, int INspdS, int INlift, int INintk, T_END INendType, int INextra);
void zeroMotors(void);
void stateSwitchToAutonomous(void);
void inputOperator(void);
void inputSensors(void);
bool joystickIsMoved(bool checkStkTrn);
void setLastInt(T_LC_INT *INLC);
void setStepInt(T_LC_INT *INLC);
static int potReverse(int INpot);
int joystickFilter(int INraw);
int slew(int INtargetValue, int INlastValue, int INslew);
int potPosition(int INMaxVal);
int emulateLiftPot(int INtimer, int INspeed, int INgearing);
int emulateWheelQSE(int INtimer, int INspeed);
int emulateGyro(int INtimer, int INleft, int INright);
