//Constants
#if (_TARGET=="Robot")
static const int LIFT_L_OFFSET = 230; //if higher, side lowers
static const int LIFT_R_OFFSET = 205; //if lower, side raises

//Functions
void inputSensors(void)
	{
	//--Robot Sensors--//
	senGyro.curr =					SensorValue[GYRO];
	senLeftQSE.curr =				SensorValue[QUAD_LEFT];
	senRightQSE.curr =				SensorValue[QUAD_RIGHT];
	senLeftUS.curr =				SensorValue[ULTRA_LEFT];
	senRightUS.curr =				SensorValue[ULTRA_RIGHT];
	senSelectorPot =				SensorValue[POT_SELECTOR];
	senPwrExpVoltage =				SensorValue[PWR_EXP_VLTG];
	senLiftLPot.curr =	potReverse(SensorValue[POT_LIFTL]) + LIFT_L_OFFSET;
	senLiftRPot.curr =	potReverse(SensorValue[POT_LIFTR]) + LIFT_R_OFFSET;

	//--Sensor Irregularity Fixer--//
	slewLCInt(senGyro,3);		//Estimated .5
	slewLCInt(senLeftQSE,2);	//Estimated .33
	slewLCInt(senRightQSE,2);	//Estimated .33
	slewLCInt(senLeftUS,6);		//Estimated 2.5
	slewLCInt(senRightUS,6);	//Estimated 2.5
#else
void inputSensors(void)
	{
#endif

	if (senGyro.last>3000 && senGyro.curr<600)	senAddToAbsGyro += 3600;
	if (senGyro.last<600 && senGyro.curr>3000)	senAddToAbsGyro -= 3600;
	senAbsGyro = senAddToAbsGyro + senGyro.curr;
	}


/*This function returns a reversed value for pots
that were installed so that the number goes up
when the arm goes down, etc.
*/
static int potReverse(int INpot)
	{
	return (4095-INpot);
	}
