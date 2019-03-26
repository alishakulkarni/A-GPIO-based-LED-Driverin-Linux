Team-4:

RITESH THAKUR (1215283069) [RGBled1.c Developer]
ALISHA KULKARNI (1215311903) [RGBled2.c Developer]
------------------------------------------------------------
==========Sequnce to run the code:

unexport ==========> RGBled_1.c/RGBled_2.c (It is important and neat to run unexport.c first)

------------------------------------------------------------------------------------------------
PLEASE NOTE: Code below means: RGBled_1.c, RGBled_2.c and Unexport.c
------------------------------------------------------------------------------------------------
MakeFile Instructions:

1. use "make clean" to clean the objects which the .c(s) will create to create the necessary objects.
2. use "make" to gcc compile the code.
3. use "make EXECUTION_ENV=GALILEO2" to compile code using i586-poky-linux-gcc. (THERE SHOULD BE NO SPACES AROUND "=" IN THIS EXAMPLE)

Path and IOT_HOME can be changed per user's convinience:

IOT_HOME = /opt/iot-devkit/1.7.2/sysroots/sysroots
PATH := $(PATH):$(IOT_HOME)/x86_64-pokysdk-linux/usr/bin/i586-poky-linux
-------------------------------------------------------------------------------------------------
MOUSE_DEV = "/dev/input/mice" (this is hard coded in the code but can be changed if user wants to use another input event)
-------------------------------------------------------------------------------------------------
For unexport.c
Please run unexport first to make sure that all the GPIOs are unexported before RGBled_1 and RGBled_2 program's execution start.
--------------------------------------------------------------------------------------------------
For RGBled_1.c

1. Use any pin from 0-13 as per instructions coming on terminal.
User needs to put pin input for Red, Green and Blue pin separately as user is asked during program's execution.

Led's intensity is hard coded to be 50%. Meaning it will be on for 20ms and off for 20ms. On/Off for a given LED (R, G, B, R&G, R&B, 
G&B, R&G&B) is total of 1 s. i.e RED will glow for 1 sec in total where after every 20ms it ll switch off and after every 20ms from off it ll glow for another 20ms. This is to ensure that LED is on for only 50% duration of total 1s. 

Same is done for all other LEDS in the program and all other combinations of LEDs.

IMPORTANT NOTE: MOUSE CLICKS ENSURE THAT LEDs SEQUNCE RESTARTS FROM RED AGAIN. HOWEVER, ONLY PRESS MOUSE BUTTON DURING THE 1s SLEEP. THIS IS SAID BECAUSE IF LET'S SAY USER PRESSES MOUSE WHEN LED VALUE IS 1 FOR EX. GREEN LED, ALTHOUGH SEQUNCE RESTARTS FROM RED BUT THAT PARTICULAR GPIO STAYS AT 1, WHICH MIXES TWO COLORS (MIXES WITH GREEN IN THIS QUOTED EXAMPLE).

----------------------------------------------------------------------------------------------------

For RGBled_2.c

1. Red is pin IO 11, Green is IO 9, Blue is IO 3. (I.E THIS PART OF CODE IS HARD CODED TO RUN ON MENTIONED PINS ONLY)

Total On duration for given LED or combination is 1 s where it stays on for 20ms and off for 20ms because of the duty cycle.

Mouse click ensures duty cycle is reduced by 10% (PLEASE NOTE AS PER ASSIGNMENT WE WERE NOT SUPPOSED TO RESTART SEQUNCE IN PART 2 SO CODE DOESNT DO THAT IN PART 2)

-----------------------------------------------------------------------------------------------------




