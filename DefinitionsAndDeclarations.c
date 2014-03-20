//Definitions.c
//2013-05-06

/*FLAGS
 These flags are meant to be overall system
toggles that are easily turned off and on.
*/
//#define AUTON_BEEP
//#define SOUND_EFFECTS


#if (_TARGET=="Robot")
	#define PHYSICAL_ROBOT_TARGET
#endif

//#define PHYSICAL_ROBOT_TARGET //Fake a physical robot to the emulator

/*Automonous - Advanced functionality
 These #define's make the autonomous commands
easier to read and remake.
*/

#define LINE_EDGE     2500   //For edge sensors
#define LINE_PERCENT  0.2    //0=tile 1=tape
#define LINE_LO       1200   //Left Tile
#define LINE_HI       1960   //Left Tape
#define LINE_TARGET   LINE_LO + ((float)LINE_PERCENT * (LINE_HI - LINE_LO))

#define LIFT_P        (float)0.3
#define LINE_P        (float)0.1
#define WALL_P        (float)0.1
#define ENCODER_P     (float)1.0
#define SONAR_P       (float)0.6
#define GYRO_P        (float)2.0

#define straight(n)   (n),  (n)
#define turn2(n)      (n),  -(n)
#define turnL(n)      (n),  0
#define turnR(n)      0,    -(n)
#define gyro2(n)      (((n)-senGyro.curr)*GYRO_P), \
                     ((-(n)+senGyro.curr)*GYRO_P)
#define strafe(n)     0,    0,    (n)
#define stopped()     0,    0,    0
#define enc(n,m)      (((n)-senLeftQSE.curr)*ENCODER_P), \
                      (((m)-senRightQSE.curr)*ENCODER_P)
#define usL(n)        (((n)-senLeftUS.curr)*SONAR_P)
#define usR(n)        (((n)-senRightUS.curr)*SONAR_P)

//Operator, Autonomous - Lift Presets
//Make sure not to re-define LIFT_L or LIFT_R anywhere.
#define L_PRE_START      128
#define L_GRND			 128
#define L_DRIV			 129
#define L_STSH			 130
#define L_PRE_END        130
#define NO_LIFT_PRESETS	 (L_PRE_END-L_PRE_START+1)

//State
#define DISABLED     0
#define OPERATOR     1
#define AUTONOMOUS   2

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
#define BRAKE   5

#define NO_AUTO_ROUTINES  12
#define MIN_LOOP_MS       5

//Output - Slew
#define AUTO_DRV_SLEW     3
#define OPER_DRV_SLEW     3
#define AUTO_LIFT_SLEW    8
#define OPER_LIFT_SLEW    8
#define AUTO_INTK_SLEW    10
#define OPER_INTK_SLEW    10

//Autonomous
#define NO_TIME_RECORDS   100
#define PID_WAIT_MS       200
#define SENSOR_HIT        0
#define MIN_TIMEOUT       1
#define MAX_TIMEOUT       2
#define PID_ZONE          20



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
typedef enum {
	NOT_HIT = -1,
	NEXT = 0,
	PID = 1
	} T_SENSOR_STATUS;

typedef enum {
	TIME_LIMIT = 0,	//Time Limit
	DRIV_READY,	//Finished using Drive (including strafing)
	LIFT_READY,	//Finished using Lift
	FULL_READY,	//Finished using Drive and Lift
	ONE_EDG_LN,	//Cross Line
	TWO_EDG_LN,	//Line up on white line
	SCREEN_BTN	//Screen Button
	} T_END;

typedef enum {
	STO_NONE = 0,
	STO_TAKEOVER,
	STO_ADD
	} T_SCRIPT_TAKEOVER;

typedef enum {
	DRIVE = 0,
	LIFT,
	INTK
	} T_COMPONENT;

typedef enum {
	ERR_NONE = 0,
	ERR_LOW_CORTEX,
	ERR_LOW_POW_EX,
	ERR_ROBOT_IDLE
	} T_ERROR;

typedef enum {
	M_AUTON = 0,
	M_CHECKLIST,
	M_DIS_ENABLE_MTRS,
	M_BATT_LEVELS,
	M_MTR_TEST,
	M_ANALOG_LEVELS,
	M_DIGITAL_LEVELS,
	NO_MENU_ITEMS
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



/*Function Prototypes
 This is so that functions that used to give
"undefined procedure" errors will cease.
*/
void autoResetStart(int INgoToStep, T_AUTO_SCRIPT INasType, T_SCRIPT_TAKEOVER INstoType,
					bool INscriptDrive, bool INscriptLift, bool INscriptIntake);
void autoResetEnd(void);
void auto(int INspdL, int INspdR, int INspdS, int INlift, int INintk,
	T_END INendType, int INminTime, int INmaxTime, T_SENSOR_STATUS INdelayPID);
void zeroMotors(void);
void initializeAutonomous(void);
void initializeLCD(void);
void initializeOutput(void);
void stateSwitchToAutonomous(void);
void inputOperator(void);
void inputLCD(void);
void inputSensors(void);
bool joystickIsMoved(bool checkStkTrn);
void setLastInt(T_LC_INT *INLC);
void setStepInt(T_LC_INT *INLC);
static int potReverse(int INpot);
int joystickFilter(int INraw);
int slew(int INtargetValue, int INlastValue, int INslew);
int potPosition(int INMaxVal);
int emulateLiftPot(int INspeed, int INgearing);
int emulateWheelQSE(int INspeed);
void emulateSensors(void);


/* Declarations
 Constants, variables, etc.
*/
//Constants
const int L_PRESETS[NO_LIFT_PRESETS] = {230,255,1680};

//System Variables
bool sysAutoMode = false;
bool sysDisabledMode = false;
bool autoClockRunning = false;
bool sysMotorTest = false;
bool sysMotorsEnabled = true;
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

//Timer Variables
unsigned int timerElapsedTime	= 0;
unsigned int timerLCDScroll		= 0;
unsigned int timerLCDBacklight	= 0;
unsigned int timerAuto			= 0;
unsigned int timerRobotIdle		= 0;

//Other
bool autoScriptTakeover[3]={0,0,0};
short mtrTestEnabled[10]={0,0,0,0,0,0,0,0,0,0};
