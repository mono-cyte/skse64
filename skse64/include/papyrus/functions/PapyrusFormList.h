#pragma once

#include "api/GameTypes.h"
#include "papyrus/vm/PapyrusArgs.h"

class BGSListForm;
class VMClassRegistry;

namespace papyrusFormList {
	void RegisterFuncs(VMClassRegistry* registry);

	VMResultArray<TESForm*> ToArray(BGSListForm* list);
} // namespace papyrusFormList