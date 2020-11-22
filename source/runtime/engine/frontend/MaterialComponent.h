#ifndef __MATERIALCOMPONENT_H__
#define __MATERIALCOMPONENT_H__

#include "../../Core/EntityComponentSystem/Component.h"
#include "../../Resource/Material/MaterialResource.h"

namespace SE {
	namespace engine {
		class MaterialComponent : public SE::core::ecs::Component
		{
			friend class										RenderSystem;

			typedef SE::core::ecs::Component					Super;
			typedef SE::resource::Material						MaterialResource;

		public:
			MaterialComponent(MaterialResource& material)
				: Super()
				, mMaterial(material)
			{
				doRendering = true;
			}

		public:
			MaterialComponent&		setMesh(const MaterialResource& material)
			{
				mMaterial = material;
				return *this;
			}

			MaterialResource		getMaterial() const
			{
				return mMaterial;
			}

		public:
			bool						doRendering;

		private:
			MaterialResource			mMaterial;
		};
	}
}


#endif // __MATERIALCOMPONENT_H__