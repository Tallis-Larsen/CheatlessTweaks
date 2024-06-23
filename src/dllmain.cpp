#include <array>
#include <iostream>
#include "dllmain.hpp"
#include "minecraft/src/common/world/level/storage/GameRules.hpp"

SafetyInlineHook _GameRules__registerRules;

void GameRules_registerRules(GameRules* self) {
  _GameRules__registerRules.call<void>(self);

  std::array<GameRulesIndex, 3> noCheatRules = {
    GameRulesIndex::MobGriefing,
    GameRulesIndex::PlayersSleepingPercentage,
    GameRulesIndex::DoWeatherCycle };

  for (int i = 0; i < noCheatRules.size(); i++) {
    self->mGamerules[noCheatRules[i]].mRequiresCheats = false;
  }

}

ModFunction void Initialize(AmethystContext* ctx) {
  HookManager& hooks = ctx->mHookManager;

  hooks.RegisterFunction<&GameRules::_registerRules>("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B F9 48 83 C1");
  hooks.CreateHook<&GameRules::_registerRules>(_GameRules__registerRules, &GameRules_registerRules);

  Log::Info("[CheatlessTweaks] Mod successfully initialized!");
}