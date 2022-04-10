#include "Grid.h"
bool Grid::isContained(LPGAMEOBJECT object)
{
	float cx, cy;
	object->GetPosition(cx, cy);
	if (cx == -250||cx==-350) return true;
	if (cx <= x )
	{
		return false;
	}
	else return true;
}

void Grid::addObject(LPGAMEOBJECT object)
{
	if (isContained(object) == true)
		objectlist.push_back(object);
}

void Grid::removeObeject()
{
	for (int i = 0;i < objectlist.size();i++)
		if(isContained(objectlist[i])==false)
			delete objectlist[i];
}

void Grid::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects )
{
	for (int i = 0;i < objectlist.size();i++)
	{
		if (isContained(objectlist[i]) == false)
			delete objectlist[i];
		else objectlist[i]->Update(dt, coObjects);
	}
}

void Grid::Render()
{
	for (int i = 0;i < objectlist.size();i++)
	{
		if (isContained(objectlist[i]) == false)
			delete objectlist[i];
		else objectlist[i]->Render();
	}
}

void Grid::Unload()
{
	for (int i = 0;i < objectlist.size();i++)
	{
		delete objectlist[i];
	}
	objectlist.clear();
}
