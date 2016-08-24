#ifndef  KEYBOARD_H
#define KEYBOARD_H

//Kyle St.Amant
//7/11/2016
//description here

#include <iostream>

struct Key
{
	int vKey;
	bool wasDownLastTime;
	bool justPressed;
	bool justReleased;
};

struct KeyToggle
{
	int  vKey;
	bool * pToggle;
	bool toggleOnPress;
	 
	void Toggle() { 
		printf("Toggled: [%d]\n", char(vKey));
		*(pToggle) = !*(pToggle); 
	}
};

class Keyboard
{
public:
	Keyboard() {}
	void Initialize();
	void Update(float dt);
	bool AddKey(int vKey);
	bool AddKeys(const char * keys);
	//fireonpress = true = when pressed, bool changes
	bool AddToggle(int vKey, bool * toggleRef, bool fireOnPress = true);
	bool KeyIsDown(int vKey);
	bool KeyWasPressed(int vKey);
	bool KeyWasReleased(int vKey);
	
	bool HasKey(int vKey);

private:

	void HandleKeys();
	void HandleToggles();


private:


	
	static const int MAX_KEYS = 30;
	static const int MAX_TOGGLES = 10;

	Key			m_previousKeyboardState[256];
	int			m_keys[MAX_KEYS]{ 0 };
	KeyToggle	m_toggles[MAX_TOGGLES]{ 0 };

	int m_numKeys{ 0 };
	int m_numToggles{ 0 };
};

#endif //def KEYBOARD_H


