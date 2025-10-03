#pragma once
#include <ITypes.h>


struct StaticFunctionTag;
class VMClassRegistry;

namespace papyrusCamera {
	void RegisterFuncs(VMClassRegistry* registry);

	SInt32 GetCameraState(StaticFunctionTag* base);
	void UpdateThirdPerson(StaticFunctionTag* base);
} // namespace papyrusCamera
