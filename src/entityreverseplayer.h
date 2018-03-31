#pragma once

#include "entity.h"
#include "eventmanager.h"
#include "windowmanager.h"

class EntityReversePlayer: public CEntity, public IEventManager::IListener {
public:
	EntityReversePlayer(int priority = 0, float posX = 0.f, float posY = 0.f);
	bool Init();

	virtual bool ProcessEvent(const CEvent &event);

	void Update(float deltaTime);
	void Render();

	int  GetPriority() const;
	void SetPriority(int priority);

private:
	const float SPEED  = 50.f;
	const float WIDTH  = 100.f;
	const float HEIGHT = 100.f;

	int mPriority;
	float mPosX;
	float mPosY;
	float mMovementX;
	float mMovementY;
	float mMouseX;
	float mMouseY;
	bool  mUnregisterKeyPressed;

	IWindowManager * m_pWindowManager;
};