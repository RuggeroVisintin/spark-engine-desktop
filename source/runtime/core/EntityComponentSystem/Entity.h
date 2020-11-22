#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <vector>
#include <type_traits>
#include "Component.h"

#include <Assertion/Assert.h>

namespace SE
{
	namespace core
	{
		namespace ecs
		{
			class Entity
			{
				typedef std::vector<Component*> ComponentMap;

			public:
				Entity()
				{
				}

				virtual ~Entity()
				{
				}

			public:
				template <class T>
				T*							getComponent() const;

				template <class T>
				T*							addComponent(T* component);

				template <class T>
				void						removeComponent() { SPARK_ASSERT(false, "Entity::removeComponent not implemented"); }

				template <class T>
				bool						hasComponent() const;

			public:
				ComponentMap				mComponents;
				
			};

			template <class T>
			T* Entity::getComponent() const
			{
				SPARK_ASSERT((std::is_base_of<Component, T>::value), "Entity::getComponent template argument is not derived from Component class");

				for (ComponentMap::const_iterator it = mComponents.begin(); it != mComponents.end(); it++) {

					// TODO: dynamic_cast is qutie slow, think to some kind of RTTI to keep only for component for now
					if (T* component = dynamic_cast<T*>(*it)) {
						return dynamic_cast<T*>(*it);
					}
				}			

				SPARK_ASSERT(false, "Entity::getComponent cannot find given component type");
				return nullptr;
			}

			template <class T>
			T* Entity::addComponent(T* component)
			{
				SPARK_ASSERT((std::is_base_of<Component, T>::value), "Entity::addComponent template argument is not derived from Component class");

				for (ComponentMap::iterator it = mComponents.begin(); it != mComponents.end(); it++) {

					// TODO: dynamic_cast is qutie slow, think to some kind of RTTI to keep only for component for now
					if (T* _component = dynamic_cast<T*>(*it)) {
						return component;
					}
				}
				
				component->mContainer = this;
				mComponents.push_back((Component*)component);

				return component;
			}

			template <class T>
			bool Entity::hasComponent() const
			{
				SPARK_ASSERT((std::is_base_of<Component, T>::value), "Entity::addComponent template argument is not derived from Component class");

				for (ComponentMap::const_iterator it = mComponents.begin(); it != mComponents.end(); it++) {

					// TODO: dynamic_cast is qutie slow, think to some kind of RTTI to keep only for component for now
					if (T* _component = dynamic_cast<T*>(*it)) {
						return true;
					}
				}

				return false;
			}
		}
	}
}

#endif // !__ENTITY_H__