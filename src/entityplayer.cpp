#include "entityplayer.h"
#include "application.h"
#include "asserts.h"
#include "events.h"


EntityPlayer::EntityPlayer(int priority) : mPriority(priority) {}

// *************************************************
//
// *************************************************

bool EntityPlayer::Init() { 
	Application    * pApplication   = Application::Instance();
	ASSERT(pApplication);
	IEventManager  * pInputManager  = pApplication->GetEventManager();
	ASSERT(pInputManager);
	pInputManager ->Register(this, IEventManager::TEvent::ELeftClick , mPriority); 
	pInputManager ->Register(this, IEventManager::TEvent::EKeyPressed, mPriority); 

	return true;
}

// *************************************************
//
// *************************************************

bool EntityPlayer::ProcessEvent(const CEvent &event) {
	switch (event.GetType()) {
	
		case IEventManager::TEvent::ELeftClick:
			//TODO
		break;

		case IEventManager::TEvent::EKeyPressed:
			//TODO
			break;

		default:
			return false;
	}

	return true;
}

// *************************************************
//
// *************************************************

int  EntityPlayer::GetPriority() const       { return mPriority; }

// *************************************************
//
// *************************************************

void EntityPlayer::SetPriority(int priority) { mPriority = priority; }