#pragma once

#include "internal/PluginAPI.h"

void Hooks_Papyrus_Init();
void Hooks_Papyrus_Commit();

bool RegisterPapyrusPlugin(SKSEPapyrusInterface::RegisterFunctions);
