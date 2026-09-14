/*
  Arduino Bluetooth Controlled Car with Mecanum Wheels
  Using AFMotor Library for L293D Shield
  Bluetooth on A0 (RX) and A1 (TX)
*/

#include <AFMotor.h>  // Use AFMotor.h, not AFMotor_R4.h
#include <SoftwareSerial.h>

// Bluetooth on A0 (RX) and A1 (TX)
// On Arduino, A0 = 14, A1 = 15
SoftwareSerial bluetoothSerial(14, 15);  // RX = A0, TX = A1

// Initialize motors
AF_DCMotor motor1(1, MOTOR12_1KHZ);  // M1 - Left Front
AF_DCMotor motor2(2, MOTOR12_1KHZ);  // M2 - Left Back
AF_DCMotor motor3(3, MOTOR34_1KHZ);  // M3 - Right Back
AF_DCMotor motor4(4, MOTOR34_1KHZ);  // M4 - Right Front

char command;
int speed = 180;
int speed_reducing_factor = 2;  // 🔥 CHANGED: 3 → 2 (less speed reduction)

void setup() {
  bluetoothSerial.begin(9600);
  Stop();
}

void loop() {
  if (bluetoothSerial.available() > 0) {
    command = bluetoothSerial.read();
    
    // Basic movements
    if (command == 'F') Forward();
    else if (command == 'B') Backward();
    else if (command == 'R') TurnRight();
    else if (command == 'L') TurnLeft();
    
    // Mecanum diagonal movements
    else if (command == 'G') ForwardLeft();
    else if (command == 'H') BackwardLeft();
    else if (command == 'I') ForwardRight();
    else if (command == 'J') BackwardRight();
    
    // Mecanum strafe (sideways) movements
    else if (command == 'Q') StrafeLeft();
    else if (command == 'E') StrafeRight();
    
    else if (command == 'S') Stop();
    
    // Speed control
    else if (command == '0') speed = 100;
    else if (command == '1') speed = 130;
    else if (command == '2') speed = 160;
    else if (command == '3') speed = 180;
    else if (command == '4') speed = 200;
    else if (command == '5') speed = 220;
    else if (command == '6') speed = 240;
    else if (command == '7') speed = 255;
    
    // Speed increase/decrease
    else if (command == '+') {
      speed = min(255, speed + 20);
    }
    else if (command == '-') {
      speed = max(0, speed - 20);
    }
  }
}

// ===== BASIC MOVEMENTS =====

void Forward() {
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void Backward() {
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void TurnLeft() {
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
  motor1.run(BACKWARD);  // Left wheels backward
  motor2.run(BACKWARD);  // Left wheels backward
  motor3.run(FORWARD);   // Right wheels forward
  motor4.run(FORWARD);   // Right wheels forward
}

void TurnRight() {
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
  motor1.run(FORWARD);   // Left wheels forward
  motor2.run(FORWARD);   // Left wheels forward
  motor3.run(BACKWARD);  // Right wheels backward
  motor4.run(BACKWARD);  // Right wheels backward
}

void Stop() {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

// ===== MECANUM DIAGONAL MOVEMENTS - IMPROVED =====

void ForwardLeft() {
  // Move diagonal forward-left
  // Right wheels full speed, Left wheels half speed
  motor1.setSpeed(speed / speed_reducing_factor);  // Left Front - slow
  motor2.setSpeed(speed / speed_reducing_factor);  // Left Back - slow
  motor3.setSpeed(speed);                          // Right Back - full
  motor4.setSpeed(speed);                          // Right Front - full
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void ForwardRight() {
  // Move diagonal forward-right
  // Left wheels full speed, Right wheels half speed
  motor1.setSpeed(speed);                          // Left Front - full
  motor2.setSpeed(speed);                          // Left Back - full
  motor3.setSpeed(speed / speed_reducing_factor);  // Right Back - slow
  motor4.setSpeed(speed / speed_reducing_factor);  // Right Front - slow
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void BackwardLeft() {
  // Move diagonal backward-left
  // Right wheels full speed, Left wheels half speed
  motor1.setSpeed(speed / speed_reducing_factor);  // Left Front - slow
  motor2.setSpeed(speed / speed_reducing_factor);  // Left Back - slow
  motor3.setSpeed(speed);                          // Right Back - full
  motor4.setSpeed(speed);                          // Right Front - full
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void BackwardRight() {
  // Move diagonal backward-right
  // Left wheels full speed, Right wheels half speed
  motor1.setSpeed(speed);                          // Left Front - full
  motor2.setSpeed(speed);                          // Left Back - full
  motor3.setSpeed(speed / speed_reducing_factor);  // Right Back - slow
  motor4.setSpeed(speed / speed_reducing_factor);  // Right Front - slow
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

// ===== MECANUM SIDEWAYS MOVEMENTS (STRAFE) =====

void StrafeLeft() {
  // Move sideways left
  // M1(LF): backward, M2(LB): forward, M3(RB): backward, M4(RF): forward
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
  motor1.run(BACKWARD);  // Left Front backward
  motor2.run(FORWARD);   // Left Back forward
  motor3.run(BACKWARD);  // Right Back backward
  motor4.run(FORWARD);   // Right Front forward
}

void StrafeRight() {
  // Move sideways right
  // M1(LF): forward, M2(LB): backward, M3(RB): forward, M4(RF): backward
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
  motor1.run(FORWARD);   // Left Front forward
  motor2.run(BACKWARD);  // Left Back backward
  motor3.run(FORWARD);   // Right Back forward
  motor4.run(BACKWARD);  // Right Front backward
}
