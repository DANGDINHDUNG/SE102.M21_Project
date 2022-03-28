#pragma once
#include "GameObject.h"
class Map
{
#define Map_BBOX_WIDTH  16
#define Map_BBOX_HEIGHT 16

	class CBrick : public CGameObject
	{
	public:
		virtual void Render();
		virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	};
};

