#include "ControlSystem.h"

#include <Input/ControlsEvents.h>

namespace SE
{
	namespace engine
	{
		void ControlSystem::registerComponent(ControlComponent* component)
		{
			mControls.push_back(component);
		}

		void ControlSystem::update() const
		{
			typedef std::vector<SE::platform::input::KeyboardEvent> EventsList;
			EventsList events = mInputDispatcher->nextKeys();

			for (std::vector<ControlComponent*>::const_iterator component = mControls.begin();
				component != mControls.end(); component++)
			{
				for (EventsList::const_iterator inputEvt = events.begin(); inputEvt != events.end(); inputEvt++)
				{
					if (inputEvt->state == SE::platform::input::KEYBOARD_STATES::KEY_PRESSED && (*component)->mKeyDownCallback != nullptr) {
						(*component)->mKeyDownCallback((*inputEvt));
					}
					else if ((*component)->mKeyUpCallback != nullptr) {
						(*component)->mKeyUpCallback((*inputEvt));
					}
				}
			}
		}
	}
}