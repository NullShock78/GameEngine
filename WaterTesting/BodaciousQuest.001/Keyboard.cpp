#include "Keyboard.h"
#include "MyWindow.h"	
#include "GameLogger.h"



void Keyboard::Update(float /*dt*/)
{
	/*for (int j = 0; j < m_currentSize; j++)
	{
		m_toggles[j].CheckToggle();
	}*/
	for (int j = 0; j < m_numKeys; ++j)
	{
		int vKey = m_keys[j];
		Key * key = &m_previousKeyboardState[vKey];
		key->justPressed = false;
	}
	HandleKeys(); //FIRST
	HandleToggles(); //SECOND

	
}

//void Keyboard::AddToggle(int vKey, bool * toggleRef)
//{
//	if (numToggles < KEY_ARRAY_SIZE) {
//		m_toggles[numToggles] = { toggleRef, vKey, false };
//		++numToggles;
//		GameLogger::Log(LogMsgType::cInfo, "Added toggle for key [%c]", vKey);
//	}
//	else
//	{
//		GameLogger::Log(LogMsgType::cError, "Toggle for key [%c] NOT added, array size exceeded. Why do you need more than [%d] toggles?!", vKey, KEY_ARRAY_SIZE);
//	}
//}

bool Keyboard::AddToggle(int vKey, bool * toggleRef, bool fireOnPress)
{
	if (m_numToggles >= MAX_TOGGLES)
	{
		GameLogger::Log(LogMsgType::cFatalError, " Keyboard::AddToggle() is full at %d", MAX_TOGGLES);
		return false;
	}
	

	if (!AddKey(vKey))
	{
		GameLogger::Log(LogMsgType::cFatalError, "Keyboard::AddToggle(): Could not add key [%d].", vKey);
		return false;
	}
	m_toggles[m_numToggles++] = { vKey , toggleRef, fireOnPress };
	
	return true;
	//m_previousKeyboardState[vKey] = { vKey, KeyIsDown(vKey), false, false };
}

void Keyboard::Initialize(ConfigReader * confReader)
{
	m_confReader = confReader;
	for (int j = 0; j < MAX_KEYS; ++j)
	{
		m_keys[j] = j;
	
	}
	GameLogger::Log(LogMsgType::cProcess, "Keyboard::Initialize() successful");
}

//
//void Keyboard::AddToggle(int vKey, bool * toggleRef)
//{
//	m_toggles[m_currentSize] = Toggle(vKey);
//	++m_currentSize;
//}

bool Keyboard::KeyIsDown(int vKey)
{
	return (0 != GetAsyncKeyState(vKey));
}

bool Keyboard::KeyWasPressed(int vKey)
{

	return m_previousKeyboardState[vKey].justPressed;


	/*if (m_keyStatus[vKey] = false)
	{
		if (KeyIsDown(vKey)) {
			m_keyStatus[vKey] = true;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (!KeyIsDown(vKey)) {
			m_keyStatus[vKey] = false;
		}

		return false;
		
	}

*/

}

bool Keyboard::KeyWasReleased(int vKey)
{
	return m_previousKeyboardState[vKey].justReleased;
	//if (m_keyStatus[vKey])
	//{
	//	if (!KeyIsDown(vKey))
	//	{
	//		GameLogger::Log(LogMsgType::ConsoleOnly, "Hit [%c]", vKey);
	//		m_keyStatus[vKey] = false;
	//		return true;
	//	}
	//}
	//if (KeyIsDown(vKey))
	//{
	//	m_keyStatus[vKey] = true;
	//}
	//else
	//{
	//	m_keyStatus[vKey] = false;
	//}

}

void Keyboard::HandleKeys()
{
	for (int j = 0; j < m_numKeys; ++j)
	{
		int vKey = m_keys[j];
		Key * key = &m_previousKeyboardState[vKey];
		bool isDown = KeyIsDown(vKey);
		bool wasDown = m_previousKeyboardState[vKey].wasDownLastTime;

		if (isDown)  key->justPressed = !wasDown; 
		else  key->justReleased = wasDown; 
		m_previousKeyboardState[vKey].wasDownLastTime = isDown;


	}

}

void Keyboard::HandleToggles()
{
	for (int j = 0; j < m_numToggles; ++j)
	{
		KeyToggle * t = &m_toggles[j];
		int vKey = t->vKey;
		Key*	k = &m_previousKeyboardState[vKey];

		if (k->justPressed && t->toggleOnPress) { t->Toggle(); }
		else if (k->justReleased && !t->toggleOnPress) { t->Toggle();}
	}
}

bool Keyboard::AddKey(int vKey)
{
	//add for loop to check keys


	if (m_numKeys >= MAX_KEYS)
	{
		GameLogger::Log(LogMsgType::cFatalError, " Keyboard::AddKey() is full at %d", MAX_KEYS);
		return false;
	}
	m_keys[m_numKeys++]				= vKey;
	m_previousKeyboardState[vKey]	= { vKey, KeyIsDown(vKey), false, false };
	return true;
}

bool Keyboard::AddKeys(const char * keys)
{
	for (const char * j = keys; *j; ++j)
	{
		if (!AddKey(*j))return false;

	}
	return true;
}


//void Keyboard::CheckToggles()
//{
//
//	for (int j = 0; j < numToggles; ++j)
//	{
//
//	if (KeyWasReleased(m_toggles[j].vKey))
//	{
//		if (!m_toggles[j].isPressed)
//		{
//			if (*m_toggles[j].m_out) {
//				*m_toggles[j].m_out = false;
//			}
//			else
//			{
//				*m_toggles[j].m_out = true;
//			}
//		}
//
//		m_toggles[j].isPressed = true;
//	}
//	else {
//		m_toggles[j].isPressed = false;
//	}
//
//	}
//}
