#pragma once
#include "GameObject.h"
class Space
{
	float min;
	float max;
	int number;
public:
	Space(float x, float y, int num)
	{
		min = x;
		max = y;
		number = num;
	}
	void Get_min(float x) { x=min; }
	void Get_max(float y) { y=max; }
	void Get_number(int num) {  num=number; }
};
class Grid
{
	float x;
	float y;
	vector<LPGAMEOBJECT> objectlist;
public:
	Grid();
	Grid(float cx, float cy) { x = cx;y = cy; }
	bool isContained(LPGAMEOBJECT object);
	void addObject(LPGAMEOBJECT obeject);
	void removeObeject();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects=NULL);
	void Render();
	void Unload();
};

