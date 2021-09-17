cmake_minimum_required(VERSION 3.19)

cmake_policy(SET CMP0091 NEW)

project(xXBestIaEverXx)

add_executable(xXBestIaEverXx "src/main.cpp"     "src/Goap V1/GoapActionV1.h" "src/Goap V1/GoapActionV1.cpp" "src/Goap V1/GoapAI.h" "src/Goap V1/GoapAI.cpp" "src/Goap V1/EnemyAI.h" "src/Goap V1/Node.h" "src/Goap V1/World.h" "src/Goap V1/AttackPlayerAction.h" "src/Goap V1/GetWeaponAction.h" "src/Goap V1/ReloadAction.cpp" "src/Goap V1/EnemayAI.cpp" "src/Goap V1/IdleAction.h" "src/Goap V1/IdleAction.cpp" "src/Goap V1/AttackPlayerAction.cpp" "src/Goap V1/World.cpp" "src/Goap V1/GetWeaponAction.cpp" "src/Goap V1/MoveToPlayerAction.cpp" "src/Action/GoapAction.h" "src/Action/GoapAction.cpp" src/GoapAgent.cpp src/GoapAgent.h src/Action/Action_MoveToPlayer.cpp src/Action/Action_MoveToPlayer.h src/Action/Action_Reload.cpp src/Action/Action_Reload.h src/Action/Action_PickupWeapon.cpp src/Action/Action_PickupWeapon.h src/GoapPlanner.cpp src/GoapPlanner.h src/GoapNode.h src/Action/Action_AttackPlayer.cpp "src/Action/Action_AttackPlayer.h" "src/Action/Action_Idle.h" "src/Action/Action_Idle.cpp" "src/WorldV2.h" "src/WorldV2.cpp" "src/Action/Action_AttackMelee.h" "src/Action/Action_Teleport.h" "src/Action/Action_MoveToPlayerMelee.h" "src/Action/Action_AttackMelee.cpp" "src/Action/Action_Teleport.cpp" "src/Action/Action_MoveToPlayerMelee.cpp" "src/Action/Action_PutOnBoots.cpp" "src/UtilityAi/Village.h" "src/UtilityAi/Inhabitants/Inhabitant.h" "src/UtilityAi/Inhabitants/Villager.h" "src/UtilityAi/Village.cpp"  "src/UtilityAi/Task.h" "src/UtilityAi/Tasks/CreateVillager.h"  "src/UtilityAi/Inhabitants/Fighter.h" "src/UtilityAi/Tasks/CreateFighter.h" "src/UtilityAi/Tasks/GetFood.h" "src/UtilityAi/Tasks/GetFood.cpp" "src/UtilityAi/Tasks/CreateFighter.cpp" "src/UtilityAi/Tasks/CreateVillager.cpp" "src/UtilityAi/Tasks/GetWood.h" "src/UtilityAi/Tasks/GetWood.cpp" "src/UtilityAi/Tasks/BuildHouse.h" "src/UtilityAi/Tasks/BuildHouse.cpp" "src/UtilityAi/Tasks/CreateHouse.h" "src/UtilityAi/Task.h" "src/UtilityAi/UtilityAi.cpp" "src/UtilityAi/UtilityAI.h")

set_property(TARGET xXBestIaEverXx PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_compile_options(xXBestIaEverXx PRIVATE /Zc:__cplusplus)
target_compile_features(xXBestIaEverXx PRIVATE cxx_std_20)
