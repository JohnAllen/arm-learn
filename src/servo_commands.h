#ifndef SERVO_COMMANDS_H
# define SERVO_COMMANDS_H

int calcTicks(float impulseMs, int hertz);
float map(float input, float min, float max);
float range_increment(float min, float max, float millis);
int angleMicroSec(int tick);

#endif

