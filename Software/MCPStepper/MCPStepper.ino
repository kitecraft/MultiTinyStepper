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
	
	Wire.begin(4, 5, 1000000);
	g_stepperController.begin(Wire, MCP23017_DEFAULT_ADDR);

	stepper1 = g_stepperController.getStepper(MTS_STEPPER_1);
	stepper2 = g_stepperController.getStepper(MTS_STEPPER_2);
	stepper3 = g_stepperController.getStepper(MTS_STEPPER_3);
	stepper4 = g_stepperController.getStepper(MTS_STEPPER_4);

	//Serial.println("Stepper 1");
	stepper1->setStepperType(MTS_STEPPER_TYPE_64, MTS_STEPPER_FULL_STEP);
	stepper1->setSpeedInStepsPerSecond(600);
	stepper1->setAccelerationInStepsPerSecondPerSecond(600);

	//Serial.println("\nStepper 2");
	stepper2->setStepperType(MTS_STEPPER_TYPE_64, MTS_STEPPER_HALF_STEP);
	stepper2->setSpeedInStepsPerSecond(800);
	stepper2->setAccelerationInStepsPerSecondPerSecond(800);
	
	//Serial.println("\nStepper 3");
	stepper3->setStepperType(MTS_STEPPER_TYPE_16, MTS_STEPPER_FULL_STEP);
	stepper3->setStepsPerMillimeter(10);
	stepper3->setSpeedInMillimetersPerSecond(30);
	stepper3->setAccelerationInMillimetersPerSecondPerSecond(30);

	//Serial.println("\nStepper 4");
	stepper4->setStepperType(MTS_STEPPER_TYPE_64, MTS_STEPPER_HALF_STEP);
	stepper4->setSpeedInStepsPerSecond(800);
	stepper4->setAccelerationInStepsPerSecondPerSecond(800);
}

// the loop function runs over and over again until power down or reset
void loop() {
	bool complete = false;

	stepper1->setTargetPositionInSteps(MTS_STEPPER_TYPE_64_REV);
	stepper2->setTargetPositionInRevolutions(1);
	stepper3->setTargetPositionInMillimeters(MTS_STEPPER_TYPE_64_REV/10);
	stepper4->setTargetPositionRelativeInSteps(MTS_STEPPER_TYPE_64_REV);
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

	complete = false;
	stepper1->setTargetPositionInSteps(0); // will spin in reverse
	stepper2->setTargetPositionInRevolutions(0); // will spin in reverse
	stepper3->setTargetPositionInMillimeters(0); // will spin in reverse
	stepper4->setTargetPositionRelativeInSteps(MTS_STEPPER_TYPE_64_REV); //will still spin foward
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
