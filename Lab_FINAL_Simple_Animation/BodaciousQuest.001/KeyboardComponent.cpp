#include "KeyboardComponent.h"

const int MAX_BOOLS = 256;

bool KeyboardComponent::Initialize()
{
	m_keyboard.Initialize();

	

	return true;
}

bool KeyboardComponent::Update(float dt)
{
	m_keyboard.Update(dt);


	return true;
}

bool KeyboardComponent::AddKey(int vKey)
{
	return m_keyboard.AddKey(vKey);
}

bool KeyboardComponent::IsKeyDown(int vKey)
{
	return m_keyboard.KeyIsDown(vKey);
}

bool KeyboardComponent::KeyWasPressed(int vKey)
{
	return m_keyboard.KeyWasPressed(vKey);
}

bool KeyboardComponent::KeyWasReleased(int vKey)
{
	return m_keyboard.KeyWasReleased(vKey);
}

bool KeyboardComponent::AddToggle(int vKey, bool * toggle, bool trigger)
{
	return m_keyboard.AddToggle(vKey,toggle,trigger);
}
