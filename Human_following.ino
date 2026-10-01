#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
SCREEN_WIDTH,
SCREEN_HEIGHT,
&Wire,
-1);

Servo scanner;

//---------------PIN----------------

#define LEFT_IR 2
#define SERVO_PIN 3
#define RIGHT_IR 4

#define ENA 5
#define ENB 6

#define IN1 7
#define IN2 8

#define IN3 9
#define IN4 10

#define TRIG 11
#define ECHO 12

//----------------------------------

#define MOTOR_SPEED 255
#define TURN_SPEED 200

#define MIN_DISTANCE 10
#define MAX_DISTANCE 30

//----------------------------------

void setup()
{
  Serial.begin(9600);

  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  scanner.attach(SERVO_PIN);
  scanner.write(90);

  display.begin(
    SSD1306_SWITCHCAPVCC,
    0x3C);

  display.clearDisplay();
  display.display();

  stopRobot();
}

//----------------------------------

float getDistance()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);

  if(duration == 0)
    return 100;

  return duration * 0.034 / 2;
}

//----------------------------------

float scanAt(int angle)
{
  scanner.write(angle);
  delay(300);

  return getDistance();
}

//----------------------------------

void showDistance(float d)
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(0,0);
  display.print("DIST");

  display.setCursor(0,30);
  display.print((int)d);
  display.print("cm");

  display.display();
}

//----------------------------------

void moveForward()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  analogWrite(ENA,MOTOR_SPEED);
  analogWrite(ENB,MOTOR_SPEED);
}

//----------------------------------

void moveBackward()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);

  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  analogWrite(ENA,MOTOR_SPEED);
  analogWrite(ENB,MOTOR_SPEED);
}

//----------------------------------

void turnLeft()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);

  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  analogWrite(ENA,TURN_SPEED);
  analogWrite(ENB,TURN_SPEED);
}

//----------------------------------

void turnRight()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  analogWrite(ENA,TURN_SPEED);
  analogWrite(ENB,TURN_SPEED);
}

//----------------------------------

void stopRobot()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);

  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);

  analogWrite(ENA,0);
  analogWrite(ENB,0);
}

//----------------------------------

void loop()
{
  float distance = scanAt(90);

  showDistance(distance);

  int leftIR = digitalRead(LEFT_IR);
  int rightIR = digitalRead(RIGHT_IR);

  // Stop if too close

  if(distance > 0 && distance < MIN_DISTANCE)
  {
    stopRobot();
  }

  // Turn Left

  else if(leftIR == LOW && rightIR == HIGH)
  {
    turnLeft();
  }

  // Turn Right

  else if(leftIR == HIGH && rightIR == LOW)
  {
    turnRight();
  }

  // Follow

  else if(distance >= MIN_DISTANCE &&
          distance <= MAX_DISTANCE)
  {
    moveForward();
  }

  // Search

  else
  {
    stopRobot();

    float leftDistance = scanAt(0);
    float rightDistance = scanAt(180);

    scanner.write(90);

    if(leftDistance > rightDistance)
    {
      turnLeft();
      delay(300);
    }
    else
    {
      turnRight();
      delay(300);
    }

    stopRobot();
  }

  delay(50);
}