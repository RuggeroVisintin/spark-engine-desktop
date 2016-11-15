#include "TransformSystem.h"

namespace SE
{
	namespace engine
	{
		TransformSystem& TransformSystem::registerComponent(TransformComponent* component)
		{
			mTransforms.push_back(component);

			return *this;
		}

		TransformSystem& TransformSystem::unregisterComponent(unsigned int uuid) 
		{
			for (std::vector<TransformComponent*>::const_iterator it = mTransforms.begin();
				it != mTransforms.end(); it++) {

				if ((*it)->getUuid() == uuid) {
					mTransforms.erase(it);
					break;
				}
			}

			return *this;
		}
	}
}