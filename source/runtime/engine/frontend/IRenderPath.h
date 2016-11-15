#ifndef __IRENDERPATH_H__
#define __IREDNERPATH_H__

#include "CameraComponent.h"
#include "StaticMeshComponent.h"
#include "LightComponent.h"

namespace SE
{
	namespace engine
	{
		class IRenderPath
		{
		public:
			virtual void renderVieweport(
				CameraComponent* camera, 
				std::vector<StaticMeshComponent*> meshes, 
				std::vector<LightComponent*> lights
			) = 0;

		};
	}
}

#endif // !__IRENDERPATH_H__