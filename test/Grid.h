#pragma once
#include "GameObject.h"
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

