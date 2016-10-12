
#include <Arduino.h>

//Global Variables
const byte BUTTON = 2 ; // our button pin
const byte SENSOR = 3;
const byte CYLINDERBIG = 4; // CYLINDERBIG (built-in on Uno)
const byte CYLINDERSMALL = 5;
const byte LEDBIG = 6;
const byte ledSmall = 7;

byte comando = 0;

unsigned long buttonPushedMillis; // when button was released
unsigned long relayTurnedOnAt; // when CYLINDERBIG was turned on
unsigned long turnOnDelay = 000; // wait to turn on CYLINDERBIG
unsigned long turnOnDelay1 = 3000;
unsigned long turnOnLedB = 000;
unsigned long turnOnLedS = 3000;
unsigned long turnOffDelay = 9000; // turn off CYLINDERBIG after this
unsigned long turnOffDelay1 = 7000;
unsigned long turnOffLedB = 000;
unsigned long turnOffLedS = 7000;

bool ledReady = false; // flag for when button is let go
bool ledReady1 = false;
bool ledBigReady = false;
bool ledSmallReady = false;
bool ledState = false; // for CYLINDERBIG is on or not.
bool ledState1 = false;
bool ledBigState = false;
bool ledSmallState = false;

void setup() {
	pinMode(SENSOR, INPUT);
	pinMode(BUTTON, INPUT_PULLUP);
	pinMode(CYLINDERBIG, OUTPUT);
	pinMode(CYLINDERSMALL, OUTPUT);
	pinMode(LEDBIG, OUTPUT);
	pinMode(ledSmall, OUTPUT);
	digitalWrite(CYLINDERBIG, HIGH);
	digitalWrite(CYLINDERSMALL, HIGH);
	digitalWrite(LEDBIG, LOW);
	digitalWrite(ledSmall, HIGH);
}

void loop() {
	// get the time at the start of this loop()
	unsigned long currentMillis = millis();
	int estado1 = digitalRead(BUTTON);
	int estado2 = digitalRead(SENSOR);

	if (estado1 == LOW && estado2 == LOW) {
		comando = 0;
	}

	else
		if (estado1 == LOW && estado2 == HIGH) {
			comando = 1;
		}

	switch (comando) {
	case 0:
		if (digitalRead(BUTTON) == LOW) {
			// update the time when button was pushed
			buttonPushedMillis = currentMillis;
			ledReady = true;
			ledReady1 = true;
			ledBigReady = true;
			ledSmallReady = true;
		}

		// make sure this code isn't checked until after button has been let go
		if (ledReady) {
			//this is typical millis code here:
			if ((unsigned long)(currentMillis - buttonPushedMillis) >= turnOnDelay) {
				// okay, enough time has passed since the button was let go.
				digitalWrite(CYLINDERBIG, LOW);
				// setup our next "state"
				ledState = true;
				// save when the CYLINDERBIG turned on
				relayTurnedOnAt = currentMillis;
				// wait for next button press
				ledReady = false;
			}
		}

		if (ledReady1) {
			//this is typical millis code here:
			if ((unsigned long)(currentMillis - buttonPushedMillis) >= turnOnDelay1) {
				// okay, enough time has passed since the button was let go.
				digitalWrite(CYLINDERSMALL, LOW);
				// setup our next "state"
				ledState1 = true;
				// save when the CYLINDERBIG turned on
				relayTurnedOnAt = currentMillis;
				// wait for next button press
				ledReady1 = false;
			}
		}

		if (ledBigReady) {
			//this is typical millis code here:
			if ((unsigned long)(currentMillis - buttonPushedMillis) >= turnOnLedB) {
				// okay, enough time has passed since the button was let go.
				digitalWrite(LEDBIG, LOW);
				// setup our next "state"
				ledBigState = true;
				// save when the CYLINDERBIG turned on
				relayTurnedOnAt = currentMillis;
				// wait for next button press
				ledBigReady = false;
			}
		}

		if (ledState) {
			// okay, CYLINDERBIG on, check for now long
			if ((unsigned long)(currentMillis - relayTurnedOnAt) >= turnOffDelay) {
				ledState = false;
				digitalWrite(CYLINDERBIG, HIGH);
			}
		}

		if (ledState1) {
			// okay, CYLINDERBIG on, check for now long
			if ((unsigned long)(currentMillis - relayTurnedOnAt) >= turnOffDelay1) {
				ledState1 = false;
				digitalWrite(CYLINDERSMALL, HIGH);
			}
		}

		// see if we are watching for the time to turn off CYLINDERBIG
		if (ledBigState) {
			// okay, CYLINDERBIG on, check for now long
			if ((unsigned long)(currentMillis - relayTurnedOnAt) >= turnOffLedB) {
				ledReady = false;
				digitalWrite(LEDBIG, HIGH);
			}
		}

		break;

	case 1:
		if (digitalRead(BUTTON) == LOW) {
			// update the time when button was pushed
			buttonPushedMillis = currentMillis;
			ledReady = true;
		}

		// make sure this code isn't checked until after button has been let go
		if (ledReady) {
			//this is typical millis code here:
			if ((unsigned long)(currentMillis - buttonPushedMillis) >= turnOnDelay) {
				// okay, enough time has passed since the button was let go.
				digitalWrite(CYLINDERBIG, HIGH);
				// setup our next "state"
				ledState = true;
				// save when the CYLINDERBIG turned on
				relayTurnedOnAt = currentMillis;
				// wait for next button press
				ledReady = false;
			}
		}

		break;
	}
}


