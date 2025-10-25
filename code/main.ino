#include <ESP32Servo.h>
#include <Arduino.h>

//OLED display - GyverHub.h, GyverOLED, and bitmaps in a seperate file


//for servos condesned - "legFL_base" means leg_front_left_base "
Servo legFL_Base, legFL_Foot;
Servo legFR_Base, legFR_Foot;
Servo legRL_Base, legRL_Foot;
Servo legRR_Base, legRR_Foot;
//defining neutral position, currently estimated :( left foot is 160, front right is 20
/*
FL = Front Left
FR = Front Right
RL = Rear Left
RR = Rear right
*/
#define FL_BASE_ZERO 90
#define FL_FOOT_ZERO 160
#define FR_BASE_ZERO 90
#define FR_FOOT_ZERO 20
#define RL_BASE_ZERO 90
#define RL_FOOT_ZERO 20
#define RR_BASE_ZERO 90
#define RR_FOOT_ZERO 160

//how far the joints move (THANK YOU RANDOM SPIDER CODE)
#define LEG_UP_DEGREE 60 //left each leg 60 during a setp
#define WALK_DEGREE 45   //base moves 45 degrees each forward/back step
#define ROTATE_DEGREE    //How far to rotate side each rotatoin
#define MAX_DEVIATION 2  //small correction for tolerance, makes it so that if its within 2 its fine

//timing
#define STEP_DELAY_TIME 200
#define FORCED_HOME_DELAY_TIME 30

//servo range - minimum pwm
#define SERVO_MIN_US 500
#define SERVO_MAX_US 2400

//bools to define mode
#define MODE_IDLE 0
#define MODE_WALK_FORWARD 1
#define MODE_WALK_BACKWARD 2


//MOVEMEENT GIJORIOJRIO
void idle() {
  legFL_Base.write(FL_BASE_ZERO);
  legFL_Foot.write(FL_FOOT_ZERO);

  legFR_Base.write(FR_BASE_ZERO);
  legFR_Foot.write(FR_FOOT_ZERO);

  legRL_Base.write(RL_BASE_ZERO);
  legRL_Foot.write(RL_FOOT_ZERO);

  legRR_Base.write(RR_BASE_ZERO);
  legRR_Foot.write(RR_FOOT_ZERO);

  delay(FORCED_HOME_DELAY_TIME);
}

//walk forward? wtf is this code it looks disgusting
void walkForward(){
  //Lift front-left and rear-right legs
  legFL_Foot.write(FL_FOOT_ZERO - LEG_UP_DEGREE); //ts why I defined so much
  legRR_Foot.write(RR_FOOT_ZERO - LEG_UP_DEGREE);
  delay(STEP_DELAY_TIME)

  //move legs that are now lifted foward
  legFL_Base.write(FL_BASE_ZERO - WALK_DEGREE);
  legRR_Base.write(RR_BASE_ZERO + WALK_DEGREE);  //forward is opposite for the rear side
  delay(STEP_DELAY_TIME);

  //lower legs
  legFL_Foot.write(FL_FOOT_ZERO);
  leg_RR_Foot.write(RR_FOOT_ZERO);
  delay(STEP_DELAY_TIME);

  // Lift other side now :( same code but backwards
  legFR_Foot.write(FR_FOOT_ZERO - LEG_UP_DEGREE);
  legRL_Foot.write(RL_FOOT_ZERO - LEG_UP_DEGREE);
  delay(STEP_DELAY_TIME);
  //move forward
  legFR_Base.write(FR_BASE_ZERO - WALK_DEGREE);
  legRL_Base.write(RL_BASE_ZERO + WALK_DEGREE); //forward is opposite for the rear side
  delay(STEP_DELAY_TIME);
  //lower
  legFR_Foot.write(FR_FOOT_ZERO);
  legRL_Foot.write(RL_FOOT_ZERO);
  delay(STEP_DELAY_TIME);

  //return to home now :( ts was so useless
  idle();
}

//I assume base would just be this but backwards lol

void loop(){
  walkForward();
  delay(500);
  idle();
  delay(1000);
}


  






