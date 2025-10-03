#include "papyrus/functions/PapyrusTree.h"
#include "api/GameObjects.h"

namespace papyrusTree {
	TESForm* GetIngredient(TESObjectTREE* thisTree) {
		return (thisTree) ? thisTree->produce.produce : NULL;
	}

	void SetIngredient(TESObjectTREE* thisTree, TESForm* ingredient) {
		if (thisTree) {
			thisTree->produce.produce = ingredient;
		}
	}

	BGSSoundDescriptorForm* GetHarvestSound(TESObjectTREE* thisTree) {
		return (thisTree) ? thisTree->produce.harvestSound : NULL;
	}

	void SetHarvestSound(TESObjectTREE* thisTree, BGSSoundDescriptorForm* sound) {
		if (thisTree) {
			thisTree->produce.harvestSound = sound;
		}
	}
} // namespace papyrusTree

#include "papyrus/vm/PapyrusVM.h"
#include "papyrus/vm/PapyrusNativeFunctions.h"

void papyrusTree::RegisterFuncs(VMClassRegistry* registry) {
	registry->RegisterForm(TESObjectTREE::kTypeID, "TreeObject");

	registry->RegisterFunction(
		new NativeFunction0<TESObjectTREE, TESForm*>("GetIngredient", "TreeObject", papyrusTree::GetIngredient, registry));

	registry->RegisterFunction(
		new NativeFunction1<TESObjectTREE, void, TESForm*>("SetIngredient", "TreeObject", papyrusTree::SetIngredient, registry));

	registry->RegisterFunction(
		new NativeFunction0<TESObjectTREE, BGSSoundDescriptorForm*>("GetHarvestSound", "TreeObject", papyrusTree::GetHarvestSound, registry));

	registry->RegisterFunction(
		new NativeFunction1<TESObjectTREE, void, BGSSoundDescriptorForm*>("SetHarvestSound", "TreeObject", papyrusTree::SetHarvestSound, registry));
}
