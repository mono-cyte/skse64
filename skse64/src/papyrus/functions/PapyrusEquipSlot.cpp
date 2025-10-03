#include "papyrus/functions/PapyrusEquipSlot.h"

#include "api/GameForms.h"
#include "api/GameObjects.h"
#include "api/GameRTTI.h"

namespace papyrusEquipSlot {
	UInt32 GetNumParents(BGSEquipSlot* equipSlot) {
		return (equipSlot) ? equipSlot->parentSlots.count : 0;
	}

	BGSEquipSlot* GetNthParent(BGSEquipSlot* equipSlot, UInt32 n) {
		if (equipSlot) {
			BGSEquipSlot* nthSlot = NULL;
			equipSlot->parentSlots.GetNthItem(n, nthSlot);
			if (nthSlot)
				return nthSlot;
		}

		return NULL;
	}
} // namespace papyrusEquipSlot

#include "papyrus/vm/PapyrusVM.h"
#include "papyrus/vm/PapyrusNativeFunctions.h"

void papyrusEquipSlot::RegisterFuncs(VMClassRegistry* registry) {
	registry->RegisterForm(BGSEquipSlot::kTypeID, "EquipSlot");

	registry->RegisterFunction(
		new NativeFunction0<BGSEquipSlot, UInt32>("GetNumParents", "EquipSlot", papyrusEquipSlot::GetNumParents, registry));

	registry->RegisterFunction(
		new NativeFunction1<BGSEquipSlot, BGSEquipSlot*, UInt32>("GetNthParent", "EquipSlot", papyrusEquipSlot::GetNthParent, registry));
}
