#ifndef  KEYBOARD_COMPONENT_H
#define KEYBOARD_COMPONENT_H

//Kyle St.Amant
//8/15/2016
//description here

#include "Component.h"
#include "Keyboard.h"

class MovementComponent;
class KeyboardComponent : public Component
{
private:
	Keyboard m_keyboard;
	MovementComponent * m_moveComponent{ nullptr };
	
	bool * m_bools[256];
	int m_keys[256]{ -1 };
	int m_numbools{ 0 };

public:
	
	bool Initialize();
	bool Update(float dt);
	bool AddKey(int vKey);
	bool IsKeyDown(int vKey);

	bool KeyWasPressed(int vKey);
	bool KeyWasReleased(int vKey);
	bool AddToggle(int vKey, bool * toggle, bool trigger = true);
	//bool KeyWasPressed(int vKey);

};

#endif //def KEYBOARD_COMPONENT_H



