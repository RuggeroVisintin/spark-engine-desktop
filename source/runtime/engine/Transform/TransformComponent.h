#ifndef __TRANSFORMCOMPONENT_H__
#define __TRANSFORMCOMPONENT_H__

#include <vector>

// assertion library
#include "../../Platform/Assertion/Assert.h"

// component library
#include "../../Core/EntityComponentSystem/Component.h"

// math library
#include "../../Core/math/Transform.h"
#include "../../Core/math/Mat4.h"

namespace SE
{
	namespace engine
	{
		// TODO: review
		class TransformComponent : public SE::core::ecs::Component
		{
			typedef SE::core::ecs::Component			Super;
			typedef SE::core::math::Transform<float>	FloatTransform;
			typedef SE::core::math::Mat4<float>			FloatMatrix4;

		public:
			TransformComponent()
				: Super()
				, mParent(nullptr)
			{
			}

			TransformComponent(const FloatTransform& transform)
				: Super()
				, transform(transform)
				, mParent(nullptr)
			{
			}

			~TransformComponent()
			{
				removeChildren();

				if (mParent != nullptr) {
					makeOrphan();
				}
			}

		public:
			FloatMatrix4								getLocalToWorld() const;

			void										setParent(TransformComponent* parent);
			void										makeOrphan();
			void										addChild(TransformComponent* child);
			void										removeChild(unsigned int childId);
			void										removeChildren();

			bool										isChildOf(TransformComponent* other);
			bool										isParentOf(TransformComponent* other);

		public:
			FloatTransform								transform;

		private:
			// really an optimization?
			//bool										mDirty;

			// const TransformComponent* should not be an issue here
			std::vector<TransformComponent*>			mChildren;
			TransformComponent*							mParent;

			//FloatMatrix4								mCachedWorldMatrix;
		};
	}
}

#endif // !__TRANSFORMCOMPONENT_H__