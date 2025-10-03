#pragma once

class TESSoulGem;
class BGSApparatus;
class BGSOutfit;
class TESForm;
class VMClassRegistry;
class BGSKeyword;

#include "api/GameTypes.h"

namespace papyrusSoulGem {
	void RegisterFuncs(VMClassRegistry* registry);
	UInt32 GetSoulSize(TESSoulGem* thisGem);
	UInt32 GetGemSize(TESSoulGem* thisGem);
} // namespace papyrusSoulGem

namespace papyrusApparatus {
	void RegisterFuncs(VMClassRegistry* registry);
	UInt32 GetQuality(BGSApparatus* thisApparatus);
	void SetQuality(BGSApparatus* thisApparatus, UInt32 nuQuality);
} // namespace papyrusApparatus

namespace papyrusOutfit {
	void RegisterFuncs(VMClassRegistry* registry);

	UInt32 GetNumParts(BGSOutfit* thisOutfit);
	TESForm* GetNthPart(BGSOutfit* thisOutfit, UInt32 n);
} // namespace papyrusOutfit
