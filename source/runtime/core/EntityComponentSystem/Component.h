#ifndef __COMPONENT_H__
#define __COMPONENT_H__

/**
* @brief identifies a class as a unique component class
* @param COMPONENT_CLASS - the class name of the component class

* TODO: implement
*/
#define SE_DECLARE_COMPONENT(COMPONENT_CLASS)			\
private:												\
	static const unsigned int COMPONENT_TYPE_ID;		\
	static const char* COMPONENT_TYPE_NAME;				\
														\
public:													\
	static unsigned int getComponentTypeId() {			\
		return COMPONENT_CLASS::COMPONENT_TYPE_ID;		\
	}													\
	static const char* getComponentTypeName() {			\
		return COMPONENT_CLASS::COMPONENT_TYPE_NAME;	\
	}													\
private:

namespace SE
{
	namespace core
	{
		namespace ecs
		{
			class Component
			{
				friend class Entity;

			public:
				Component()
				{
					// atomic
					mUuidCounter++;
					mUuid = mUuidCounter;
				}

				virtual ~Component()
				{
					mUuid = 0;
				}

			public:
				Entity*					getContainer() const
				{
					return mContainer;
				}

				unsigned int			getUuid() const
				{
					return mUuid;
				}

			private:
				static unsigned int		mUuidCounter;
				unsigned int			mUuid;

				Entity*					mContainer;
			};

		}
	}
}

#endif // !__COMPONENT_H__