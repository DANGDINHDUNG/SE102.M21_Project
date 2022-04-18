#pragma once
#include "GameObject.h"

#define CRAB_WALKING_SPEED 0.05f;

#define CRAB_BBOX_WIDTH 51
#define CRAB_BBOX_HEIGHT 45
#define CRAB_BBOX_HEIGHT_DIE 52

#define CRAB_STATE_WALKING 100
#define CRAB_STATE_DIE 600

#define CRAB_ANI_WALKING 0
#define CRAB_ANI_DIE 1

class CCRAB : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

public: 	
	CCRAB();
	virtual void SetState(int state);
};