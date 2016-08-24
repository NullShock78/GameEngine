#include "Component.h"
#include "GameLogger.h"
#include <string.h>


Component::Component()
{
}


Component::~Component()
{
}

bool Component::Init()
{
	 bool retVal = Initialize();
	 if (!retVal) {
		 GameLogger::Log(LogMsgType::cFatalError, "Component::Init(): Entity[%s]: Component[%s] failed to initialize.", m_owner->GetName(), m_name);
	 }
	 return retVal;
}

bool Component::Initialize()
{
	return true;
}

void Component::SetName(const char * name)
{
	strncpy_s(m_name, MAX_NAME_LEN, name, _TRUNCATE);
}

void Component::SetOwner(Entity * owner)
{
	assert(owner);
	m_owner = owner;
}

bool Component::IsEnabled()
{
	return m_enabled;
}

bool Component::IsDisabled()
{
	return !m_enabled;
}

void Component::Enable(bool enabled)
{
	m_enabled = enabled;
}
