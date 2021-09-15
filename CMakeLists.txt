cmake_minimum_required(VERSION 3.19)

cmake_policy(SET CMP0091 NEW)

project(xXBestIaEverXx)

add_executable(xXBestIaEverXx src/main.cpp     "src/GoapAction.h" "src/GoapAction.cpp" "src/GoapAI.h" "src/GoapAI.cpp" "src/EnemyAI.h" "src/Node.h" "src/World.h" "src/AttackPlayerAction.h" "src/GetWeaponAction.h" "src/ReloadAction.cpp" "src/EnemayAI.cpp" "src/IdleAction.h" "src/IdleAction.cpp")

set_property(TARGET xXBestIaEverXx PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_compile_options(xXBestIaEverXx PRIVATE /Zc:__cplusplus)
target_compile_features(xXBestIaEverXx PRIVATE cxx_std_20)
