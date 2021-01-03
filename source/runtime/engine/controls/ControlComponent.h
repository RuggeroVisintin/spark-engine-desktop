#ifndef __CONTROLCOMPONENT_H__
#define __CONTROLCOMPONENT_H__

#include <functional>
#include <EntityComponentSystem/Component.h>
#include <Input/ControlsEvents.h>

namespace SE
{
	namespace engine
	{
		class ControlComponent : public SE::core::ecs::Component
		{
			friend class								ControlSystem;

			typedef SE::core::ecs::Component			super;
			typedef SE::platform::input::KeyboardEvent	KeyboardEvent;
			typedef std::function<void(KeyboardEvent)>	ControlCallback;

		public:
			ControlComponent()
				: super()
			{
			}

			~ControlComponent()
			{
			}

		public:
			/**
			* @description - the key is pressed up and down
			*/
			//void onKeyPress();

			/**
			* @description - the key is pressed
			*/
			void onKeyDown(ControlCallback callback)
			{
				this->mKeyDownCallback = callback;
			}

			/**
			* @description - the key is released
			*/
			void onKeyUp(ControlCallback callback)
			{
				this->mKeyUpCallback = callback;
			}

		private:
			//void triggerKeyDown();
			//void triggerKeyUp();

		private:
			ControlCallback mKeyDownCallback;
			ControlCallback mKeyUpCallback;
		};
	}
}

#endif // !__CONTROLCOMPONENT_H__