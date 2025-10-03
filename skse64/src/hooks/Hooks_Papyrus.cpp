#include "hooks/Hooks_Papyrus.h"
#include <Relocation.h>
#include <SafeWrite.h>
#include <BranchTrampoline.h>
#include <list>
#include "papyrus/vm/PapyrusVM.h"

#include "papyrus/vm/PapyrusEvents.h"
#include "papyrus/vm/PapyrusDelayFunctors.h"
#include "internal/Serialization.h"

#include "papyrus/functions/PapyrusSKSE.h"
#include "papyrus/functions/PapyrusMath.h"
#include "papyrus/functions/PapyrusWeapon.h"
#include "papyrus/functions/PapyrusKeyword.h"
#include "papyrus/functions/PapyrusForm.h"
#include "papyrus/functions/PapyrusEnchantment.h"
#include "papyrus/functions/PapyrusMagicEffect.h"
#include "papyrus/functions/PapyrusSpell.h"
#include "papyrus/functions/PapyrusEquipSlot.h"
#include "papyrus/functions/PapyrusActor.h"
#include "papyrus/functions/PapyrusWornObject.h"
#include "papyrus/functions/PapyrusGame.h"
#include "papyrus/functions/PapyrusObjectReference.h"
#include "papyrus/functions/PapyrusActiveMagicEffect.h"
#include "papyrus/functions/PapyrusActorBase.h"
#include "papyrus/functions/PapyrusCombatStyle.h"
#include "papyrus/functions/PapyrusModEvent.h"
#include "papyrus/functions/PapyrusHeadPart.h"
#include "papyrus/functions/PapyrusColorForm.h"
#include "papyrus/functions/PapyrusTextureSet.h"
#include "papyrus/functions/PapyrusActorValueInfo.h"
#include "papyrus/functions/PapyrusUICallback.h"
#include "papyrus/functions/PapyrusUI.h"
#include "papyrus/functions/PapyrusUtility.h"
#include "papyrus/functions/PapyrusStringUtil.h"
#include "papyrus/functions/PapyrusQuest.h"
#include "papyrus/functions/PapyrusAlias.h"
#include "papyrus/functions/PapyrusAmmo.h"
#include "papyrus/functions/PapyrusMisc.h"
#include "papyrus/functions/PapyrusArmor.h"
#include "papyrus/functions/PapyrusArmorAddon.h"
#include "papyrus/functions/PapyrusArt.h"
#include "papyrus/functions/PapyrusBook.h"
#include "papyrus/functions/PapyrusCell.h"
#include "papyrus/functions/PapyrusConstructibleObject.h"
#include "papyrus/functions/PapyrusDefaultObjectManager.h"
#include "papyrus/functions/PapyrusFaction.h"
#include "papyrus/functions/PapyrusFlora.h"
#include "papyrus/functions/PapyrusFormList.h"
#include "papyrus/functions/PapyrusSoundDescriptor.h"
#include "papyrus/functions/PapyrusGameData.h"
#include "papyrus/functions/PapyrusIngredient.h"
#include "papyrus/functions/PapyrusLeveledActor.h"
#include "papyrus/functions/PapyrusLeveledItem.h"
#include "papyrus/functions/PapyrusLeveledSpell.h"
#include "papyrus/functions/PapyrusNetImmerse.h"
#include "papyrus/functions/PapyrusPerk.h"
#include "papyrus/functions/PapyrusPotion.h"
#include "papyrus/functions/PapyrusRace.h"
#include "papyrus/functions/PapyrusScroll.h"
#include "papyrus/functions/PapyrusShout.h"
#include "papyrus/functions/PapyrusSound.h"
#include "papyrus/functions/PapyrusSpawnerTask.h"
#include "papyrus/functions/PapyrusInput.h"
#include "papyrus/functions/PapyrusTree.h"
#include "papyrus/functions/PapyrusWeather.h"
#include "papyrus/functions/PapyrusLocation.h"

#include "xbyak/xbyak.h"

typedef void (*_RegisterPapyrusFunctions)(VMClassRegistry** registry);
RelocAddr<_RegisterPapyrusFunctions> RegisterPapyrusFunctions(0x00A19B20);
RelocAddr<uintptr_t> RegisterPapyrusFunctions_Start(0x009BDE90 + 0xCC3);

RelocAddr<uintptr_t> UnregisterFromSleep_Enter(0x009C30A0 + 0x14B);
RelocAddr<uintptr_t> RevertGlobalData_Enter(0x009CA070 + 0x22);
RelocAddr<uintptr_t> RevertGlobalData_Enter2(0x009CA5B0 + 0x288);
RelocAddr<uintptr_t> SaveRegsSleep_Enter(0x009CCAF0 + 0x390);
RelocAddr<uintptr_t> LoadRegsSleep_Enter(0x009CDBD0 + 0x2FB);

