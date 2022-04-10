#include "BigCrab.h"

CBCRAB::CBCRAB()
{
	SetState(BCRAB_STATE_WALKING);
}

void CBCRAB::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BCRAB_BBOX_WIDTH;

	if (state == BCRAB_STATE_DIE)
		bottom = y + BCRAB_BBOX_HEIGHT_DIE;
	else
		bottom = y + BCRAB_BBOX_HEIGHT;
}

void CBCRAB::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure BCRAB can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	/*if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}*/

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
}

void CBCRAB::Render()
{
	int ani = BCRAB_ANI_WALKING_LEFT;
	if (state == BCRAB_STATE_DIE) {
		ani = BCRAB_ANI_DIE;
	}
	else if (vx > 0) ani = BCRAB_ANI_WALKING_RIGHT;
	else if (vx <= 0) ani = BCRAB_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CBCRAB::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BCRAB_STATE_DIE:
		y += BCRAB_BBOX_HEIGHT - BCRAB_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case BCRAB_STATE_WALKING:
		vx = BCRAB_WALKING_SPEED;
	}

}