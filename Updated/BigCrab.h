#pragma once

#include "GameObject.h"

#define BCRAB_WALKING_SPEED 0.03f;

#define BCRAB_BBOX_WIDTH 105
#define BCRAB_BBOX_HEIGHT 81
#define BCRAB_BBOX_HEIGHT_DIE 16

#define BCRAB_STATE_WALKING 100
#define BCRAB_STATE_DIE 200

#define BCRAB_ANI_WALKING_LEFT 0
#define BCRAB_ANI_WALKING_RIGHT 1
#define BCRAB_ANI_DIE 2

class CBCRAB : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

public:
	CBCRAB();
	virtual void SetState(int state);
};