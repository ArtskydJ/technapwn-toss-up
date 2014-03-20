//Sound
static int sndIndexLift = 0;
static int sndIndexIntk = 0;

void outputSound()
	{
	if (sysError!=ERR_NONE && sysError!=ERR_ROBOT_IDLE)
		{
		if (timerLCDBacklight<10)
			PlayImmediateTone(784, 15);
		}
	else
		{
		if (0)//(outLift>64)
			{
			switch (sndIndexLift)
				{
				case 0: PlaySoundFile("GearClicking4.wav"); break;
				}
			sndIndexLift = (sndIndexLift+1)%1;	//The number "1" is the number of sounds available
			}
		if (0)//(outIntk>64)
			{
			switch (sndIndexIntk)
				{
				case 0: PlaySoundFile("Inception.wav"); break;
				case 1: PlaySoundFile("LaserFire.wav"); break;
				}
			sndIndexLift = (sndIndexLift+1)%2;	//The number "2" is the number of sounds available
			}
		}
	}
