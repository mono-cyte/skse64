#pragma once

class VMClassRegistry;
struct StaticFunctionTag;

#include "api/GameTypes.h"

namespace papyrusGameData {
	void RegisterFuncs(VMClassRegistry* registry);
}