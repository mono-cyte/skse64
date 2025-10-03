#include "papyrus/functions/PapyrusLocation.h"

#include "api/GameForms.h"

namespace papyrusLocation {
	BGSLocation* GetParent(BGSLocation* thisLocation) {
		return thisLocation ? thisLocation->parentLoc : NULL;
	}
} // namespace papyrusLocation

#include "papyrus/vm/PapyrusVM.h"
#include "papyrus/vm/PapyrusNativeFunctions.h"

void papyrusLocation::RegisterFuncs(VMClassRegistry* registry) {
	registry->RegisterFunction(
		new NativeFunction0<BGSLocation, BGSLocation*>("GetParent", "Location", papyrusLocation::GetParent, registry));
}