#ifndef __DEBUGCAMERAENTITY_H__
#define __DEBUGCAMERAENTITY_H__

#include <Input/ControlsEvents.h>
#include <GameObjects/CameraEntity.h>
#include <controls/ControlComponent.h>

namespace SE
{
	namespace engine
	{
		class DebugCameraEntity : public CameraEntity
		{
			typedef CameraEntity super;
			typedef SE::platform::input::KeyboardEvent	KeyboardEvent;

		public:
			DebugCameraEntity()
				: super()
			{
				addComponent<ControlComponent>(&this->controls);

				this->controls.onKeyDown(std::bind(&DebugCameraEntity::onKeyDown, this, std::placeholders::_1));
				this->controls.onKeyUp(std::bind(&DebugCameraEntity::onKeyUp, this, std::placeholders::_1));
			}

			~DebugCameraEntity()
			{
			}

		private:
			void onKeyDown(KeyboardEvent evt);
			void onKeyUp(KeyboardEvent evt);

		public:
			ControlComponent controls;
		};
			
	}
}

#endif // !__DEBUGCAMERAENTITY_H__
