// ========================================================================================
// Description:       Zweite Seite mit Funktionsvariablen und Funktionen
// Mising:            Leider können die zusaetzlichen Sensoren
//                    nicht erfasst werden, mit der sich die Umdrehungen 
//                    der einzelnen Motoren erfasst werden koennen.
//                    Interrupt auf dem Arduino Uno or Duemilanove konnen 
//                    nur auf Pin 2 und 3 erfasst werden, die wiederum
//                    auf dem Shield keine Pins zur verfuegung stellt.
// ========================================================================================

// ========================================================================================
// all defines

#define PIN_595_LATCH 12              // Pin connected to ST_CP of 74HC595
#define PIN_595_CLOCK 4               // Pin connected to SH_CP of 74HC595
#define PIN_595_DATA 8                // Pin connected to DS of 74HC595
#define PIN_595_SHIFT_REG_EN 7        // enable the Shiftregister

#define PIN_OUTPUT_M1 11              // pwm pin to control M1 output
#define PIN_OUTPUT_M2 3               // pwm pin to control M2 output
#define PIN_OUTPUT_M3 6               // pwm pin to control M3 output
#define PIN_OUTPUT_M4 5               // pwm pin to control M4 output

// ========================================================================================
// shift values to control the outputs

                                      // all shift values to enable one
                                      // of connection outputs for M1, M2, M3 and M4
const int mOutputM1_A = 4;            // Output M1 A
const int mOutputM1_B = 8;            // Output M1 B
const int mOutputM2_A = 2;            // Output M2 A
const int mOutputM2_B = 16;           // Output M2 B
const int mOutputM3_A = 32;           // Output M3 A
const int mOutputM3_B = 128;          // Output M3 B
const int mOutputM4_A = 1;            // Output M4 A
const int mOutputM4_B = 64;           // Output M4 B

// ========================================================================================
// Must execute befor control the motorshield
void MotorShieldInitialize() {
  
  pinMode(PIN_OUTPUT_M1, OUTPUT);
  pinMode(PIN_OUTPUT_M2, OUTPUT);
  pinMode(PIN_OUTPUT_M3, OUTPUT);
  pinMode(PIN_OUTPUT_M4, OUTPUT);
  
  pinMode(PIN_595_LATCH, OUTPUT);
  pinMode(PIN_595_CLOCK, OUTPUT);
  pinMode(PIN_595_DATA, OUTPUT);
  
  pinMode(PIN_595_SHIFT_REG_EN, OUTPUT);
  
  digitalWrite(PIN_595_LATCH, LOW);
  digitalWrite(PIN_595_CLOCK, LOW);
  digitalWrite(PIN_595_DATA, LOW);

  SetMotorShildOn(false);
}

// ========================================================================================
// enable or disable the motorshield
// ----------------------------------------------------------------------------------------
// setOn    = take the shield on
void SetMotorShildOn(bool setOn) {

  if(setOn) {
    digitalWrite(PIN_595_SHIFT_REG_EN, LOW); 
  }
  else {
    digitalWrite(PIN_595_SHIFT_REG_EN, HIGH); 
  }
}

// ========================================================================================
// set all pwm to 0 and disable the motorshield
void MotorsStop() {

  SetRunMotors(0, 0, 0);
  SetMotorShildOn(false);
}

// ========================================================================================
// Motor drives forward
// Set get value and shift all register to one value and set the motor outputs
// ----------------------------------------------------------------------------------------
// speedValueLeft   = left side pwm value output 
// speedValueRight  = right side pwm value output
void SetForeward(int speedValueLeft, int speedValueRight) {

  int motorsOn = mOutputM1_B | mOutputM2_B | mOutputM3_A | mOutputM4_A;
  SetRunMotors(motorsOn, speedValueLeft, speedValueRight);
  
  SetMotorShildOn(true);
}

// ========================================================================================
// Motor drives backwards
// Set get value and shift all register to one value and set the motor outputs
// ----------------------------------------------------------------------------------------
// speedValueLeft   = left side pwm value output 
// speedValueRight  = right side pwm value output
void SetBackward(int speedValueLeft, int speedValueRight) {
  
  int motorsOn = mOutputM1_A | mOutputM2_A | mOutputM3_B | mOutputM4_B;
  SetRunMotors(motorsOn, speedValueLeft, speedValueRight);

  SetMotorShildOn(true);
}

// ========================================================================================
// Set left motors forward and right motors backwards
// ----------------------------------------------------------------------------------------
// speedValue       = pwm value for all motors
void SetTurnLeft(int speedValue) {

  int motorsOn = mOutputM1_B | mOutputM2_B | mOutputM3_B | mOutputM4_B;
  SetRunMotors(motorsOn, speedValue, speedValue);
  SetMotorShildOn(true);
}

// ========================================================================================
// Set left motors backwards and right motors forwards
// ----------------------------------------------------------------------------------------
// speedValue       = pwm value for all motors
void SetTurnRight(int speedValue) {

  int motorsOn = mOutputM1_A | mOutputM2_A | mOutputM3_A | mOutputM4_A;
  SetRunMotors(motorsOn, speedValue, speedValue);
  SetMotorShildOn(true);
}

// ========================================================================================
// Set target output and level output on motor driver
// ----------------------------------------------------------------------------------------
// motorsOn         = shift register value to take on the outputs
// speedValueLeft   = left side pwm value output 
// speedValueRight  = right side pwm value output
void SetRunMotors(int motorsOn, int speedValueLeft, int speedValueRight) {
  
  SetOutputValue(speedValueLeft, speedValueRight);
  
  digitalWrite(PIN_595_LATCH, LOW);
  shiftOut(PIN_595_DATA, PIN_595_CLOCK, MSBFIRST, motorsOn); //GetShiftValue(m));
  digitalWrite(PIN_595_LATCH, HIGH);
}

// ========================================================================================
// Set level output on motor driver
// ----------------------------------------------------------------------------------------
// speedValueLeft   = left side pwm value output 
// speedValueRight  = right side pwm value output
void SetOutputValue(int speedValueLeft, int speedValueRight) {

  analogWrite(PIN_OUTPUT_M1, speedValueRight);  // right
  analogWrite(PIN_OUTPUT_M2, speedValueRight);

  analogWrite(PIN_OUTPUT_M3, speedValueLeft);  // left
  analogWrite(PIN_OUTPUT_M4, speedValueLeft);
}

