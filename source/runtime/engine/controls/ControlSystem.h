#ifndef __INPUTSYSTEM_H__
#define __INPUTSYSTEM_H__

#include <vector>

#include <PlatformUtils.h>
#include <Assertion/Assert.h>
#include <Input/Dispatcher.h>

#include "ControlComponent.h"

namespace SE
{
	namespace engine
	{
		class ControlSystem
		{
			typedef SE::platform::input::Dispatcher InputDispatcher;

		public:
			ControlSystem(InputDispatcher* inputDispatcher)
				: mInputDispatcher(inputDispatcher)
			{
				SPARK_ASSERT(mInputDispatcher != nullptr, "ControlSystem::constructor - @param inputDispatcher - is null");
			}

			~ControlSystem()
			{
			}

		public:
			void registerComponent(ControlComponent* component);
			void update() const;

		private:
			InputDispatcher* mInputDispatcher;

			std::vector<ControlComponent*>  mControls;
		};
	}
}

#endif // !__INPUTSYSTEM_H__ 