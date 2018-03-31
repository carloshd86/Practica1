#include "glfwinputmanager.h"
#include "globals.h"
#include "glfwwindowmanager.h"
#include "asserts.h"
#include <algorithm>
#include "events.h"


GlfwInputManager * GlfwInputManager::mInstance;

// *************************************************
//
// *************************************************

GlfwInputManager::GlfwInputManager() :
	mInitialized (false) {}

// *************************************************
//
// *************************************************

GlfwInputManager::~GlfwInputManager() {
	if (mInitialized)
		End();
}

// *************************************************
//
// *************************************************

GlfwInputManager * GlfwInputManager::Instance() {
	if (!mInstance) {
		mInstance = new GlfwInputManager();
		mInstance->Init();
	}

	return mInstance;
}

// *************************************************
//
// *************************************************

IEventManager::EM_Err GlfwInputManager::Init() {

	if (mInitialized)
		return OK;

	m_pWindowManager = GlfwWindowManager::Instance();

	ASSERT(m_pWindowManager);

	// Setting events
	// Mouse Move
	m_pWindowManager->SetMouseMoveCallback(&GlfwInputManager::MouseMove);

	// Mouse Click
	m_pWindowManager->SetMouseClickCallback(&GlfwInputManager::MouseClick);
	
	// Key Pressed
	m_pWindowManager->SetKeyPressedCallback(&GlfwInputManager::KeyPressed);


	mInitialized = true;
	return OK;
}

// *************************************************
//
// *************************************************

IEventManager::EM_Err GlfwInputManager::End() {

	return OK;
}

// *************************************************
//
// *************************************************

IEventManager::EM_Err GlfwInputManager::Register(IListener * listener, TEvent e, int priority) {

	if (EAll == e)
		return KO;

	mListeners[e][priority].push_back(listener);

	return OK;
}

// *************************************************
//
// *************************************************

IEventManager::EM_Err GlfwInputManager::Unregister(IListener * listener, TEvent e) {

	if (TEvent::EAll == e) {
		for (auto it = mListeners.begin(); it != mListeners.end(); ++it) {
			TEvent event = it->first;
			RemoveListenerMapListenerForEvent(listener, event);
		}
	}
	else {
		RemoveListenerMapListenerForEvent(listener, e);
	}

	return OK;
}

// *************************************************
//
// *************************************************

GlfwInputManager::ListenerMap& GlfwInputManager::GetListenerMap() {
	return mListeners;
}

// *************************************************
//
// *************************************************

void GlfwInputManager::RemoveListenerMapListenerForEvent(IListener * listener, TEvent e) {
	for(auto prioritiesIt = mListeners[e].begin(); prioritiesIt != mListeners[e].end(); ++prioritiesIt) {
		std::vector<IListener *> listeners = prioritiesIt->second;
		auto listenersIt = listeners.begin();
		while (listenersIt != listeners.end()) {
			if (listener == *listenersIt) {
				listenersIt = listeners.erase(listenersIt);
			} else
				++listenersIt;
		}
	}
}

// *************************************************
//
// *************************************************

void GlfwInputManager::MouseMove(GLFWwindow * window, double xpos, double ypos) {
	ListenerMap& listenerMap = mInstance->GetListenerMap();

	if (listenerMap[TEvent::EMouseMove].size()) {
		for (auto prioritiesIt = listenerMap[TEvent::EMouseMove].begin(); prioritiesIt != listenerMap[TEvent::EMouseMove].end(); ++prioritiesIt) {
			std::vector<IListener *> listeners = prioritiesIt->second;
			auto listenersIt = listeners.begin();
			for (auto listenersIt = listeners.begin(); listenersIt !=listeners.end(); ++listenersIt) {
				(*listenersIt)->ProcessEvent(CEventMouseMove(static_cast<float>(xpos), static_cast<float>(ypos)));
			}
		}
	}
}

// *************************************************
//
// *************************************************

void GlfwInputManager::MouseClick(GLFWwindow * window, int button, int action, int mods) {
	ListenerMap& listenerMap = mInstance->GetListenerMap();

	CEventMouseClick::EMouseButton mouseButton = CEventMouseClick::EMouseButton::NotSupported;
	switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:   mouseButton = CEventMouseClick::EMouseButton::Left;   break;
		case GLFW_MOUSE_BUTTON_MIDDLE: mouseButton = CEventMouseClick::EMouseButton::Middle; break;
		case GLFW_MOUSE_BUTTON_RIGHT:  mouseButton = CEventMouseClick::EMouseButton::Right;  break;
	}

	if (listenerMap[TEvent::EMouseClick].size()) {
		for (auto prioritiesIt = listenerMap[TEvent::EMouseClick].begin(); prioritiesIt != listenerMap[TEvent::EMouseClick].end(); ++prioritiesIt) {
			std::vector<IListener *> listeners = prioritiesIt->second;
			auto listenersIt = listeners.begin();
			for (auto listenersIt = listeners.begin(); listenersIt != listeners.end(); ++listenersIt) {
				(*listenersIt)->ProcessEvent(CEventMouseClick(mouseButton));
			}
		}
	}
}

// *************************************************
//
// *************************************************

void GlfwInputManager::KeyPressed(GLFWwindow * window, int key, int scancode, int action, int mods) {
	ListenerMap& listenerMap = mInstance->GetListenerMap();
	
	if (listenerMap[TEvent::EKeyPressed].size()) {
		for (auto prioritiesIt = listenerMap[TEvent::EKeyPressed].begin(); prioritiesIt != listenerMap[TEvent::EKeyPressed].end(); ++prioritiesIt) {
			std::vector<IListener *> listeners = prioritiesIt->second;
			auto listenersIt = listeners.begin();
			for (auto listenersIt = listeners.begin(); listenersIt !=listeners.end(); ++listenersIt) {
				(*listenersIt)->ProcessEvent(CEventKeyPressed(key));
			}
		}
	}
}