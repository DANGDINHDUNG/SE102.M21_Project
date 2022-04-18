#include "Jellyfish.h"
CJELLY::CJELLY()
{
	SetState(JELLY_STATE_WALKING);
}

void CJELLY::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + JELLY_BBOX_WIDTH;

	if (state == JELLY_STATE_DIE)
		bottom = y + JELLY_BBOX_HEIGHT_DIE;
	else
		bottom = y + JELLY_BBOX_HEIGHT;
}

void CJELLY::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure KILLER can interact with the world and to each of them too!
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

void CJELLY::Render()
{
	int ani = JELLY_ANI_WALKING;
	/*if (state == KILLER_STATE_DIE) {
		ani = KILLER_ANI_DIE;
	}*/

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CJELLY::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case JELLY_STATE_DIE:
		y += JELLY_BBOX_HEIGHT - JELLY_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case JELLY_STATE_WALKING:
		vx = -JELLY_WALKING_SPEED;
	}
}
