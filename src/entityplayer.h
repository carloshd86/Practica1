#pragma once

#include "entity.h"
#include "eventmanager.h"

class EntityPlayer: public CEntity, public IEventManager::IListener {
public:
	EntityPlayer(int priority = 0);
	int Init();

	virtual bool ProcessEvent(const CEvent &event);

	int  GetPriority() const;
	void SetPriority(int priority);

private:
	int mPriority;
};