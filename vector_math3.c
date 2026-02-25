#include "miniRT.h"

double ndc_x(int x)
{
	double new_x;

	new_x = ((x + 0.5) / (double)WIDTH);
	new_x =(2 * new_x) - 1;
	return (new_x);
}

double ndc_y(int y)
{
	double new_y;

	new_y = ((y + 0.5) / (double)HEIGHT);
	new_y = 1 - (2 * new_y);
	return (new_y);
}

double fov_factor(int fov)
{
	double radian;
	double factor;

	radian = (fov * 0.5) * (PI / 180.0);
	factor = tan(radian);
	return (factor);
}
