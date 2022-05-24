#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>

#define TRIG_PIN A4
#define ECHO_PIN A5
#define MAX_DISTANCE 200
#define MAX_SPEED 100
#define MAX_SPEED_OFFSET 10
#define COLL_DIST 10
#define TURN_DIST COLL_DIST+10

NewPing sonar (TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1 (1, MOTOR12_1KHZ) ;
AF_DCMotor motor2(2, MOTOR12_1KHZ) ;
AF_DCMotor motor3(3, MOTOR12_1KHZ) ;
AF_DCMotor motor4(4, MOTOR12_1KHZ) ;

Servo myservo;

int pos = 0;
int maxDist = 0;
int maxAngle = 0;
int maxRight = 0;
int maxLeft = 0;
int maxFront = 0;
int course = 0;
int curDist = 0;
String motorSet="";
int speedSet = 0;

void checkPath();
void moveBackward();
void checkBackward();
void moveStop();
void checkCourse();
void changePath();
int readPing();
void checkForward();
void moveForward();
void turnRight();
void turnLeft();
void veerRight();
void setCourse();
void veerLeft();


void setup() {
  motor1.setSpeed(60);
  motor2.setSpeed(60);
  motor3.setSpeed(60);
  motor4.setSpeed(60);
  myservo.attach(9);
  myservo.write(90);
  delay (2000) ;
  checkPath();
  motorSet = "FORWARD" ;
  myservo.write(90);
  //moveForward();
}

void loop() {
  checkForward();
  checkPath();
}

void moveBackward(){
  motorSet = "BACKWARD";
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2){
    motor1.setSpeed (speedSet+MAX_SPEED_OFFSET);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet+MAX_SPEED_OFFSET);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}
void checkBackward(){
  if (motorSet=="BACKWARD") {
    motor1.run(BACKWARD) ;
    motor2.run(BACKWARD) ;
    motor3.run(BACKWARD) ;
    motor4.run (BACKWARD) ;
  }
}

void moveStop(){
  motor1.run(RELEASE);
  motor2.run (RELEASE);
  motor3.run (RELEASE);
  motor4.run (RELEASE);
} // stop the motors.

void checkCourse(){
  moveBackward();
  delay (500) ;
  moveStop();
  setCourse();
}

void checkPath() {
  int curLeft = 0;
  int curFront = 0;
  int curRight = 0;
  int curDist = 0;
  myservo.write(144);
  delay (120) ;
  for (pos = 144; pos >= 36; pos-=18){
    myservo.write(pos);
    delay(90) ;
    checkForward();
    curDist = readPing();
    if (curDist < COLL_DIST){
      checkCourse();
      break;
    }
    if (curDist < TURN_DIST) {
    changePath();
    }
    if (curDist > curDist) {maxAngle = pos;}
    if (pos > 90 && curDist > curLeft) { curLeft = curDist;}
    if (pos == 90 && curDist > curFront) {curFront = curDist;}
    if (pos < 90 && curDist > curRight) {curRight = curDist;}
  }
  maxLeft = curLeft;
  maxRight = curRight;
  maxFront = curFront;
}





void changePath(){
  if (pos < 90) {veerLeft();}
  if (pos > 90) {veerRight () ;}
}

int readPing(){
  delay (70) ;
  unsigned int uS = sonar.ping() ;
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}

void checkForward(){
  if (motorSet=="FORWARD") {
    motor1.run(FORWARD) ;
    motor2.run (FORWARD) ;
    motor3.run (FORWARD) ;
    motor4.run(FORWARD) ;
  }
}






void moveForward(){
  motorSet = "FORWARD";
  motor1.run (FORWARD) ;
  motor2. run (FORWARD) ;
  motor3. run (FORWARD);
  motor4.run (FORWARD);
  for (speedSet; speedSet & MAX_SPEED; speedSet +=2){
    motor1.setSpeed(speedSet+MAX_SPEED_OFFSET);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet+MAX_SPEED_OFFSET);
    motor4.setSpeed(speedSet);
    delay (5) ;
  }
}




void turnRight() {
  motorSet = "RIGHT";
  motor1.run (BACKWARD) ;
  motor2. run (BACKWARD) ;
  motor3. run (FORWARD);
  motor4. run (FORWARD);
  
  delay (400) ;
  motorSet = "FORWARD" ;
  motor1. run(FORWARD) ;
  motor2.run (FORWARD) ;
  motor3.run(FORWARD) ;
  motor4.run (FORWARD) ;
}



void turnLeft(){
  motorSet = "LEFT";
  motor1.run(FORWARD) ;
  motor2.run(FORWARD);
  motor3.run (BACKWARD) ;
  motor4.run (BACKWARD);
  delay (400) ;
  motorSet = "FORWARD" ;
  motor1.run (FORWARD) ;
  motor2.run (FORWARD) ;
  motor3.run (FORWARD);
  motor4.run (FORWARD) ;
}

void veerRight () {
  motor1.run(BACKWARD);
  delay (400) ;
  motor1.run(FORWARD) ;
  motor2.run(BACKWARD);
  delay (400) ;
  motor2.run (FORWARD) ;
}

void setCourse(){
  if (maxAngle < 90) {turnRight();}
  if (maxAngle > 90) {turnLeft();}
  maxLeft = 0;
  maxRight = 0;
  maxFront = 0;
}

void veerLeft(){
  motor3.run (BACKWARD) ;
  delay (400) ;
  motor3. run(FORWARD) ;
  motor4.run (BACKWARD) ;
  delay (400) ;
  motor4. run (FORWARD) ;
}
