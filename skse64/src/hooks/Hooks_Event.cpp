#include "hooks/Hooks_Event.h"

#include <Utilities.h>
#include "api/GameInput.h"
#include "api/GameMenus.h"
#include "papyrus/vm/PapyrusEvents.h"
#include "internal/PluginManager.h"
#include <BranchTrampoline.h>

RelocAddr<uintptr_t> PlayerControls_ctor_Call(0x0063EB50 + 0xD7A);

PlayerControls* PlayerControls::ctor_Hook(void) {
	PlayerControls* result = CALL_MEMBER_FN(this, ctor)();

	MenuManager* mm = MenuManager::GetSingleton();
	if (mm) {
		mm->MenuOpenCloseEventDispatcher()->AddEventSink(&g_menuEventHandler);
	} else {
		_MESSAGE("Failed to register SKSE menuEventHandler!");
	}

	g_modCallbackEventDispatcher.AddEventSink(&g_modCallbackEventHandler);
	g_cameraEventDispatcher.AddEventSink(&g_cameraEventHandler);
	g_crosshairRefEventDispatcher.AddEventSink(&g_crosshairRefEventHandler);
	g_actionEventDispatcher.AddEventSink(&g_actionEventHandler);
	g_ninodeUpdateEventDispatcher.AddEventSink(&g_ninodeUpdateEventHandler);

	InputEventDispatcher* inputEventDispatcher = InputEventDispatcher::GetSingleton();
	if (inputEventDispatcher) {
		inputEventDispatcher->AddEventSink(&g_inputEventHandler);
	} else {
		_MESSAGE("Failed to register SKSE inputEventHandler");
	}

	PluginManager::Dispatch_Message(0, SKSEMessagingInterface::kMessage_InputLoaded, NULL, 0, NULL);

	return result;
}

void Hooks_Event_Commit(void) {
	g_branchTrampoline.Write5Call(PlayerControls_ctor_Call, GetFnAddr(&PlayerControls::ctor_Hook));
}
