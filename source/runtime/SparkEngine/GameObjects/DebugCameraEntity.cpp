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
			case KEYS::KEY_LEFT:
			{
				SE::core::math::Quat<float> rotation;
				rotation.setRotationAboutY(0.1f);
				this->transform.transform.rotate(rotation);
				break;
			}
			case KEYS::KEY_RIGHT:
			{
				SE::core::math::Quat<float> rotation;
				rotation.setRotationAboutY(-0.1f);
				this->transform.transform.rotate(rotation);
				break;
			}
			// TODO: add up and down
			case KEYS::KEY_UP:
			{
				SE::core::math::Quat<float> rotation;
				rotation.setRotationAboutX(0.1f);
				this->transform.transform.rotate(rotation);
				break;
			}
			case KEYS::KEY_DOWN:
			{
				SE::core::math::Quat<float> rotation;
				rotation.setRotationAboutX(-0.1f);
				this->transform.transform.rotate(rotation);
				break;
			}
			}
		}

		void DebugCameraEntity::onKeyUp(KeyboardEvent evt)
		{

		}
	}
}