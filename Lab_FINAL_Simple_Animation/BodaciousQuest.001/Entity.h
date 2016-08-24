
#ifndef  ENTITY_H
#define ENTITY_H

//Kyle St.Amant
//8/15/2016
//description here

#include <ostream>
#include <typeinfo>

class Component;
class Entity
{
protected:
	enum {
		MAX_COMPONENTS = 15,
		MAX_NAME_LEN = 32,
		MAX_CHILDREN = 10

	};


public:
	Entity();
	~Entity();

	void SetName(const char * name);
	const char * GetName() const { return m_name; }

	std::ostream& Output(std::ostream& os);

	bool AddComponent(Component * component, const char * name, bool init = false);
	bool InitializeComponents();


	template <class T> T* GetComponentByType()
	{
		for (int j = 0; j < MAX_COMPONENTS; ++j)
		{
			if (!m_components[j]) continue;
			if (m_components[j]->IsDisabled()) continue;
			if (typeid(T) == typeid(*m_components[j]))
			{
				return static_cast<T*>(m_components[j]);
			}
		}

		return nullptr;
	}

	template <class T> T* GetComponentByName(const char * name)
	{
		for (int j = 0; j < MAX_COMPONENTS; ++j)
		{
			if (!m_components[j]) continue;
			if (m_components[j]->IsDisabled()) continue;
			if (strcmp(m_components[j]->GetName(), name) != 0) continue;
			if (typeid(T) == typeid(*m_components[j]))
			{
				return static_cast<T*>(m_components[j]);
			}
		}

		return nullptr;
	}

	bool Update(float dt);

protected:
	Component * m_components[MAX_COMPONENTS]{ nullptr };
	char		m_name[MAX_NAME_LEN]{ 0 };

	Entity * m_children[MAX_CHILDREN];

};

std::ostream& operator<<(std::ostream& os, Entity& entity);

//template <class T> T* GetComponentByType();
//{
//	for (int j = 0; j < MAX_COMPONENTS; ++j)
//	{
//		if (!m_components[j]) continue;
//		if (m_components[j]->IsDisabled()) continue;
//		if (typeid(T) == typeid(*m_components[j]))
//		{
//			return static_cast<T*>(m_components[j]);
//		}
//	}
//
//	return nullptr;
//};

#endif //def ENTITY_H