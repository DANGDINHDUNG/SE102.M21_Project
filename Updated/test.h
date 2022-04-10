#pragma once
#include "GameObject.h"
class CCamera:public CGameObject
{
	float x=0;
	float y=0;
	int height=320;
	int width=240;
public:
	CCamera()
	{
		
	}
	void Set(float cx, float cy)
	{
		x = cx;
		y = cy;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x;
		top = y;
		right = x + width;
		bottom = y + height;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		CGameObject::Update(dt, coObjects);
		x +=dx;
		y -= height / 2;
	}
	void Render()
	{
		RenderBoundingBox();
	}
	
};