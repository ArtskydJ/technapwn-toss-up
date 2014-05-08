#TechnaPWN Toss Up

##Intro
TechnaPWN's 2013-2014 code for their robot, Nora
Created by Joseph Dykstra of VRC Team #3018 for use during the 2013-2014 Vex Toss Up season

##Features:

+ Sense-Plan-Act paradigm
	+ Get and store sensor data in variables
	+ Decide what state it's in
	+ Process variables and decide how to act upon them
	+ Assign Motor, Solenoid, and LCD variables

+ Powerful Autonomous structure
	+ Concise, yet easy to read/edit
	+ Safe, built in time-out functionality
	+ Versatile
		+ Can end step via time limit, drive done, lifting done, etc.
		+ Can use PID control
		+ Can line follow
		+ Can follow wall with ultrasonic sensors

+ Slew controller, gradually changes motor power
	+ Motors don't hurt themselves as quickly
	+ Voltage drop is minimized, less likely to have brown-outs
	+ Less likely to tip robot when switching directions with a high COG

+ Operator control
	+ Code for strafing with mecanum wheels (would work with x-drive also)
	+ Built-in preset lift heights, with manual override
	+ Two-driver control setup, but one driver can do it all

+ Intuitive LCD menu system (Requires potentiometer also)
	+ Select and start autonomous routines, and view the elapsed time
	+ Checklist to see if bot is ready to compete
	+ Disable Motor/pneumatic control
	+ View Battery, Analog, Digital, and Motor values
	+ Advanced motor test

+ Other
	+ State friendly, if you lose connection during a match, it will not wait for autonomous selection before driver control is regained
	+ Autonomous and state switching data is logged in the debug stream
	+ Structures to easily set and compare previous values of a variable
	+ Ultrasonic deadzone, in case subsystems occasionally get in front of the sensor
	+ Can set LCD backlight to always off/on, blink fast/slow, or turn on for a few seconds every time an LCD button is pressed
	+ **Free** to use and modify!

##License
[MIT](http://opensource.org/licenses/MIT)