### Wall-E project

A couple of years ago, I bought an arduino robot tank kit from <a href="https://kookye.com/2017/08/20/kookye-robot-tank-car-starter-kit-tutorial-introduction/">Kooky.</a>
The pakages included the Tank chasis, 2 tracks, 2 motors, 2 lights, a proximity meter, a buzzer, and an Arduino UNO + expantionboard for controlling the motors.
I decided to add an raspberry pi 3 B and a logitec webcam I had laying around.

As it fitted really nice under the hood, I connected the Arduino Uno to the Raspberry pi. This way I could connect over SSH to the Machine and upload the Adruino files directly.

## Connecting the Pi to the Adruino 

Updating your Pi and installing the software needed:



	sudo apt update
	sudo apt full-upgrade
	sudo apt install minicom arduino


Minicom is a clone of the MS-DOS "Telix" communication program. It emulates ANSI and VT102 terminals, has a dialing directory and auto zmodem download.
In this project we will use it to connect to the arduino 

Arduino is a pacakage where we will use the arduino-cli command to interact with the Arduino UNO

First we will create a new directory to store our program and config files, or download the GIT Repository.


	git clone https://github.com/spuzzelsnest/Tiger.git
	cd Tiger


To search and install the needed lirbraries you can use the following commands


	arduino-cli lib search servo

	  Updating index: library_index.json downloaded 
	  [ LIST CUT FROM EXAMPLE]

	arduino-cli lib install Servo
	arduino-cli lib list


To compile the file and store it on the Arduino


	adruino-cli compile --fqbn arduino:avr:uno Exanple


To connect to the Arduino we can use the Screen command


	screen /dev/ttyACM0 9600
