#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Crab.h"
#include "Portal.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_BIG;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);

	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y; 
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += MARIO_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		if (x >= 53.6 * 30)
		{
			x = 53.6 * 30;
		}
		else if (x <= -8 * 30)
		{
			x = -8 * 30;
		}
		else
		{
			x += dx;
		}
		if (y < -3)
		{
			y = -3;
		}
		else
		{
			y += dy;
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0; 
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		if (rdx != 0 && rdx!=dx)
			x += nx*abs(rdx); 
		
		// block every object first!

		x += min_tx*dx + nx*0.4f;
		y += min_ty*dy + ny*0.4f;

		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CCRAB *>(e->obj)) // if e->obj is CRAB 
			{
				CCRAB *CRAB = dynamic_cast<CCRAB *>(e->obj);

				// jump on top >> kill CRAB and deflect a bit 
				if (e->ny < 0)
				{
					if (CRAB->GetState()!= CRAB_STATE_DIE)
					{
						CRAB->SetState(CRAB_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable==0)
					{
						float cx, cy;
						CRAB->GetPosition(cx, cy);
							if (state == MARIO_STATE_SHOOT&& CRAB->GetState() != CRAB_STATE_DIE)
							{
								if((nx>0 && cx < x)|| (nx<0 && cx > x))
									CRAB->SetState(CRAB_STATE_DIE);
							}
						/*if (CRAB->GetState() != CRAB_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else 
								SetState(MARIO_STATE_DIE);
						}*/
					}
				}
			} // if CRAB
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::Render()
{
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else if (state == MARIO_STATE_SHOOT)
		{
			if (nx > 0) ani = MARIO_ANI_SHOOT_RIGHT;
			else ani = MARIO_ANI_SHOOT_LEFT;
		}
	else if (state == MARIO_STATE_KNEEL)
	{
		if (nx > 0) ani = MARIO_ANI_KNEEL_RIGHT;
		else ani = MARIO_ANI_KNEEL_LEFT;
	}
	else 
		if (vy < 0)
		{
			if (nx > 0) ani = MARIO_ANI_JUMP_RIGHT;
			else ani = MARIO_ANI_JUMP_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
				else ani = MARIO_ANI_BIG_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = MARIO_ANI_BIG_WALKING_RIGHT;
			else ani = MARIO_ANI_BIG_WALKING_LEFT;
		}
	

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT: 
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		vy = -MARIO_JUMP_SPEED_Y;
		break; 
	case MARIO_STATE_IDLE: 
		vx = 0;
		break;
	case MARIO_STATE_KNEEL:
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
 
	left = x;
	top = y;
	if (state == MARIO_STATE_SHOOT)
	{
		
		right = x + MARIO_BIG_SHOOT_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else if (state == MARIO_STATE_KNEEL_OFF)
	{
		y-=MARIO_BIG_BBOX_HEIGHT;
		state = MARIO_STATE_IDLE;
	}
	else if (state == MARIO_STATE_KNEEL)
	{
		bottom =y+ MARIO_BIG_KNEEL_HEIGHT;
		right = x + MARIO_BIG_BBOX_WIDTH;
	}
	else
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

