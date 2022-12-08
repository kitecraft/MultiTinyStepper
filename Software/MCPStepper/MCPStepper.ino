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
MtsStepper* stepper3;
MtsStepper* stepper4;

// the setup function runs once when you press reset or power the board
void setup() {
	delay(500);
	Serial.begin(115200);
	Serial.println("\n\nStarting....");
	
	Wire.begin(4, 5);
	Serial.print("Clock: ");
	Serial.println(Wire.getClock());
	//Wire.setClock(100000);
	//Serial.print("Clock: ");
	//Serial.println(Wire.getClock());

	g_stepperController.begin(Wire, MCP23017_DEFAULT_ADDR);

	stepper1 = g_stepperController.getStepper(MTS_STEPPER_1);
	stepper2 = g_stepperController.getStepper(MTS_STEPPER_2);
	stepper3 = g_stepperController.getStepper(MTS_STEPPER_3);
	stepper4 = g_stepperController.getStepper(MTS_STEPPER_4);

	stepper1->setType(MTS_STEPPER_TYPE_64);
	stepper1->setSpeedInStepsPerSecond(200);
	stepper1->setAccelerationInStepsPerSecondPerSecond(200);
	stepper1->setCurrentPositionInSteps(0);

	stepper2->setType(MTS_STEPPER_TYPE_64);
	stepper2->setSpeedInStepsPerSecond(400);
	stepper2->setAccelerationInStepsPerSecondPerSecond(400);
	stepper2->setCurrentPositionInSteps(0);

	stepper3->setType(MTS_STEPPER_TYPE_64);
	stepper3->setSpeedInStepsPerSecond(600);
	stepper3->setAccelerationInStepsPerSecondPerSecond(600);
	stepper3->setCurrentPositionInSteps(0);

	stepper4->setType(MTS_STEPPER_TYPE_64);
	stepper4->setSpeedInStepsPerSecond(800);
	stepper4->setAccelerationInStepsPerSecondPerSecond(800);
	stepper4->setCurrentPositionInSteps(0);

}

// the loop function runs over and over again until power down or reset
void loop() {
	bool complete = false;
	Serial.println("Going");
	stepper1->setTargetPositionInSteps(2000);
	stepper2->setTargetPositionInSteps(2000);
	stepper3->setTargetPositionInSteps(2000);
	stepper4->setTargetPositionInSteps(2000);
	
	while (!complete) {
		bool a = stepper1->process();
		bool b = stepper2->process();
		bool c = stepper3->process();
		bool d = stepper4->process();
		if (a && b && c && d) {
			complete = true;
		}
	}

	delay(1000);
	Serial.println("Returning");
	complete = false;
	stepper1->setTargetPositionInSteps(0);
	stepper2->setTargetPositionInSteps(0);
	stepper3->setTargetPositionInSteps(0);
	stepper4->setTargetPositionInSteps(0);

	while (!complete) {
		bool a = stepper1->process();
		bool b = stepper2->process();
		bool c = stepper3->process();
		bool d = stepper4->process();
		if (a && b && c && d) {
			complete = true;
		}
	}
	delay(1000);
}
