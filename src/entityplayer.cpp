#include "entityplayer.h"
#include "inputmanager.h"
#include "asserts.h"
#include "events.h"

// Constructors

EntityPlayer::EntityPlayer(int priority) : m_priority(priority) {}


// Public

int EntityPlayer::Init() { 
	InputManager * pInputManager = InputManager::Instance();
	ASSERT(pInputManager);
	pInputManager ->Register(this, IEventManager::TEvent::ELeftClick , m_priority); 
	pInputManager ->Register(this, IEventManager::TEvent::EKeyPressed, m_priority); 
}

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

int  EntityPlayer::GetPriority() const       { return m_priority; }
void EntityPlayer::SetPriority(int priority) { m_priority = priority; }