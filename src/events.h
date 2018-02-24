#pragma once

#include "eventmanager.h"

class CEvent {
public:
	CEvent(IEventManager::TEvent type) : m_type(type) {}

	IEventManager::TEvent GetType() const { return m_type; }

private:
	IEventManager::TEvent m_type;
};

class CEventMouse : public CEvent {
public:
	int GetX() const { return m_x; }
	int GetY() const { return m_y; }

private:
	int m_x;
	int m_y;
};