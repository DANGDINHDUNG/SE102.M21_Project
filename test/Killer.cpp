#include "Killer.h"
CKiller::CKiller()
{
	SetState(KILLER_STATE_WALKING);
}

void CKiller::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KILLER_BBOX_WIDTH;

	if (state == KILLER_STATE_DIE)
		bottom = y + KILLER_BBOX_HEIGHT_DIE;
	else
		bottom = y + KILLER_BBOX_HEIGHT;
}

void CKiller::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void CKiller::Render()
{
	int ani = KILLER_ANI_WALKING;
	/*if (state == KILLER_STATE_DIE) {
		ani = KILLER_ANI_DIE;
	}*/

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CKiller::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KILLER_STATE_DIE:
		y += KILLER_BBOX_HEIGHT - KILLER_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case KILLER_STATE_WALKING:
		vx = -KILLER_WALKING_SPEED;
	}
}
