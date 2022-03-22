#include <algorithm>
#include "debug.h"

#include "character.h"
#include "Game.h"

#include "Solider.h"

void Ccharacter::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += character_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=character_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > character_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		if (x >= 33.6*30)
		{
			x = 33.6 * 30;	
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

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;
		
		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;

		// Collision logic with Soliders
		/*for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CSolider *>(e->obj)) // if e->obj is Solider 
			{
				CSolider *Solider = dynamic_cast<CSolider *>(e->obj);

				// jump on top >> kill Solider and deflect a bit 
				if (e->ny < 0)
				{
					if (Solider->GetState()!= Solider_STATE_DIE)
					{
						Solider->SetState(Solider_STATE_DIE);
						vy = -character_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable==0)
					{
						if (Solider->GetState()!=Solider_STATE_DIE)
						{
							if (level > character_LEVEL_SMALL)
							{
								level = character_LEVEL_SMALL;
								StartUntouchable();
							}
							else 
								SetState(character_STATE_DIE);
						}
					}
				}
			}
		}*/
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Ccharacter::Render()
{
	int ani;
	if (state == character_STATE_DIE)
		ani = character_ANI_DIE;
	else
	if (level == character_LEVEL_BIG)
	{
		if (vy<0)
		{
			if (nx > 0) ani = character_ANI_JUMP_RIGHT;
			else ani = character_ANI_JUMP_LEFT;
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) ani = character_ANI_BIG_IDLE_RIGHT;
				else ani = character_ANI_BIG_IDLE_LEFT;
	
			}
			else if (vx > 0)
				ani = character_ANI_BIG_WALKING_RIGHT;
			else ani = character_ANI_BIG_WALKING_LEFT;
		}
	}
	else if (level == character_LEVEL_SMALL)
	{
		if (vx == 0)
		{
			if (nx>0) ani = character_ANI_SMALL_IDLE_RIGHT;
			else ani = character_ANI_SMALL_IDLE_LEFT;
		}
		else if (vx > 0)
			ani = character_ANI_SMALL_WALKING_RIGHT;
		else ani = character_ANI_SMALL_WALKING_LEFT;
	}

	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[ani]->Render(x, y, alpha);

	RenderBoundingBox();
}

void Ccharacter::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case character_STATE_WALKING_RIGHT:
		vx = character_WALKING_SPEED;
		nx = 1;
		break;
	case character_STATE_WALKING_LEFT: 
		vx = -character_WALKING_SPEED;
		nx = -1;
		break;
	case character_STATE_KNEEL:
		vx = 0;
		break;
	case character_STATE_JUMP: 
		vy = -character_JUMP_SPEED_Y;
	case character_STATE_IDLE: 
		vx = 0;
		break;
	case character_STATE_DIE:
		vy = -character_DIE_DEFLECT_SPEED;
		break;
	}
}

void Ccharacter::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	if (level==character_LEVEL_BIG)
	{
		right = x + character_BIG_BBOX_WIDTH;
		bottom = y + character_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + character_SMALL_BBOX_WIDTH;
		bottom = y + character_SMALL_BBOX_HEIGHT;
	}
}

