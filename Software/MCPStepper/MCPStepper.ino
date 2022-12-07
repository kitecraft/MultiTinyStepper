/*
 Name:		MCPStepper.ino
 Created:	12/5/2022 6:32:11 PM
 Author:	Kitecraft
*/

#include "MultiTinyStepper/MultiTinyStepper.h"
#include "MultiTinyStepper/MtsStepper.h"

MultiTinyStepper g_stepperController;
MtsStepper* stepper1;
MtsStepper* stepper2;

// the setup function runs once when you press reset or power the board
void setup() {
	delay(500);
	Serial.begin(115200);
	Serial.println("\n\nStarting....");
	
	Wire.begin(4, 5);
	g_stepperController.begin(Wire, MCP23017_DEFAULT_ADDR);

	stepper1 = g_stepperController.getStepper(MTS_STEPPER_1);
	stepper2 = g_stepperController.getStepper(MTS_STEPPER_2);
	stepper1->setAccelerationInStepsPerSecondPerSecond(100);

	//stepper1->setSpeedInStepsPerSecond(100);
	
	
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	for (uint8_t i = 0; i < 4; i++) {
		stepper1->processStep(i, MTS_STEPPER_FULL_STEP);
		for (uint8_t j = 0; j < 4; j++) {
			stepper2->processStep(j, MTS_STEPPER_FULL_STEP);
			delay(150);
		}
	}
}
