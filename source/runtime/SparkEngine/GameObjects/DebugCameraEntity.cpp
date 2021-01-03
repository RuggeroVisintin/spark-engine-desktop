#include "DebugCameraEntity.h"

namespace SE
{
	namespace engine
	{
		void DebugCameraEntity::onKeyDown(KeyboardEvent evt)
		{
			typedef SE::platform::input::KEYS KEYS;

			switch (evt.key)
			{
			case KEYS::KEY_W:
			{
				this->transform.transform.translate(this->transform.transform.getForward() * .1f);
				break;
			}
			case KEYS::KEY_S:
			{
				this->transform.transform.translate(this->transform.transform.getForward() * -.1f);
				break;
			}
			case KEYS::KEY_A:
			{
				this->transform.transform.translate(this->transform.transform.getRight() * .1f);
				break;
			}
			case KEYS::KEY_D:
			{
				this->transform.transform.translate(this->transform.transform.getRight() * -.1f);
				break;
			}
			}
		}

		void DebugCameraEntity::onKeyUp(KeyboardEvent evt)
		{

		}
	}
}