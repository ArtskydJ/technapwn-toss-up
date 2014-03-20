//Definitions.c
//2013-05-06

/*FLAGS
 These flags are meant to be overall system
toggles that are easily turned off and on.
*/
//#define AUTON_BEEP
//#define SOUND_EFFECTS
//#define LIFT_SYNC

//*
#undef _TARGET			//This statement and the next go together. Uncomment both
#define _TARGET "Robot"	//If you want the emulator to act like a real robot.
// */

/*Preset Heights
 Heights for lift, etc.
*/
#define L_GRND			0 //Make sure not to re-define LIFT_L or LIFT_R anywhere.
#define L_DRIV			1
#define L_STSH			2
#define NO_LIFT_PRESETS	3


#define DISABLED	0
#define OPERATOR	1
#define AUTONOMOUS	2

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
#define BRAKE   5

#define NO_AUTO_ROUTINES 12

//--Typedefs--//
/*Structs
T means type
LC means Last/Current (see function-like defines
above; after flags, before values.)
PID means Proportional, Integral and Derivative.
*/
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

//**Other
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

/*Enums*/
/*Sensor Statuses
 If sensor is hit.
*/
typedef enum
	{
	NOT_HIT = -1,
	NEXT = 0,
	PID = 1
	} T_SENSOR_STATUS;

typedef enum
	{
	SPEED = 0,   //Drive/Strafe with input Speeds
	ENCODER,    //Drive/Strafe with input Encoder
	LEFT_WALL,  //Drive following/Strafe to the Left  Wall
	RIGHT_WALL, //Drive following/Strafe to the Right Wall
	//LINE_FOLLOW,  //Drive following the Center Line
	GYRO_TURN   //Drive with a PID gyroscope turn
	} T_DRIVE;

typedef enum
	{
	TIME_LIMIT = 0,	//Time Limit
	DRIV_READY,	//Finished using Drive (including strafing)
	LIFT_READY,	//Finished using Lift
	FULL_READY,	//Finished using Drive and Lift
	ONE_EDG_LN,	//Cross Line
	TWO_EDG_LN,	//Line up on white line
	SCREEN_BTN	//Screen Button
	} T_END;

typedef enum
	{
	STO_NONE = 0,
	STO_TAKEOVER,
	STO_ADD
	} T_SCRIPT_TAKEOVER;

typedef enum
	{
	DRIVE = 0,
	LIFT,
	INTK
	} T_COMPONENT;

typedef enum
	{
	ERR_NONE = 0,
	ERR_LOW_CORTEX,
	ERR_LOW_POW_EX,
	ERR_ROBOT_IDLE
	} T_ERROR;

typedef enum
	{
	M_AUTON = 0,
	M_CHECKLIST,
	M_DIS_ENABLE_MTRS,
	M_BATT_LEVELS,
	M_MTR_TEST,
	M_ANALOG_LEVELS,
	M_DIGITAL_LEVELS,
	NO_MENU_ITEMS
	} T_MENU_ITEMS;

typedef enum
	{
	LCD_ALWAYS_OFF = 0,
	LCD_ALWAYS_ON,
	LCD_BLINK_SLOW,
	LCD_BLINK_FAST,
	LCD_TIMEOUT
	} T_BACKLIGHT;

typedef enum
	{
	SCRIPT,
	AUTON
	} T_AUTO_SCRIPT;



/*Function Prototypes
 This is so that functions that used to give
"undefined procedure" errors will cease.
*/
void autoResetStart(int INgoToStep, T_AUTO_SCRIPT INasType, T_SCRIPT_TAKEOVER INstoType,
					bool INscriptDrive, bool INscriptLift, bool INscriptIntake);
void autoResetEnd(void);
/*void auto(const T_DRIVE INdrvType, const int INdrvLft, const int INdrvRht, const int INdrvTarget,
		const T_DRIVE INstrfType, const int INstrfSpeed, const int INstrfTarget,
		const int INlift, const int INintk, const T_END INendType,
		const int INminTime, const int INmaxTime, const T_SENSOR_STATUS INdelayPID);*/
void auto(T_DRIVE INdrvType, int INdrvSpd, int INdrvTarget,
          T_DRIVE INstfType, int INstfSpd, int INstfTarget,
          int INlift, int INintk, T_END INendType,
          int INminTime, int INmaxTime, T_SENSOR_STATUS INdelayPID);
void zeroMotors(void);
void initializeAutonomous(void);
void initializeLCD(void);
void initializeOutput(void);
void stateSwitchToAutonomous(void);
void inputOperator(void);
void inputLCD(void);
void inputSensors(void);
void inputTimers(void);
bool joystickIsMoved(bool checkStkTrn);
void setLastInt(T_LC_INT *INLC);
void setStepInt(T_LC_INT *INLC);
static int potReverse(int INpot);
int joystickFilter(int INraw);
int slew(int INtargetValue, int INlastValue, int INslew);
int potPosition(int INMaxVal);
int emulateLiftPot(int INspeed, int INgearing);
int emulateWheelQSE(int INspeed);


/* Declarations
 Constants, variables, etc.
*/
//Constants
const int L_PRE[NO_LIFT_PRESETS] = {230,255,1680};

//System Variables
float sysLiftP = 0.7; //change to const, move to output.c, make static
bool sysAutoMode = false;
bool sysDisabledMode = false;
bool autoClockRunning = false;
bool sysMotorTest = false;
bool sysMotorsEnabled = true;
int  sysLooptime;	//Global for viewing in debug window
int  sysLCDBacklight=LCD_ALWAYS_ON;
T_ERROR sysError = ERR_NONE;
T_LC_INT autoRoutine;
T_LC_INT sysState;
bool btnDisablePots;
int liftPresetIndex = L_DRIV;


//Output Variables
int outDrvL;
int outDrvR;
int outDrvS;
int outLift;
int outIntk;
bool outBrake;


//Sensor Variables
int senSelectorPot;
int senPwrExpVoltage;
int senLeftEdge;
int senRightEdge;
T_LC_INT senLiftLPot;
T_LC_INT senLiftRPot;
T_LC_INT senGyro;
T_LC_INT senLeftUS;
T_LC_INT senRightUS;
T_LC_INT senLeftQSE;
T_LC_INT senRightQSE;

//Other
bool autoScriptTakeover[3]={0,0,0};
short mtrTestEnabled[10]={0,0,0,0,0,0,0,0,0,0};
