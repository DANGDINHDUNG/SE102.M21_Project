#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.5f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_SHOOT			400
#define MARIO_STATE_KNEEL			500
#define MARIO_STATE_KNEEL_OFF		600
#define MARIO_STATE_DIE				700

#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1

#define MARIO_ANI_BIG_WALKING_RIGHT			2
#define MARIO_ANI_BIG_WALKING_LEFT			3

#define MARIO_ANI_JUMP_LEFT 4
#define MARIO_ANI_JUMP_RIGHT 5

#define MARIO_ANI_SHOOT_LEFT 6
#define MARIO_ANI_SHOOT_RIGHT 7

#define MARIO_ANI_KNEEL_LEFT 8
#define MARIO_ANI_KNEEL_RIGHT 9

#define MARIO_ANI_DIE	10

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2

#define MARIO_BIG_BBOX_WIDTH  30
#define MARIO_BIG_BBOX_HEIGHT 40
#define MARIO_BIG_SHOOT_WIDTH  50
#define MARIO_BIG_KNEEL_HEIGHT  23


#define MARIO_UNTOUCHABLE_TIME 5000


class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y; 
public: 
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};