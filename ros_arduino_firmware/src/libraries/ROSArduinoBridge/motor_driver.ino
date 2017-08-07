/***************************************************************
   Motor driver definitions

   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.

   *************************************************************/

#ifdef USE_BASE

#ifdef POLOLU_VNH5019
  /* Include the Pololu library */
  #include "DualVNH5019MotorShield.h"

  /* Create the motor driver object */
  DualVNH5019MotorShield drive;

  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined POLOLU_MC33926
  /* Include the Pololu library */
  #include "DualMC33926MotorShield.h"

  /* Create the motor driver object */
  DualMC33926MotorShield drive;

  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }

#elif defined L298N_DUAL_HBRIDGE

  boolean directionLeft = false;
  boolean directionRight = false;

  boolean direction(int i){
     if(i == LEFT){
        return directionLeft;
     }else{
        return directionRight;
     }
  }
  void initMotorController() {
  // set all the motor control pins to outputs
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  }

  void setMotorSpeed(int i, int spd) {
    if(spd>MAX_PWM){
      spd=MAX_PWM;
    }
       if(spd<-MAX_PWM){
      spd=-1*MAX_PWM;
    }
    if (i == LEFT){
        if(spd>=0){
            directionLeft = FORWARDS;
            digitalWrite(IN2, HIGH);
            digitalWrite(IN1, LOW);
            analogWrite(ENA, spd);
        }else if(spd < 0){
            directionLeft = BACKWARDS;
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            analogWrite(ENA, -spd);
        }
    }
    else {
        if(spd>=0){
            directionRight = FORWARDS;
            digitalWrite(IN4, HIGH);
            digitalWrite(IN3, LOW);
            analogWrite(ENB, spd);
        }else if(spd<0){
            directionRight = BACKWARDS;
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            analogWrite(ENB, -spd);
        }
    }
  }

  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined DF_DUAL_HBRIDGE
  
  void initMotorController() {
	  // set all the motor control pins to outputs
	  pinMode(M1, OUTPUT);
	  pinMode(M2, OUTPUT);
	  pinMode(M3, OUTPUT);
	  pinMode(E1, OUTPUT);
	  pinMode(E2, OUTPUT);
	  pinMode(E3, OUTPUT);
  }

  void setMotorSpeed(int i, int spd) {
	  if(spd>MAX_PWM){
		  spd=MAX_PWM;
	  }
	  if(spd<-MAX_PWM){
		  spd=-1*MAX_PWM;
	  }
	  if (i == WHEEL1){
		  if(spd>=0){
			  analogWrite (E1,spd);      //motor1 move forward at speed spd
			  digitalWrite(M1,HIGH);  
		  }else if(spd < 0){
			  analogWrite (E1,-spd);      //motor1 move backward at speed spd
			  digitalWrite(M1,LOW);
		  }
	  }
	  else if (i == WHEEL2){
		  if(spd>=0){
			  analogWrite (E2,spd);      //motor2 move forward at speed spd
			  digitalWrite(M2,HIGH);  
		  }else if(spd < 0){
			  analogWrite (E2,-spd);      //motor2 move backward at speed spd
			  digitalWrite(M2,LOW);
		  }
	  }
	  else {
		  if(spd>=0){
			  analogWrite (E3,spd);      //motor3 move forward at speed spd
			  digitalWrite(M3,HIGH); 
		  }else if(spd<0){
			  analogWrite (E3,-spd);      //motor3 move backward at speed spd
			  digitalWrite(M3,LOW);
		  }
	  }
  }

  void setMotorSpeeds(int wheel1Speed, int wheel2Speed, int wheel3Speed) {
	  setMotorSpeed(WHEEL1, wheel1Speed);
	  setMotorSpeed(WHEEL2, wheel2Speed);
	  setMotorSpeed(WHEEL3, wheel3Speed);
  }
#else
  #error A motor driver must be selected!
#endif

#endif
