#include "papyrus/functions/PapyrusSound.h"

#include "api/GameFormComponents.h"
#include "api/GameForms.h"
#include "api/GameObjects.h"

namespace papyrusSound {
	BGSSoundDescriptorForm* GetDescriptor(TESSound* thisSound) {
		return (thisSound) ? thisSound->descriptor : NULL;
	}
} // namespace papyrusSound

#include "papyrus/vm/PapyrusVM.h"
#include "papyrus/vm/PapyrusNativeFunctions.h"

void papyrusSound::RegisterFuncs(VMClassRegistry* registry) {
	registry->RegisterFunction(
		new NativeFunction0<TESSound, BGSSoundDescriptorForm*>("GetDescriptor", "Sound", papyrusSound::GetDescriptor, registry));
}