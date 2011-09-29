#include <stdio.h>
#include <math.h>
#include <android/log.h>

#include "common.h"
#include "Matrix.h"

double Matrix::PI = 3.14159265;

int Matrix::rotate2D( int* p_x, int* p_y, int degree ) {
	if( ( p_x == NULL ) || ( p_y == NULL ) ) {
		return R_PARAMETER;
	}

	double x = *p_x;
	double y = *p_y;

	double radian;

	radian = (PI / 180.0) * double(degree);

	x = x * cos(radian) - y * sin(radian);
	y = x * sin(radian) + y * cos(radian);

	*p_x = (int)x;
	*p_y = (int)y;

	return R_NORMAL;
}