RelocAddr<uintptr_t> kDFQueueHook_Base(0x009D0180);
uintptr_t kDFQueueHook_HookAddr	  = kDFQueueHook_Base + 0x6E;
uintptr_t kDFQueueHook_Entry_retn = kDFQueueHook_Base + 0x73;

typedef std::list<SKSEPapyrusInterface::RegisterFunctions> PapyrusPluginList;
static PapyrusPluginList s_pap_plugins;

bool RegisterPapyrusPlugin(SKSEPapyrusInterface::RegisterFunctions callback) {
	s_pap_plugins.push_back(callback);
	return true;
}

void RegisterPapyrusFunctions_Hook(VMClassRegistry** registryPtr) {
	RegisterPapyrusFunctions(registryPtr);

	VMClassRegistry* registry = *registryPtr;

	// registration for classes

	// SKSE
	papyrusSKSE::RegisterFuncs(registry);

	// TESForm
	papyrusForm::RegisterFuncs(registry);

	// DefaultObjectManager
	papyrusDefaultObjectManager::RegisterFuncs(registry);

	// ColorForm
	papyrusColorComponent::RegisterFuncs(registry);
	papyrusColorForm::RegisterFuncs(registry);

	// Art
	papyrusArt::RegisterFuncs(registry);

	// EquipSlot
	papyrusEquipSlot::RegisterFuncs(registry);

	// HeadPart
	papyrusHeadPart::RegisterFuncs(registry);

	// TESObjectCELL
	papyrusCell::RegisterFuncs(registry);

	// ArmorAddon (TESObjectARMA)
	papyrusArmorAddon::RegisterFuncs(registry);

	// TESObjectARMO
	papyrusArmor::RegisterFuncs(registry);

	// TESSoulGem
	papyrusSoulGem::RegisterFuncs(registry);

	// BGSApparatus
	papyrusApparatus::RegisterFuncs(registry);

	// Math
	papyrusMath::RegisterFuncs(registry);

	// Input
	papyrusInput::RegisterFuncs(registry);

	// ObjectReference
	papyrusObjectReference::RegisterFuncs(registry);

	// Weapon
	papyrusWeapon::RegisterFuncs(registry);

	// Ammo
	papyrusAmmo::RegisterFuncs(registry);

	// CombatStyle
	papyrusCombatStyle::RegisterFuncs(registry);

	// Actor
	papyrusActor::RegisterFuncs(registry);

	// ActorBase (TESNPC)
	papyrusActorBase::RegisterFuncs(registry);

	// Outfit
	papyrusOutfit::RegisterFuncs(registry);

	// SoundDescriptor
	papyrusSoundDescriptor::RegisterFuncs(registry);

	// Potion
	papyrusPotion::RegisterFuncs(registry);

	// Race
	papyrusRace::RegisterFuncs(registry);

	// Spell
	papyrusSpell::RegisterFuncs(registry);

	// Enchantment
	papyrusEnchantment::RegisterFuncs(registry);

	// Ingredient
	papyrusIngredient::RegisterFuncs(registry);

	// Scroll
	papyrusScroll::RegisterFuncs(registry);

	// StringUtil
	papyrusStringUtil::RegisterFuncs(registry);

	// Keyword
	papyrusKeyword::RegisterFuncs(registry);

	// TESObjectBOOK
	papyrusBook::RegisterFuncs(registry);

	// ConstructibleObject
	papyrusConstructibleObject::RegisterFuncs(registry);

	// Game
	papyrusGame::RegisterFuncs(registry);

	// UI
	papyrusUI::RegisterFuncs(registry);

	// Alias
	papyrusAlias::RegisterFuncs(registry);

	// Quest
	papyrusQuest::RegisterFuncs(registry);

	// Shout
	papyrusShout::RegisterFuncs(registry);

	// Utility
	papyrusUtility::RegisterFuncs(registry);

	// ActiveMagicEffect
	papyrusActiveMagicEffect::RegisterFuncs(registry);

	// Sound
	papyrusSound::RegisterFuncs(registry);

	// Weather
	papyrusWeather::RegisterFuncs(registry);

	// NetImmerse
	papyrusNetImmerse::RegisterFuncs(registry);

	// TextureSet
	papyrusTextureSet::RegisterFuncs(registry);

	// Tree
	papyrusTree::RegisterFuncs(registry);

	// Flora
	papyrusFlora::RegisterFuncs(registry);

	// Perk
	papyrusPerk::RegisterFuncs(registry);

	// MagicEffect
	papyrusMagicEffect::RegisterFuncs(registry);

	// UICallback
	papyrusUICallback::RegisterFuncs(registry);

	// ModEvent
	papyrusModEvent::RegisterFuncs(registry);

	// ActorValueInfo
	papyrusActorValueInfo::RegisterFuncs(registry);

	// LeveledItem
	papyrusLeveledItem::RegisterFuncs(registry);

	// LeveledSpell
	papyrusLeveledSpell::RegisterFuncs(registry);

	// LeveledActor
	papyrusLeveledActor::RegisterFuncs(registry);

	// WornObject
	papyrusWornObject::RegisterFuncs(registry);

	// Faction
	papyrusFaction::RegisterFuncs(registry);

	// PapyrusSpawnerTask
	papyrusSpawnerTask::RegisterFuncs(registry);

	// FormList
	papyrusFormList::RegisterFuncs(registry);

	// GameData
	papyrusGameData::RegisterFuncs(registry);

	// Location
	papyrusLocation::RegisterFuncs(registry);

	// #ifdef _PPAPI
	//  Plugins
	for (PapyrusPluginList::iterator iter = s_pap_plugins.begin(); iter != s_pap_plugins.end(); ++iter) {
		(*iter)(registry);
	}
	// #endif
}

