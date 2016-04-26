#include <servo_commands.h>

/**
 *  *  *  * Calculate the number of ticks the signal should be high for the required amount of time
 *   *   *   */
int calcTicks(float impulseMs, int hertz)
{
            float cycleMs = 1000.0f / hertz;
                        return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}

float map(float input, float min, float max)
{
            return (input * max) + (1 - input) * min;
}

float range_increment(float min, float max, float millis)
{
            return (max - min) / millis;
}

int angleMicroSec(int tick)
{
            return tick;
}

