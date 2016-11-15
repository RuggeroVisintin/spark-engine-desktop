#include "TransformComponent.h"


namespace SE
{
	namespace engine
	{
		TransformComponent::FloatMatrix4 TransformComponent::getLocalToWorld() const
		{
			// keep it simple. no dirty, no cached
			FloatMatrix4 transformMatrix = transform.getTransformMatrix();

			if (mParent != nullptr) {
				FloatMatrix4 parentMatrix = mParent->getLocalToWorld();
				transformMatrix = parentMatrix * transformMatrix;
			}

			return transformMatrix;
		}

		void TransformComponent::setParent(TransformComponent* parent)
		{
			SPARK_ASSERT(parent != nullptr, "TransformComponent::setParent passed @param parent is null");

			if (mParent == parent) {
				return;
			}

			for (std::vector<TransformComponent*>::iterator it = mParent->mChildren.begin(); 
				it != mParent->mChildren.end(); 
				it++) 
			{
				if ((*it) == this) {
					mParent->mChildren.erase(it);
				}
			}

			mParent = parent;
			mParent->mChildren.push_back(this);
		}

		void TransformComponent::makeOrphan()
		{
			if (mParent == nullptr) {
				return;
			}

			for (std::vector<TransformComponent*>::iterator it = mParent->mChildren.begin();
				it != mParent->mChildren.end();
				it++)
			{
				if ((*it) == this) {
					mParent->mChildren.erase(it);
				}
			}

			mParent = nullptr;
		}

		void TransformComponent::addChild(TransformComponent* child) {
			SPARK_ASSERT(child != nullptr, "TransformComponent::addChild @param child is null");

			if (child->mParent == this) {
				return;
			}

			mChildren.push_back(child);
			child->mParent = this;
		}

		void TransformComponent::removeChild(unsigned int childId) {

			for (std::vector<TransformComponent*>::iterator it = mChildren.begin();
				it != mChildren.end();
				it++)
			{
				if ((*it)->getUuid() == childId) {
					(*it)->mParent = nullptr;
					mChildren.erase(it);

					return;
				}
			}

			SPARK_ASSERT(false, "TransformComponent::removeChild there are no children with given @param childId");
		}

		void TransformComponent::removeChildren() {
			for (std::vector<TransformComponent*>::iterator it = mChildren.begin();
				it != mChildren.end();
				it++)
			{
				(*it)->mParent = nullptr;
			}

			mChildren.clear();
		}

		bool TransformComponent::isChildOf(TransformComponent* other)
		{
			SPARK_ASSERT(other != nullptr, "TransformComponent::isChildOf @param other is null");

			return other == mParent;
		}

		bool TransformComponent::isParentOf(TransformComponent* other)
		{
			SPARK_ASSERT(other != nullptr, "TransformComponent::isParentOf @param other is null");

			return other->mParent == this;
		}
	}
}