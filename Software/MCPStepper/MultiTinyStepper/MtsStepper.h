#pragma once
#include <Arduino.h>
#include <functional>
#include <stdlib.h>

#define MTS_STEPPER_TYPE_16_REV 513
#define MTS_STEPPER_TYPE_64_REV 2038

#define MTS_STEPPER_TYPE_16 0
#define MTS_STEPPER_TYPE_64 1



enum MTS_STEPPER_ID {
    MTS_STEPPER_1 = 0,
    MTS_STEPPER_2,
    MTS_STEPPER_3,
    MTS_STEPPER_4
};

enum MTS_STEPPER_STEP_TYPE {
    MTS_STEPPER_FULL_STEP = 0,
    MTS_STEPPER_HALF_STEP
};

enum MTS_STEPPER_PHASE {
    MTS_STEPPER_PHASE_1 = 0,
    MTS_STEPPER_PHASE_2,
    MTS_STEPPER_PHASE_3,
    MTS_STEPPER_PHASE_4,
    MTS_STEPPER_PHASE_5,
    MTS_STEPPER_PHASE_6,
    MTS_STEPPER_PHASE_7,
    MTS_STEPPER_PHASE_8
};


typedef std::function<void(uint8_t, uint8_t)> processStepHandler;

class MtsStepper
{
private:

    void DeterminePeriodOfNextStep();
    //void setNextFullStep();

    int8_t _stepPhase;
    float _stepsPerMillimeter;
    int8_t _stepsPerRevolution;
    int _directionOfMotion;
    long _currentPosition_InSteps;
    long _targetPosition_InSteps;
    float _desiredSpeed_InStepsPerSecond;
    float _desiredPeriod_InUSPerStep;
    float _acceleration_InStepsPerSecondPerSecond;
    float _acceleration_InStepsPerUSPerUS;
    float _periodOfSlowestStep_InUS;
    float _minimumPeriodForAStoppedMotion;
    float _nextStepPeriod_InUS;
    unsigned long _lastStepTime_InUS;
    float _currentStepPeriod_InUS;
    
    

public:
    MtsStepper();
    processStepHandler processStep = nullptr;

    /*
    Sets the stepsPerRevolution for the appropriate stepper type
    MTS_STEPPER_TYPE_64 = 2038
    MTS_STEPPER_TYPE_16 = 513
    */
    void setType(int type);
    void setCallback(processStepHandler fn) { processStep = fn; }

    void setStepsPerRevolution(float motorStepPerRevolution);
    void setStepsPerMillimeter(float motorStepPerMillimeter);

    // Functions which use Steps

    void setSpeedInStepsPerSecond(float speedInStepsPerSecond);
    void setAccelerationInStepsPerSecondPerSecond(float accelerationInStepsPerSecondPerSecond);
    void setCurrentPositionInSteps(long currentPositionInSteps);
    long getCurrentPositionInSteps();
    //void moveRelativeInSteps(long distanceToMoveInSteps);
    //void setTargetPositionRelativeInSteps(long distanceToMoveInSteps);
    //void moveToPositionInSteps(long absolutePositionToMoveToInSteps);
    //void setTargetPositionInSteps(long absolutePositionToMoveToInSteps);
    //void setTargetPositionToStop();
    //float getCurrentVelocityInStepsPerSecond();

    //bool moveToHomeInSteps(long directionTowardHome, float speedInStepsPerSecond, long maxDistanceToMoveInSteps, int homeSwitchPin);


    //void deadStop();

    bool motionComplete();

    /*
    DO NOT CALL THIS! It is used by MultiTinyStepper
    returns true and sets the currentStepPhase if a move is required
    returns false if no move is required
    */
    //bool processStep(int8_t &currentStepPhase);
};

