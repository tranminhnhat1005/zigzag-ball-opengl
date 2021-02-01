// random_float.cpp
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/// <summary>
/// get a random float number between "min" and "max"
/// </summary>
/// <param name="min"></param>
/// <param name="max"></param>
/// <returns>(float) number</returns>
float float_rand(float min, float max)
{
    float scale = rand() / (float)RAND_MAX; /* [0, 1.0] */
    return min + scale * (max - min);      /* [min, max] */
}