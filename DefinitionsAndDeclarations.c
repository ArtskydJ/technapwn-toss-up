//Definitions.c
//2013-05-06

/*FLAGS
 These flags are meant to be overall system
toggles that are easily turned off and on.
*/
#define AUTON_BEEP
#define SOUND_EFFECTS
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

#define LIFT_EIGHTEEN	500


#define DISABLED	0
#define OPERATOR	1
#define AUTONOMOUS	2


/*Miscellaneous defined values
 The joystick dead zone is so that small values
on the joystick are ignored. This is so that the
robot will not drift or "lock" the motors in
operator mode.
*/
#define outDrvL				outDrvX		//In autonomous, use X as Left
#define outDrvR				outDrvY		//In autonomous, use Y as Right
#define outDrvS				outDrvZ		//In autonomous, use Z as Strafe

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
	NOT_HIT,
	NEXT,
	PID
	} T_SENSOR_STATUS;

typedef enum
	{
	IN_SPEED,		//Drive/Strafe with input Speeds
	ENCODER,	//Drive/Strafe with input Encoder
	LEFT_WALL,	//Drive following/Strafe to the Left  Wall
	RIGHT_WALL,	//Drive following/Strafe to the Right Wall
	//LINE_FOLLOW,	//Drive following the Center Line
	GYRO_TURN	//Drive with a PID gyroscope turn
	} T_DRIVE;

typedef enum
	{
	TIME_LIMIT,	//Time Limit
	DRIV_READY,	//Finished using Drive (including strafing)
	LIFT_READY,	//Finished using Lift
	FULL_READY,	//Finished using Drive and Lift
	ONE_EDG_LN,	//Cross Line
	TWO_EDG_LN,	//Line up on white line
	SCREEN_BTN	//Screen Button
	} T_END;

typedef enum
	{
	STO_NONE,
	STO_TAKEOVER,
	STO_ADD
	} T_SCRIPT_TAKEOVER;

typedef enum
	{
	DRIVE,
	LIFT,
	INTK
	} T_COMPONENT;

typedef enum
	{
	ERR_NONE,
	ERR_LOW_CORTEX,
	ERR_LOW_POW_EX,
	ERR_ROBOT_IDLE
	} T_ERROR;

typedef enum
	{
	LCD_ALWAYS_OFF,
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
void auto(T_DRIVE INdrvType, int INdrvLft, int INdrvRht, int INdrvTarget,
		T_DRIVE INstrfType, int INstrfSpeed, int INstrfTarget,
		int INlift, int INintk, T_END INendType,
		int INminTime, int INmaxTime, T_SENSOR_STATUS INdelayPID);
void zeroMotors(void);
void setLCDLasts(void);
void setOperatorLasts(void);
void initializeAutonomous(void);
void initializeLCD(void);
void initializeOutput(void);
void stateChangeLCD(void);
void stateSwitchToAutonomous(void);
void inputOperator(void);
void inputAutonomous(void);
void inputLCD(void);
void inputEmulator(void); //In N_Output.c
void inputSensors(void);
void inputTimers(void);
bool joystickIsMoved(bool checkStkZ);
void setLastInt(T_LC_INT *INLC);
void setStepInt(T_LC_INT *INLC);
void updateBatteryString(void);
static int potReverse(int INpot);
int joystickFilter(int INraw);
int slew(int INtargetValue, int INlastValue, int INslew);


/* Declarations
 Constants, variables, etc.
*/
//Constants
const int L_PRE[NO_LIFT_PRESETS] = {230,255,1680};
const int UP = 127;
const int DOWN = -127;
const int FWD = 127;
const int REV = -127;
const int IN = -127;
const int OUT = 127;
const int LEFT = -127;
const int RIGHT = 127;
const int FULL = 127;
const int HALF = 64;
const int FOLLOW = 100;
const int BRAKE = 5;

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
int outDrvX;
int outDrvY;
int outDrvZ;
int outLift;
int outIntk;

//Fake Timer Variables
unsigned int timerLCDScroll		= 0;
unsigned int timerLCDBacklight	= 0;
unsigned int timerAuto			= 0;
unsigned int timerRobotIdle		= 0;
unsigned int timerEmulateSpeed	= 0;

//Sensor Variables
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

//Other
bool autoScriptTakeover[3]={0,0,0};
short mtrTestEnabled[10]={0,0,0,0,0,0,0,0,0,0};
