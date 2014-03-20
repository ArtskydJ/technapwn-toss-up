//Constants
static const int MIN_LOOP_MS = 5;

//Functions
/* The following function is run every time the
autonomous step advances. It sets the starting
values of each sensor for that step, for checking
the difference between them.
 For example, the starting gyro value is stored.
When the robot turns, it calculates the differ-
ence between the current value and the step-start
value, so it knows how far it has turned.
*/

/* This function sets the last-step values to the
current-step values and saves them for when the
current-step values are overwritten.
*/
void setAllLasts()
	{
	setLCDLasts();
	setOperatorLasts();

	//--Sensors--//
	setLastInt(&senGyro);
	setLastInt(&senLeftQSE);
	setLastInt(&senRightQSE);
	setLastInt(&senLeftUS);
	setLastInt(&senRightUS);

	//--System--//
	setLastInt(&sysState);
	setLastInt(&autoRoutine);
	}

/* This function keeps the loop time of the code
constant. The value MIN_LOOP_MS is the minimum
time the loop will take to iterate with it being
constant. If the iteration takes longer than the
minimum, then no delay is executed. If the
iteration is faster, than a delay is applied.
 To check how long an iteration normally takes,
define MIN_LOOP_MS as 0. Then, in the debugger,
watch sysLooptime.
*/
void constantLoopTime()
	{
	sysLooptime=time1[T4];
	while (time1[T4] < MIN_LOOP_MS)
		{}
	ClearTimer(T4);
	}


/* This function takes a min, and max value, and
a pointer to a variable. The variable is changed
so that it is no smaller than the min value, and
no larger than the max value.
*/
void capIntValue(int min,int &value,int max)
	{
	int temp = value;
	temp = (temp<min) ? (min):(temp);
	temp = (temp>max) ? (max):(temp);
	value = temp;
	}

	
/* This function calculates the proportional,
integral and derivative values for the specified
T_PID values. (See Definitions.c for T_PID.)
*/
int updatePIDController(T_PID &INPID, int INerror)
	{
	INPID.error.curr = INerror;
	INPID.integral = (INPID.integral * 4 / 5) + INPID.error.curr;
	INPID.derivative = INPID.error.curr - INPID.error.last;
	setLastInt(INPID.error);
	INPID.output = (float)(INPID.error.curr	* INPID.kp)
						+ (INPID.integral	* INPID.ki)
						+ (INPID.derivative	* INPID.kd);
	return (INPID.output);
	}


/* This function checks the voltage on the cortex
and power expander. It also checks if the robot
has been idle for over a minute. If one of these
is true, then sysError is set.
*/
void processErrors()
	{
#if (_TARGET=="Robot") //Gives the low battery error when emulated.
	sysError = ERR_NONE;
	//if (senPwrExpVoltage<7200)		sysError = ERR_LOW_POW_EX; //power expander voltage is not x1000
	//if (timerRobotIdle>=60000)		sysError = ERR_ROBOT_IDLE;
	if (nAvgBatteryLevel<1000)		sysError = ERR_LOW_CORTEX;
#endif
	}