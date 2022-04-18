#pragma once
#include "GameObject.h"

#define JELLY_WALKING_SPEED 0.05f;

#define JELLY_BBOX_WIDTH 51
#define JELLY_BBOX_HEIGHT 45
#define JELLY_BBOX_HEIGHT_DIE 52

#define JELLY_STATE_WALKING 100
#define JELLY_STATE_DIE 200

#define JELLY_ANI_WALKING 0
//#define JELLY_ANI_DIE 1

class CJELLY : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CJELLY();
	virtual void SetState(int state);
};