#include "cub3d.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

double	puissance2(double val)
{
	return (val * val);
}

double	calc_dist(double x1, double y1, double x2, double y2)
{
	return (sqrt(puissance2(x2 - x1) + puissance2(y2 - y1)));
}
