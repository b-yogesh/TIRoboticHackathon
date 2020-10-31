#ifndef MOVEROBOT_H
#define MOVEROBOT_H

#define FORWARD 0
#define BACKWARD 180

void InitMotor();
void MoveRobot(int degree, long int duty, long int cycles);
void MoveForward(long int duty, long int cycles);
void MoveBackward(long int duty, long int cycles);
void TurnRight();
void TurnLeft();
void Turn180();
void MotorStop();


#endif