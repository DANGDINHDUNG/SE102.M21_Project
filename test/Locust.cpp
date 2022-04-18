#include "Locust.h"
CLOCUST::CLOCUST()
{
	SetState(LOCUST_STATE_WALKING);
}

void CLOCUST::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + LOCUST_BBOX_WIDTH;

	if (state == LOCUST_STATE_DIE)
		bottom = y + LOCUST_BBOX_HEIGHT_DIE;
	else
		bottom = y + LOCUST_BBOX_HEIGHT;
}

void CLOCUST::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure GRAB can interact with the world and to each of them too!
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

void CLOCUST::Render()
{
	int ani = LOCUST_ANI_WALKING;
	if (state == LOCUST_STATE_DIE) {
		ani = LOCUST_ANI_DIE;
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CLOCUST::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LOCUST_STATE_DIE:
		y += LOCUST_BBOX_HEIGHT - LOCUST_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case LOCUST_STATE_WALKING:
		vx = -LOCUST_WALKING_SPEED;
	}
}
