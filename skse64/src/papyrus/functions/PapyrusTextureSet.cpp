#include "papyrus/functions/PapyrusTextureSet.h"

#include "api/GameObjects.h"

namespace papyrusTextureSet {
	UInt32 GetNumTexturePaths(BGSTextureSet* thisTextureSet) {
		return thisTextureSet ? BGSTextureSet::kNumTextures : NULL;
	}

	BSFixedString GetNthTexturePath(BGSTextureSet* thisTextureSet, UInt32 n) {
		return (thisTextureSet && n < BGSTextureSet::kNumTextures) ? thisTextureSet->texturePaths[n].str : NULL;
	}

	void SetNthTexturePath(BGSTextureSet* thisTextureSet, UInt32 n, BSFixedString texturePath) {
		if (thisTextureSet && n < BGSTextureSet::kNumTextures) {
			thisTextureSet->texturePaths[n].str = texturePath;
		}
	}
} // namespace papyrusTextureSet

#include "papyrus/vm/PapyrusVM.h"
#include "papyrus/vm/PapyrusNativeFunctions.h"

void papyrusTextureSet::RegisterFuncs(VMClassRegistry* registry) {
	registry->RegisterFunction(
		new NativeFunction0<BGSTextureSet, UInt32>("GetNumTexturePaths", "TextureSet", papyrusTextureSet::GetNumTexturePaths, registry));

	registry->RegisterFunction(
		new NativeFunction1<BGSTextureSet, BSFixedString, UInt32>("GetNthTexturePath", "TextureSet", papyrusTextureSet::GetNthTexturePath, registry));

	registry->RegisterFunction(
		new NativeFunction2<BGSTextureSet, void, UInt32, BSFixedString>("SetNthTexturePath", "TextureSet", papyrusTextureSet::SetNthTexturePath, registry));
}