void SkyrimVM::OnFormDelete_Hook(UInt64 handle) {
	CALL_MEMBER_FN(this, UnregisterFromSleep_Internal)(handle);

	g_menuOpenCloseRegs.UnregisterAll(handle);
	g_inputKeyEventRegs.UnregisterAll(handle);
	g_inputControlEventRegs.UnregisterAll(handle);
	g_modCallbackRegs.UnregisterAll(handle);
	g_actionEventRegs.UnregisterAll(handle);

	g_cameraEventRegs.Unregister(handle);
	g_crosshairRefEventRegs.Unregister(handle);

	Serialization::HandleDeletedForm(handle);
}

void SkyrimVM::RevertGlobalData_Hook(void) {
	CALL_MEMBER_FN(this, RevertGlobalData_Internal)();

	Serialization::HandleRevertGlobalData();
}

bool SkyrimVM::SaveGlobalData_Hook(void* handleReaderWriter, void* saveStorageWrapper) {
	bool success = CALL_MEMBER_FN(this, SaveRegSleepEventHandles_Internal)(handleReaderWriter, saveStorageWrapper);
	Serialization::HandleSaveGlobalData();
	return success;
}

bool SkyrimVM::LoadGlobalData_Hook(void* handleReaderWriter, void* loadStorageWrapper) {
	bool success = CALL_MEMBER_FN(this, LoadRegSleepEventHandles_Internal)(handleReaderWriter, loadStorageWrapper);
	Serialization::HandleLoadGlobalData();
	return success;
}

__int64 DelayFunctorQueue_Hook(float budget) {
	SKSEDelayFunctorManagerInstance().OnPreTick();

	LARGE_INTEGER startTime;
	QueryPerformanceCounter(&startTime);

	// Sharing budget with papyrus queue
	SKSEDelayFunctorManagerInstance().OnTick(startTime.QuadPart, budget);

	return startTime.QuadPart;
}

void Hooks_Papyrus_Init() {
}

void Hooks_Papyrus_Commit() {
	g_branchTrampoline.Write5Call(RegisterPapyrusFunctions_Start, (uintptr_t)RegisterPapyrusFunctions_Hook);

	// GlobalData / event regs
	g_branchTrampoline.Write5Call(UnregisterFromSleep_Enter, GetFnAddr(&SkyrimVM::OnFormDelete_Hook));
	g_branchTrampoline.Write5Call(RevertGlobalData_Enter, GetFnAddr(&SkyrimVM::RevertGlobalData_Hook));	 // Normal game load
	g_branchTrampoline.Write5Call(RevertGlobalData_Enter2, GetFnAddr(&SkyrimVM::RevertGlobalData_Hook)); // New script reload command
	g_branchTrampoline.Write5Call(SaveRegsSleep_Enter, GetFnAddr(&SkyrimVM::SaveGlobalData_Hook));
	g_branchTrampoline.Write5Call(LoadRegsSleep_Enter, GetFnAddr(&SkyrimVM::LoadGlobalData_Hook));

	{
		struct DelayFunctorQueue_Entry_Code : Xbyak::CodeGenerator {
			DelayFunctorQueue_Entry_Code(void* buf) :
				Xbyak::CodeGenerator(4096, buf) {
				// Need timeBudget as parameter
				movss(xmm0, ptr[rsp + 0xB0]);
				mov(rax, (uintptr_t)DelayFunctorQueue_Hook);
				call(rax);

				// Return to original code
				jmp(ptr[rip]);
				dq(kDFQueueHook_Entry_retn);
			}
		};

		void* codeBuf = g_localTrampoline.StartAlloc();
		DelayFunctorQueue_Entry_Code code(codeBuf);
		g_localTrampoline.EndAlloc(code.getCurr());

		g_branchTrampoline.Write5Branch(kDFQueueHook_HookAddr, uintptr_t(code.getCode()));
	}
}
