#ifndef __TRANSFORMSYSTEM_H__
#define __TRANSFORMSYSTEM_H__

#include <vector>
#include "TransformComponent.h"

namespace SE
{
	namespace engine
	{
		class TransformSystem
		{
		public:
			TransformSystem()
			{
			}

			~TransformSystem()
			{
			}

		public:
			TransformSystem&					registerComponent(TransformComponent* component);
			TransformSystem&					unregisterComponent(unsigned int uuid);

			void								update() const 
			{
				// TODO: evaluate dirty flag
			}

		private:
			std::vector<TransformComponent*>	mTransforms;
		};
	}
}

#endif // !__TRANSFORMSYSTEM_H__