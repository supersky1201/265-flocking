#include "pvector.h"
/*
PVector::PVector(float x_, float y_)
{
this->x = x_;
this->y = y_;
}
*/
void PVector::add(PVector v)
{
	x = x + v.x;
	y = y + v.y;
}

void PVector::sub(PVector a, PVector b)
{
	x = a.x - b.x;
	y = a.y - b.y;
}

void PVector::normalize()
{
	float m = mag();
	if (m != 0)
	{
		div(m);
	}
}

void PVector::div(float n)
{
	x = x / n;
	y = y / n;
}

void PVector::mult(float n)
{
	x = x * n;
	y = y * n;
}

void PVector::limit(float max)
{
	float mag = sqrt(x*x + y * y);
	if (mag > max)
	{
		x = x / mag * max;
		y = y / mag * max;
	}
}

float PVector::mag()
{
	return sqrt(x*x + y * y);
}

float PVector::rotation()
{
	if (y <= 0)
	{
		return asin(x / sqrt(x*x + y * y))*180.f / PI;
	}
	else
	{
		if (x == 0)
		{
			return 180.f;
		}
		else if (x > 0)
		{
			return atan(y / x)*180.f / PI + 90.f;
		}
		else if (x < 0)
		{
			return  atan(y / x)*180.f / PI - 90.f;
		}
	}
}

