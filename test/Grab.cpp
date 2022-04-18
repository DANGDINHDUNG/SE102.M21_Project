#include "CRAB.h"
CCRAB::CCRAB()
{
	SetState(CRAB_STATE_WALKING);
}

void CCRAB::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + CRAB_BBOX_WIDTH;

	if (state == CRAB_STATE_DIE)
		bottom = y + CRAB_BBOX_HEIGHT_DIE;
	else 	
		bottom = y + CRAB_BBOX_HEIGHT;
}

void CCRAB::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure CRAB can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
}

void CCRAB::Render()
{
	int ani = CRAB_ANI_WALKING;
	if (state == CRAB_STATE_DIE) {
		ani = CRAB_ANI_DIE;
	}

	animation_set->at(ani)->Render(x,y);

	//RenderBoundingBox();
}

void CCRAB::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case CRAB_STATE_DIE:
			y += CRAB_BBOX_HEIGHT - CRAB_BBOX_HEIGHT_DIE + 1;
			vx = 0;
			vy = 0;
			break;
		case CRAB_STATE_WALKING: 
			vx = -CRAB_WALKING_SPEED;
	}
}
