cmake_minimum_required(VERSION 3.21)
project(ScrollingShooter)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp SDLManager.cpp SDLManager.h Texture.cpp Texture.h Background.cpp Background.h ComponentBasedES/ComponentSystem.h ComponentBasedES/TransformComponent.h ComponentBasedES/SpriteComponent.h ComponentBasedES/AllComponents.h Vector2D.h Vector2D.cpp ComponentBasedES/InputManagerComponent.h ComponentBasedES/ColliderComponent.h Collision.h Collision.cpp ComponentBasedES/ComponentSystem.cpp ComponentBasedES/TileComponent.h AssetManager.h AssetManager.cpp ComponentBasedES/ShooterComponent.h ComponentBasedES/HealthComponent.h ComponentBasedES/HealthComponent.cpp ComponentBasedES/EnemyMovementComponent.h EnemyFactory.h EnemyFactory.cpp ComponentBasedES/UIComponent.h ComponentBasedES/ScoreTrackerComponent.h ComponentBasedES/InvicibilityComponent.h)

INCLUDE(FindPkgConfig)
find_package(SDL2 REQUIRED)
PKG_SEARCH_MODULE(SDL2IMAGE
        REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED
        SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED
        SDL2_Mixer>=2.0.0)
include_directories(${SDL2_INCLUDE_DIRS}
        ${SDL2IMAGE_INCLUDE_DIRS}
        ${SDL2TTF_INCLUDE_DIRS}
        ${SDL2MIXER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARIES}
        ${SDL2IMAGE_LIBRARIES}
        ${SDL2TTF_LIBRARIES}
        ${SDL2MIXER_LIBRARIES})

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${PROJECT_SOURCE_DIR}/cmake")


