#pragma once
#include "GameObject.h"

#define KILLER_WALKING_SPEED 0.05f;

#define KILLER_BBOX_WIDTH 36
#define KILLER_BBOX_HEIGHT 25
#define KILLER_BBOX_HEIGHT_DIE 52

#define KILLER_STATE_WALKING 100
#define KILLER_STATE_DIE 600

#define KILLER_ANI_WALKING 0
//#define KILLER_ANI_DIE 1

class CKiller : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	CKiller();
	virtual void SetState(int state);
};