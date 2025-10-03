#include "hooks/Hooks_Data.h"
#include "api/GameData.h"
#include "internal/PluginManager.h"
#include <BranchTrampoline.h>

UInt32 DataHandler::LoadScripts_Hook() {
	UInt32 ret = CALL_MEMBER_FN(this, LoadScripts)();
	PluginManager::Dispatch_Message(0, SKSEMessagingInterface::kMessage_DataLoaded, (void*)NULL, 0, NULL);
	return ret;
}

RelocAddr<uintptr_t> LoadScripts_Enter(0x00642BD0 + 0x3F7);

void Hooks_Data_Commit(void) {
	g_branchTrampoline.Write5Call(LoadScripts_Enter.GetUIntPtr(), GetFnAddr(&DataHandler::LoadScripts_Hook));
}
