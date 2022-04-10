#pragma once
#include <iostream>
class Camera
{
	float x;
	float y;
public:
	void Set(float x,float y)
	{
		this->x=x;
		this->y=y;
	}
	void Update(float width, float height)
	{
		if (x > 29.9 * 30.0f)
		{
			x = 29.8 * 30.0f - (width / 2);
			y -= height / 2;
		}
		else if (x < -2.5 * 30.0f)
		{
			x = -2.4 * 30.0f - (width / 2);
			y -= height / 2;
		}
		else
		{
			x -= width / 2;
			y -= height / 2;
		}
	}
	float GetX()
	{
		return x;
	}
	float GetY()
	{
		return y;
	}
};
