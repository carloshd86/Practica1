#pragma once

#include "eventmanager.h"

class CEvent {
public:
	CEvent(IEventManager::TEvent type) : mType(type) {}

	IEventManager::TEvent GetType() const { return mType; }

private:
	IEventManager::TEvent mType;
};

class CEventMouse : public CEvent {
public:
	int GetPosX() const { return mPosX; }
	int GetPosY() const { return mPosY; }

private:
	int mPosX;
	int mPosY;
};