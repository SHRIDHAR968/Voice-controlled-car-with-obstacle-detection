#include <SoftwareSerial.h>

// ================= BLUETOOTH =================
SoftwareSerial BT(10, 11);   // RX, TX

// ================= MOTOR DRIVER =================
#define ENA 5
#define IN1 2
#define IN2 3

#define IN3 4
#define IN4 7
#define ENB 6

// ================= ULTRASONIC =================
#define FRONT_TRIG 8
#define FRONT_ECHO 9

#define REAR_TRIG A0
#define REAR_ECHO A1

// ================= BUZZER =================
#define BUZZER 12

// ================= SETTINGS =================
int speedValue = 180;
int turnSpeed = 150;

int obstacleDistance = 20;

// =================================================
// SETUP
// =================================================
void setup()
{
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(FRONT_TRIG, OUTPUT);
  pinMode(FRONT_ECHO, INPUT);

  pinMode(REAR_TRIG, OUTPUT);
  pinMode(REAR_ECHO, INPUT);

  pinMode(BUZZER, OUTPUT);

  stopCar();

  Serial.println("Voice Controlled Car Ready");
}

// =================================================
// MAIN LOOP
// =================================================
void loop()
{
  // Check Bluetooth command
  if (BT.available())
  {
    char command = BT.read();

    Serial.print("Command: ");
    Serial.println(command);

    // Convert lowercase to uppercase
    command = toupper(command);

    switch (command)
    {
      case 'F':
        moveForward();
        break;

      case 'B':
        moveBackward();
        break;

      case 'L':
        turnLeft();
        break;

      case 'R':
        turnRight();
        break;

      case 'S':
        stopCar();
        break;

      default:
        break;
    }
  }
}

// =================================================
// ULTRASONIC DISTANCE
// =================================================
long getDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0)
    return 999;

  long distance = duration * 0.034 / 2;

  return distance;
}

// =================================================
// FORWARD
// =================================================
void moveForward()
{
  long distance = getDistance(FRONT_TRIG, FRONT_ECHO);

  Serial.print("Front Distance: ");
  Serial.println(distance);

  if (distance <= obstacleDistance)
  {
    stopCar();

    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);

    Serial.println("Obstacle detected!");
    return;
  }

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);
}

// =================================================
// BACKWARD
// =================================================
void moveBackward()
{
  long distance = getDistance(REAR_TRIG, REAR_ECHO);

  Serial.print("Rear Distance: ");
  Serial.println(distance);

  if (distance <= obstacleDistance)
  {
    stopCar();

    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);

    Serial.println("Rear obstacle detected!");
    return;
  }

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, speedValue);
  analogWrite(ENB, speedValue);
}

// =================================================
// LEFT
// =================================================
void turnLeft()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
}

// =================================================
// RIGHT
// =================================================
void turnRight()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
}

// =================================================
// STOP
// =================================================
void stopCar()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}