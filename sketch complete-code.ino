#include <AccelStepper.h>

// Define LDR pins
const int ldrPinTR = A2;  // LDR for UP_RIGHT
const int ldrPinTL = A1;  // LDR for UP_LEFT
const int ldrPinBR = A3;  // LDR for DOWN_RIGHT
const int ldrPinBL = A0;  // LDR for DOWN_LEFT

// Define stepper motor pins
#define motorPin1   2
#define motorPin2   3
#define motorPin3   4
#define motorPin4   5

#define motorPin11  9
#define motorPin12  10
#define motorPin13  11
#define motorPin14  12

// Create instances of AccelStepper for horizontal and vertical steppers
AccelStepper stepperHor(AccelStepper::FULL4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepperVer(AccelStepper::FULL4WIRE, motorPin11, motorPin13, motorPin12, motorPin14);

void setup()
 {
  // Set maximum speed and acceleration for horizontal stepper
  stepperHor.setMaxSpeed(1000.0);       // Adjust as needed
  stepperHor.setAcceleration(500.0);    // Adjust as needed

  // Set maximum speed and acceleration for vertical stepper
  stepperVer.setMaxSpeed(1000.0);       // Adjust as needed
  stepperVer.setAcceleration(500.0);    // Adjust as needed

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop()
 {
  // Read LDR values from all four LDRs
  int ldrValueTR = analogRead(ldrPinTR);
  int ldrValueTL = analogRead(ldrPinTL);
  int ldrValueBR = analogRead(ldrPinBR);
  int ldrValueBL = analogRead(ldrPinBL);

  // Calculate average values for vertical and horizontal axes
  int avgTop = (ldrValueTR + ldrValueTL) / 2;
  int avgBot = (ldrValueBR + ldrValueBL) / 2;
  int avgLeft = (ldrValueTL + ldrValueBL) / 2;
  int avgRight = (ldrValueTR + ldrValueBR) / 2;

  // Calculate differences between average values
  int diffTopBot = abs(avgTop - avgBot);
  int diffLeftRight = abs(avgLeft - avgRight);

  // Control vertical stepper based on difference between top and bottom LDR readings
  if (diffTopBot > 100) {
    if (avgBot > avgTop) {
       //Move stepperVer up

      stepperVer.moveTo(diffTopBot);  // Adjust steps and direction as needed

    } else if(avgTop > avgBot) {
      // Move stepperVer down

      stepperVer.moveTo(- diffTopBot);   // Adjust steps and direction as needed
    }
  } else
   {
    
   }

  // Control horizontal stepper based on difference between left and right LDR readings
  if (diffLeftRight > 100)
  {
    if (avgLeft > avgRight)
    {
      // Move stepperVer up
      stepperHor.moveTo(- diffLeftRight);  // Adjust steps and direction as needed
    } else if(avgRight > avgLeft) {
      // Move stepperVer down
      stepperHor.moveTo( diffLeftRight);   // Adjust steps and direction as needed
    }
  } else
   { 
   }

  // Move the steppers to their target positions
  stepperHor.run();
  stepperVer.run();

  // Print sensor readings and motor positions for debugging
  Serial.print("Avg Top: ");
  Serial.print(avgTop);
  Serial.print(" | Avg Bottom: ");
  Serial.println(avgBot);
  Serial.print(" | diffTopBot: ");
  Serial.println(diffTopBot);
  Serial.print("Avg Right: ");
  Serial.print(avgRight);
  Serial.print(" | Avg left: ");
  Serial.println(avgLeft);
  Serial.print(" | diffTopBot: ");
  Serial.println(diffLeftRight);
  // Add a short delay to control loop frequency
  delay(10);
}