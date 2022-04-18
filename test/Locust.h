#pragma once
#include "GameObject.h"

#define LOCUST_WALKING_SPEED 0.05f;

#define LOCUST_BBOX_WIDTH 51
#define LOCUST_BBOX_HEIGHT 45
#define LOCUST_BBOX_HEIGHT_DIE 52

#define LOCUST_STATE_WALKING 100
#define LOCUST_STATE_DIE 200

#define LOCUST_ANI_WALKING 0
#define LOCUST_ANI_DIE 1

class CLOCUST : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CLOCUST();
	virtual void SetState(int state);
};