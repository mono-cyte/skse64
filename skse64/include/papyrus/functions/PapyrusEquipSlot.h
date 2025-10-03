#pragma once

#include <ITypes.h>

class BGSEquipSlot;
struct StaticFunctionTag;
class VMClassRegistry;

namespace papyrusEquipSlot {
	void RegisterFuncs(VMClassRegistry* registry);

	UInt32 GetNumParents(BGSEquipSlot* equipSlot);
	BGSEquipSlot* GetNthParent(BGSEquipSlot* equipSlot, UInt32 n);
} // namespace papyrusEquipSlot
