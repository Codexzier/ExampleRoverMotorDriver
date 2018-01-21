// ========================================================================================
//      Meine Welt in meinem Kopf
// ========================================================================================
// Projekt:       Example Motor Driver
// Author:        Johannes P. Langner
// Controller:    Arduino
// Receiver:      
// Sensor:        
// Actor:         Motor Shield, Rover
// Description:   Grundlage codestyle zu meinen Blog
// Stand:         21.01.2018
// ========================================================================================

// ========================================================================================
void setup() {
  Serial.begin(115200);

  MotorShieldInitialize();
}

// ========================================================================================
void loop() {

  Serial.println("Motor On: SetForeward");
  SetForeward(200, 200);
  delay(1000);

  Serial.println("Motor On: SetBackward");
  SetBackward(200, 200);
  delay(1000);

  Serial.println("Motor On: SetTurnLeft 200");
  SetTurnLeft(200);
  delay(1000);

  Serial.println("Motor On: SetTurnRight 200");
  SetTurnRight(200);
  delay(1000);
  
  Serial.println("Motor Off");
  MotorsStop();
  delay(1000);
}




