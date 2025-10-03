#include "hooks/Hooks_Diagnostics.h"
#include <SafeWrite.h>
#include <Utilities.h>
#include <vector>
#include <string>

// not really needed, bethesda does this now

void Hooks_Diagnostics_Commit(void) {
	UInt32 enableDiagnostics = 0;
	if (GetConfigOption_UInt32("General", "EnableDiagnostics", &enableDiagnostics)) {
		if (enableDiagnostics) {
			//
		}
	}
}
