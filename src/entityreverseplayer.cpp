#include "entityreverseplayer.h"
#include "application.h"
#include "asserts.h"
#include "events.h"


EntityReversePlayer::EntityReversePlayer(int priority, float posX, float posY) : 
	mPriority             (priority),
	mPosX                 (posX),
	mPosY                 (posY), 
	mMovementX            (0.f),
    mMovementY            (0.f),
    mMouseX               (0.f),
    mMouseY               (0.f),
	mUnregisterKeyPressed (false) {}

// *************************************************
//
// *************************************************

bool EntityReversePlayer::Init() { 
	Application * pApplication   = Application::Instance();
	ASSERT(pApplication);
	m_pWindowManager = pApplication->GetWindowManager();
	ASSERT(m_pWindowManager);
	IEventManager * pInputManager  = pApplication->GetEventManager();
	ASSERT(pInputManager);
	pInputManager->Register(this, IEventManager::TEvent::EMouseMove  , mPriority); 
	pInputManager->Register(this, IEventManager::TEvent::EMouseClick , mPriority); 
	pInputManager->Register(this, IEventManager::TEvent::EKeyPressed , mPriority); 

	return true;
}

// *************************************************
//
// *************************************************

bool EntityReversePlayer::ProcessEvent(const CEvent &event) {
	switch (event.GetType()) {
	
		case IEventManager::TEvent::EMouseMove: {
			const CEventMouseMove * eMouseClick = dynamic_cast<const CEventMouseMove *>(&event);
			mMouseX = eMouseClick->GetPosX();
			mMouseY = eMouseClick->GetPosY();
		}	
		break;

		case IEventManager::TEvent::EMouseClick: {
				const CEventMouseClick * eMouseClick = dynamic_cast<const CEventMouseClick *>(&event);
				if (CEventMouseClick::EMouseButton::Left == eMouseClick->GetMouseButton()) {
					mPosX = mMouseX;
					mPosY = mMouseY;
				}
			}	
			break;

		case IEventManager::TEvent::EKeyPressed: {
				const CEventKeyPressed * eKey = dynamic_cast<const CEventKeyPressed *>(&event);
				int keyPressed = eKey->GetKey();
				if      (265 == keyPressed) mMovementY = SPEED;  // UP
				else if (264 == keyPressed) mMovementY = -SPEED; // DOWN
				else if (263 == keyPressed) mMovementX = SPEED; // LEFT
				else if (262 == keyPressed) mMovementX = -SPEED;  // RIGHT
				else if (81 == keyPressed)  mUnregisterKeyPressed = true; // q
			}
			break;

		default:
			return false;
	}

	return true;
}

// *************************************************
//
// *************************************************

void EntityReversePlayer::Update(float deltaTime) {
	if (mMovementX) {
		mPosX += mMovementX * deltaTime;
		mMovementX = 0;
	}
	if (mMovementY) {
		mPosY += mMovementY * deltaTime;
		mMovementY = 0;
	}

	if (mUnregisterKeyPressed) {
		mUnregisterKeyPressed = false;
		Application * pApplication = Application::Instance();
		ASSERT(pApplication);
		IEventManager * pInputManager = pApplication->GetEventManager();
		ASSERT(pInputManager);
		pInputManager->Unregister(this, IEventManager::TEvent::EKeyPressed);
	}
}

// *************************************************
//
// *************************************************

void EntityReversePlayer::Render() {
	m_pWindowManager->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_pWindowManager->DrawRect(mPosX, mPosY, WIDTH, HEIGHT);
}

// *************************************************
//
// *************************************************

int  EntityReversePlayer::GetPriority() const { return mPriority; }

// *************************************************
//
// *************************************************

void EntityReversePlayer::SetPriority(int priority) { mPriority = priority; }