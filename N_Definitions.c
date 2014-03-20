//Definitions.c
//2013-05-06

/*FLAGS
 These flags are meant to be overall system
toggles that are easily turned off and on.
*/
#define AUTON_BEEP
#define SOUND_EFFECTS
//#undef _TARGET			//This statement and the next go together. Uncomment both
//#define _TARGET "Robot"	//If you want the emulator to act like a real robot.

/*FUNCTIONS
 These function-like defines are for shortening
and simplifying the code.
 The ones that have INLC as an input are for
last/curr structs (declared below).
 There are some for autonomous values so that
different sensors can be used.
 There are also constants for these functions.
*/
#define checkTarget(cndtn,value)	(cndtn)?((value)>=INtarget):((value)<=INtarget)
#define capValue(Min,Value,Max)		Value = (Value<Min)? (Min):(Value); Value = (Value>Max)? (Max):(Value)
#define changed(INLC)				(INLC.last != INLC.curr)
#define pressed(INLC)				(!INLC.last && INLC.curr)
#define diffLast(INLC)				(INLC.curr - INLC.last)
#define diffStep(INLC)				(INLC.curr - INLC.stepStart)
#define setLast(INLC)				INLC.last = INLC.curr
#define setStep(INLC)				INLC.stepStart = INLC.curr
#define setToZero(INLC)				INLC.last=0; INLC.curr=0
#define fixIrregularity(INLC,n)		slew(INLC.curr,INLC.last,n)
#define INCH(n)						((float)n*360/(3.14*4))

/*VALUES
 These values are stored here for easy modifica-
tion of system constants.
 NO means Number-Of.
*/
#define NO_MENU_ITEMS		8
#define NO_AUTO_ROUTINES	12
#define NO_AUTO_NAME_STRS	3
//#define NO_AUTO_COLUMNS		9
#define NO_TIME_RECORDS		100
#define NO_CHECKLIST_ITEMS	10

/*Time
 Minimum Loop time; scrolling text next
character; PID delay (for autonomous); LCD blink
time, slow and fast; LCD timeout (untouched).
*/
#define MIN_LOOP_MS			5
#define NEXT_CHAR_MS		250
#define PID_WAIT_MS			200
#define LCD_BLINK_SLOW_MS	500
#define LCD_BLINK_FAST_MS	200
#define LCD_TIMEOUT_MS		5000

/*Preset Heights
 Heights for lift, etc.
*/
#define L_GROUND	1000 //Make sure not to use LIFT_L or LIFT_R anywhere.
#define L_BARRIER	2000
#define L_STASH		3000

/*Drive Direction
 This is for which direction the robot is pointed
so that the drive can be translated correctly.
*/
#define DRV_FWD 0
#define DRV_LFT 1
#define DRV_REV 2
#define DRV_RHT 3

/*Motor Speed Constants
 Shortcuts for autonomous writing.
*/
#define UP		 127
#define DOWN	-127
#define FWD		 127
#define REV		-127
#define LEFT	-127
#define RIGHT	 127
#define FULL	 127
#define HALF	 64
#define FOLLOW	 100
#define BRAKE	 5 //can also be used in -Action- column

/*Motor Slew Constants
 Values for how much to add to each motor value
each loop iteration.
*/
#define AUTO_DRV_SLEW	3
#define OPER_DRV_SLEW	3
#define AUTO_LIFT_SLEW	8
#define OPER_LIFT_SLEW	8
#define AUTO_INTK_SLEW	10
#define OPER_INTK_SLEW	10

/*Robot States
 What state the robot is currently in.
 DISABLED can also be used for disabling min or
max time in autonomous.
*/
#define DISABLED	0
#define OPERATOR	1
#define AUTONOMOUS	2


/*Hit Target
 These values are used in autonomous. If the end-
type is encoder, and the wheels have been driven
far enough, then the variable autoHitTarget is
set to NEXT. If the minimum time is higher than
the current time, it will not execute
autoNextStep() until it is.
 These values are also used as a trigger for a
delay to allow PID controllers to stablize before
the next step is executed.
*/
#define NOT_HIT	0
#define NEXT	1
#define PID		2

/*Script Takeover
 If the robot is in a script, parts of the robot
can be in 3 modes. None, Takeover or Add.
 None means if you mess with those controls, they
will not affect the robot.
 Takeover means if you mess with those controls,
they will stop the script and give the driver
full control.
 Add means if you mess with those controls, they
will add to the current controls. If you tell the
drive to go backward when it is going forward, it
will slow down the drive.
*/
#define ST_NONE		0
#define ST_TAKEOVER	1
#define ST_ADD		2

/*Errors
1 Low Cortex battery
2 Low Power Expander battery
3 Robot's been idle for a while (depletes battery)
*/
#define ERR_NONE		0
#define ERR_LOW_CORTEX	1
#define ERR_LOW_POW_EX	2
#define ERR_ROBOT_IDLE	3

