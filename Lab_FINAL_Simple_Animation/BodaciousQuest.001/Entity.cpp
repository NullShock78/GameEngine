#include "Entity.h"
#include <string.h>
#include "Component.h"
#include <assert.h>
#include "GameLogger.h"
Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::SetName(const char * name)
{
	strncpy_s(m_name, MAX_NAME_LEN, name, _TRUNCATE);
}

std::ostream & Entity::Output(std::ostream& os)
{
	os << "\n\n\n\n\n\n\n\n\n\n\n====== Begin Entity: (" << GetName() << ") ======\n";
	const int buffersize = 100;
	char buffer[buffersize]{ 0 };

	int counter = 0;

	for (int j = 0; j < MAX_COMPONENTS; ++j)
	{
		if (m_components[j])
		{
			sprintf_s(buffer, buffersize, "  %d : Component [%s]\n",
				counter, m_components[j]->GetName());
			os << buffer;
			++counter;
		}
	}

	os << "====== Done  Entity: (" << GetName() << ") ======\n\n\n\n\n\n\n\n\n\n\n\n";
	return os;
}
bool Entity::AddComponent(Component * component, const char * name, bool init)
{

	if (!component) {
		GameLogger::Log(LogMsgType::cFatalError, "Entity::AddComponent(): Entity[%s]: Component [%s] is nullptr");
		return false;
	}

	for (int j = 0; j < MAX_COMPONENTS; j++)
	{
		if (!m_components[j])
		{
			m_components[j] = component;
			component->SetName(name);
			component->SetOwner(this);
			if (init)
			{
				return component->Init();
			}

			return true;
		}
	}
	GameLogger::Log(LogMsgType::cFatalError, "Entity::AddComponent(): Entity[%s]: List is full, could not add Component [%s] ", m_name, name);

	return false;
}
bool Entity::InitializeComponents()
{
	for (int j = 0; j < MAX_COMPONENTS; j++)
	{
		if (!m_components[j]->Initialize()) {
			return false;
		}
	}

	return true;
}
bool Entity::Update(float dt)
{
	for (int j = 0; j < MAX_COMPONENTS; j++)
	{
		if (m_components[j] && m_components[j]->IsEnabled())
		{
			bool result = m_components[j]->Update(dt);
			assert(result);
		}
	}

	return true;
}
std::ostream& operator<<(std::ostream& os, Entity& entity)
{
	return entity.Output(os);
}

