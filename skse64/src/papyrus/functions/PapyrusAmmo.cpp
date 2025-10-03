#include "papyrus/functions/PapyrusAmmo.h"
#include "api/GameObjects.h"

namespace papyrusAmmo {
	bool IsBolt(TESAmmo* thisAmmo) {
		return (thisAmmo) ? thisAmmo->isBolt() : false;
	}

	BGSProjectile* GetProjectile(TESAmmo* thisAmmo) {
		return (thisAmmo) ? thisAmmo->settings.projectile : NULL;
	}

	float GetDamage(TESAmmo* thisAmmo) {
		return (thisAmmo) ? thisAmmo->settings.damage : 0.0f;
	}
} // namespace papyrusAmmo

#include "papyrus/vm/PapyrusVM.h"
#include "papyrus/vm/PapyrusNativeFunctions.h"

void papyrusAmmo::RegisterFuncs(VMClassRegistry* registry) {
	registry->RegisterFunction(
		new NativeFunction0<TESAmmo, bool>("IsBolt", "Ammo", papyrusAmmo::IsBolt, registry));

	registry->RegisterFunction(
		new NativeFunction0<TESAmmo, BGSProjectile*>("GetProjectile", "Ammo", papyrusAmmo::GetProjectile, registry));

	registry->RegisterFunction(
		new NativeFunction0<TESAmmo, float>("GetDamage", "Ammo", papyrusAmmo::GetDamage, registry));
}