/*Auton type
 There are two types of autonomous routines;
Scripts, and normal routines. Scripts are for
operator controlled periods while autos are for
the autonomous period.
*/
#define SCRIPT	0
#define AUTON	1

/*Script Takeover
 Scripts can take over certain parts of the robot.
For example, the lift and manipulators can be
taken over without the drive being taken over.
A script stops executing when one of it's taken
over parts is moved manually.
*/
#define DRIVE	0
#define LIFT	1
#define INTK	2

/*Next Condition
 These are for if the minimum or maximum time are
used in autonomous. If one is used, then a debug
stream message is sent to the debugger. In this
way, one can easily see which steps always time-
out.
*/
#define SENSOR_HIT	0
#define MIN_TIMEOUT	1
#define MAX_TIMEOUT	2

/*LCD Position
 Where to draw the menu text. The first menu item
does not have a < symbol before it, so it can be
drawn LEFT0. The second menu item does have a <
symbol before it, so it has to be shifted over to
LEFT1. Some text is short enough that it can be
drawn in the CENTER.
*/
#define LEFT0  0
#define LEFT1  1
#define CENTER 2

/*LCD Backlight modes
1 Always Off
2 Always On
3 Blink Slow
4 Blink Fast
5 Timeout (if a button is pressed, the backlight
lights for 5 seconds)
*/
#define LCD_ALWAYS_OFF	0
#define LCD_ALWAYS_ON	1
#define LCD_BLINK_SLOW	2
#define LCD_BLINK_FAST	3
#define LCD_TIMEOUT		4

/*Line Following
 Edge, and line definitions
*/
#define EDGE_LINE_UP	2500

/*Autonomous End and Drive types
 The Drive types are for how the robot drives.
For example:
1 Line Follow
2 Gyro Strafe
3 Normal Drive
 The End types are for what sensor triggers the
step to end.
For example:
1 Left Encoder
2 Absolute Left Ultrasonic
3 Lift Potentiometer
*/
// End Types
#define TIME_LIMIT	0	// Time Limit
#define DRIV_READY	1	// Finished using Drive
#define LIFT_READY	2	// Finished using Lift
#define FULL_READY	3	// Finished using Drive and Lift
#define ONE_EDG_LN	4	// Cross Line
#define	TWO_EDG_LN	5	// Line up on white line
#define SCREEN_BTN	6	// Screen Button
// Drive Types [OBSOLETE]
/*
#define CNTR_LINE   128	// Follow the Center Line
#define GYRO_BOTH	129	// PID Gyroscope turn both wheels
#define GYRO_LEFT	130 // PID Gyroscope turn left wheels only
#define GYRO_RIHT	131 // PID Gyroscope turn right wheels only
#define LEFT_WALL	133	// Follow the Left  Wall
#define RIHT_WALL	134	// Follow the Right Wall
#define MAX_TYPES	135 // Maximum amount of allocated drive type numbers
*/

/*Miscellaneous defined values
 The joystick dead zone is so that small values
on the joystick are ignored. This is so that the
robot will not drift or "lock" the motors in
operator mode.
*/
#define JOYSTICK_DEAD_ZONE	10			//If the joystick is within this amount, ignore it
#define PID_ZONE			20			//If the PID error is within this amount, it is close enough to its target
#define outDrvL				outDrvX		//In autonomous, use X as Left
#define outDrvR				outDrvY		//In autonomous, use Y as Right
#define outDrvS				outDrvZ		//In autonomous, use Z as Strafe
#define INdrvType			INdrvLft	//In autonomous, use Left input as drive type
#define INdrvSpeed			INdrvRht	//In autonomous, use Right input as target speed
#define INdrvTarget			INdrvStrafe	//In autonomous, use Strafe input as target distance/rotation.
#define STRF_SPEED			0			//In autonomous, strafe input uses these...
#define STRF_ENC			1			//...
#define STRF_L_US			2			//...
#define STRF_R_US			3			//...Until here

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
	}
	T_LC_BOOL;

typedef struct
	{
	int curr;
	int last;
	int stepStart;
	}
	T_LC_INT;

typedef struct
	{
	string curr;
	string last;
	}
	T_LC_STRING;

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
	}
	T_PID;

/*Function Prototypes
 This is so that functions that give errors that
say "undefined procedure" will not give errors.
*/
void autoResetStart(int INgoToStep, int INautoType, int INscriptTakeoverType, bool INscriptDrive, bool INscriptLift, bool INscriptIntake);
void autoResetEnd();
void auto(int INdrvLft, int INdrvRht, int INdrvStrafe, int INlift, int INintk, int INendType, int INminTime, int INmaxTime, int INdelayPID);
