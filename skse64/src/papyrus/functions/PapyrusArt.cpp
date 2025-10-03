#include "papyrus/functions/PapyrusArt.h"

#include "api/GameObjects.h"
#include "api/GameData.h"

namespace papyrusArt {
	BSFixedString GetModelPath(BGSArtObject* thisArt) {
		return (thisArt) ? thisArt->texSwap.GetModelName() : NULL;
	}

	void SetModelPath(BGSArtObject* thisArt, BSFixedString nuPath) {
		if (thisArt) {
			thisArt->texSwap.SetModelName(nuPath.data);
		}
	}
} // namespace papyrusArt

#include "papyrus/vm/PapyrusVM.h"
#include "papyrus/vm/PapyrusNativeFunctions.h"

void papyrusArt::RegisterFuncs(VMClassRegistry* registry) {
	registry->RegisterForm(BGSArtObject::kTypeID, "Art");

	registry->RegisterFunction(
		new NativeFunction0<BGSArtObject, BSFixedString>("GetModelPath", "Art", papyrusArt::GetModelPath, registry));

	registry->RegisterFunction(
		new NativeFunction1<BGSArtObject, void, BSFixedString>("SetModelPath", "Art", papyrusArt::SetModelPath, registry));
}