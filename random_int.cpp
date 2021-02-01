// random_float.cpp
// random_intt.cpp
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/// <summary>
/// get a random integer number between "min" and "max"
/// </summary>
/// <param name="min"></param>
/// <param name="max"></param>
/// <returns></returns>
int int_rand(int min, int max) {
	int range = max - min + 1;
	return rand() % range + min;
}