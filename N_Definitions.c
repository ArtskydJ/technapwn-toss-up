//Definitions.c
//2013-05-06

/*FLAGS
 These flags are meant to be overall system
toggles that are easily turned off and on.
*/
#define AUTON_BEEP
#define SOUND_EFFECTS
/*
#undef _TARGET			//This statement and the next go together. Uncomment both
#define _TARGET "Robot"	//If you want the emulator to act like a real robot.
// */

/*Preset Heights
 Heights for lift, etc.
*/
#define L_GRND		1000 //Make sure not to re-define LIFT_L or LIFT_R anywhere.
#define L_BARR		2000
#define L_STSH		3000


#define DISABLED	0
#define OPERATOR	1
#define AUTONOMOUS	2


/*Motor Speed Constants
 Shortcuts for autonomous writing.
*/
#define UP		 (127)
#define DOWN	(-127)
#define FWD		 (127)
#define REV		(-127)
#define LEFT	(-127)
#define RIGHT	 (127)
#define FULL	 (127)
#define HALF	 (64)
#define FOLLOW	 (100)
#define BRAKE	 (5) //can also be used in -Action- column

/*Line Following
 Edge, and line values
*/
#define EDGE_LINE_UP	2500

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
	int error;
	int integral;
	int derivative;
	int lastError;
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
	DT_IN_SPD,	//Drive with input Speeds
	DT_IN_ENC,	//Drive with input Encoder
	DT_C_LINE,	//Follow the Center Line
	DT_G_TURN,	//PID Gyroscope turn
	DT_LEFT_W,	//Follow the Left  Wall
	DT_RIHT_W	//Follow the Right Wall
	} T_DRIVE;

typedef enum
	{
	ST_IN_SPD,	//Strafe with input Speed
	ST_IN_ENC,	//Strafe to Encoder
	ST_U_LEFT,	//Strafe to the Left Wall
	ST_U_RIHT	//Strafe to the Right Wall
	} T_STRAFE;

typedef enum
	{
	ET_TIME_LIMIT,	//Time Limit
	ET_DRIV_READY,	//Finished using Drive (including strafing)
	ET_LIFT_READY,	//Finished using Lift
	ET_FULL_READY,	//Finished using Drive and Lift
	ET_ONE_EDG_LN,	//Cross Line
	ET_TWO_EDG_LN,	//Line up on white line
	ET_SCREEN_BTN	//Screen Button
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
 This is so that functions that give errors that
say "undefined procedure" will not give errors.
*/
void autoResetStart(int INgoToStep, T_AUTO_SCRIPT INasType, T_SCRIPT_TAKEOVER INstoType,
					bool INscriptDrive, bool INscriptLift, bool INscriptIntake);
void autoResetEnd(void);
void auto(T_DRIVE INdrvType, int INdrvLft, int INdrvRht, int INdrvTarget,
		T_STRAFE INstrfType, int INstrfSpeed, int INstrfTarget,
		int INlift, int INintk, T_END INendType, int INminTime, int INmaxTime, T_SENSOR_STATUS INdelayPID);
void zeroMotors(void);
void setLCDLasts(void);
void setOperatorLasts(void);
void initializeAutonomous(void);
void stateChangeLCD(void);
void stateSwitchToAutonomous(void);
void inputOperator(void);
void inputLCD(void);
void inputEmulator(void); //In N_Output.c
void inputSensors(void);
void inputTimers(void);
void setLastInt(T_LC_INT *INLC);
void setStepInt(T_LC_INT *INLC);
