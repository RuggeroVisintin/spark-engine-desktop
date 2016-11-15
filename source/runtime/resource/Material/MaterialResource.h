#ifndef __MATERIALRESOURCE_H__
#define __MATERIALRESOURCE_H__

#include "../Resource.h"
#include "../Shader/ShaderResource.h"

#include <math/Vec3.h>
#include <SmartPtrs/SharedPtr.h>

#include "../ResourceHandle.h"

// In the first versions of the engine material parameters will
// be hardcoded inside the shader and the engine. This means that
// it won't be possible to have a huge difference between different
// materials.

// also note that even to change a single texture (from diffuse texture 
// to normal map and so on), a new material resource is needed. In fact 
// a single change to the material resource will be reflected to all
// the objects using that material
namespace SE
{
	namespace resource
	{
		class Material : public IResource
		{
			typedef SE::resource::Shader Shader;

		public:
			struct MaterialParams
			{		
				SE::core::math::Vec3<float> diffuseColor; 
				SE::core::math::Vec3<float> specularColor; 

				float roughness;
				float specularity;
				float metalness;
			};

		public:
			Material()
			{
				params.diffuseColor = SE::core::math::Vec3<float>(0.0f, 0.0f, 0.0f);
				params.specularColor = SE::core::math::Vec3<float>(0.0f, 0.0f, 0.0f);

				params.roughness = 0.5f;
				params.specularity = 0.5f;
			}

			Material(const MaterialParams& params)
				: params(params)
			{
			}

			~Material()
			{
			}

		public:
			MaterialParams				params;
			Shader						shaderProgram;
		};
	}	
}

#endif // !__MATERIALRESOURCE_H__