//Constants
static const int L_OFFSET = -300;


void inputSensors(void)
	{
#if (_TARGET=="Robot")
	//--Robot Sensors--//
	senGyro.curr =				SensorValue[GYRO];
	senLeftQSE.curr =			SensorValue[QUAD_LEFT];
	senRightQSE.curr =			SensorValue[QUAD_RIGHT];
	senLeftUS.curr =			SensorValue[ULTRA_LEFT];
	senRightUS.curr =			SensorValue[ULTRA_RIGHT];
	senSelectorPot.curr =		SensorValue[POT_SELECTOR];
	senPwrExpVoltage =			SensorValue[PWR_EXP_VLTG];
	senLiftLPot.curr =			SensorValue[POT_LIFTL];
	senLiftRPot.curr =			SensorValue[POT_LIFTR]+L_OFFSET; //Offset

	//--Sensor Irregularity Fixer--//
	fixIrregularity(senGyro,3);		//Estimated .5
	fixIrregularity(senLeftQSE,2);	//Estimated .33
	fixIrregularity(senRightQSE,2);	//Estimated .33
	fixIrregularity(senLeftUS,6);	//Estimated 2.5
	fixIrregularity(senRightUS,6);	//Estimated 2.5
#endif

	if (senGyro.last>3000 && senGyro.curr<600)	senAddToAbsGyro += 3600;
	if (senGyro.last<600 && senGyro.curr>3000)	senAddToAbsGyro -= 3600;
	senAbsGyro = senAddToAbsGyro + senGyro.curr;
	}
