#ifndef  COMPONENT_H
#define COMPONENT_H

//Kyle St.Amant
//8/15/2016
//description here

#include "Entity.h"
#include "GameLogger.h"
#include <assert.h>


class Component
{

	enum {

		MAX_NAME_LEN = 32

	};

public:
	Component();
	~Component();
	bool Init();
	virtual bool Initialize(); //MAKE YOUR OWN

	void SetName(const char * name);
	const char * GetName() const { return m_name; }
	void SetOwner(Entity * owner);

	bool IsEnabled();
	bool IsDisabled();


	void Enable(bool enabled = true);
	//virtual means polymorphism
	virtual bool Update(float /*dt*/) { return true; }
	
	template <class T> T* GetSiblingComponent()
	{
		if (!m_owner) {
			GameLogger::Log(LogMsgType::cProgrammerError, "GetSiblingComponent(): Component [%s]: m_owner is nullptr!", m_name);
			return nullptr; 
		}

		T * retVal = m_owner->GetComponentByType<T>();
		if (retVal == nullptr) {
			GameLogger::Log(LogMsgType::cFatalError, "GetSiblingComponent(): Entity[%s]: Component [%s]: Could not find requested sibling component!", m_owner->GetName(),m_name);
		}

		return retVal;
	}

	template <class T> T* GetSiblingComponentByName(const char * name)
	{
		if (!m_owner) {
			GameLogger::Log(LogMsgType::cProgrammerError, "GetSiblingComponent(): Component [%s]: m_owner is nullptr!", m_name);
			return nullptr;
		}

		T * retVal = m_owner->GetComponentByName<T>(name);
		if (retVal == nullptr) {
			GameLogger::Log(LogMsgType::cFatalError, "GetSiblingComponent(): Entity[%s]: Component [%s]: Could not find requested sibling component!", m_owner->GetName(), m_name);
		}

		return retVal;
	}
	

protected:
	Entity * m_owner{ nullptr };
	char	 m_name[MAX_NAME_LEN]{ 0 };
	bool     m_enabled{ true };


};

#endif //def COMPONENT_H