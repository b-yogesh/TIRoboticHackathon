#ifndef MOVEROBOT_H
#define MOVEROBOT_H

#define FORWARD 0
#define BACKWARD 180
#define RIGHT 90
#define LEFT 270

void InitMotor();
void MoveRobot(int degree, long int cycles);
void MoveForward(long int cycles);
void MoveBackward(long int cycles);
void MoveRight(long int cycles);
void MoveLeft(long int cycles);


#endif