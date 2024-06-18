cmake_minimum_required(VERSION 3.27)
project(EndlessNights)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Include directories
include_directories(.)
include_directories(Resource)

# Copy resources to the binary directory
file(COPY Resource/audios DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY allegro_monolith-5.2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Source files
add_executable(EndlessNights
    Engine/Allegro5Exception.cpp
    Engine/Allegro5Exception.hpp
    Engine/AudioHelper.cpp
    Engine/AudioHelper.hpp
    Bullet/Bullet.cpp
    Bullet/Bullet.hpp
    Engine/Collider.cpp
    Engine/Collider.hpp
    UI/Animation/DirtyEffect.cpp
    UI/Animation/DirtyEffect.hpp
    Enemy/Enemy.cpp
    Enemy/Enemy.hpp
    UI/Animation/ExplosionEffect.cpp
    UI/Animation/ExplosionEffect.hpp
    Bullet/FireBullet.cpp
    Bullet/FireBullet.hpp
    Engine/GameEngine.cpp
    Engine/GameEngine.hpp
    Engine/Group.cpp
    Engine/Group.hpp
    Engine/IControl.cpp
    Engine/IControl.hpp
    UI/Component/Image.cpp
    UI/Component/Image.hpp
    UI/Component/ImageButton.cpp
    UI/Component/ImageButton.hpp
    Engine/IObject.cpp
    Engine/IObject.hpp
    Engine/IScene.cpp
    Engine/IScene.hpp
    UI/Component/Label.cpp
    UI/Component/Label.hpp
    Bullet/LaserBullet.cpp
    Bullet/LaserBullet.hpp
    Turret/LaserTurret.cpp
    Turret/LaserTurret.hpp
    Engine/LOG.cpp
    Engine/LOG.hpp
    Scene/LoseScene.cpp
    Scene/LoseScene.hpp
    Turret/MachineGunTurret.cpp
    Turret/MachineGunTurret.hpp
    main.cpp
    Bullet/MissileBullet.cpp
    Bullet/MissileBullet.hpp
    Turret/MissileTurret.cpp
    Turret/MissileTurret.hpp
    UI/Animation/Plane.cpp
    UI/Animation/Plane.hpp
    Enemy/PlaneEnemy.cpp
    Enemy/PlaneEnemy.hpp
    Scene/PlayScene.cpp
    Scene/PlayScene.hpp
    Engine/Point.cpp
    Engine/Point.hpp
    Engine/Resources.cpp
    Engine/Resources.hpp
    UI/Component/Slider.cpp
    UI/Component/Slider.hpp
    Enemy/SoldierEnemy.cpp
    Enemy/SoldierEnemy.hpp
    Engine/Sprite.cpp
    Engine/Sprite.hpp
    Scene/StageSelectScene.cpp
    Scene/StageSelectScene.hpp
    Enemy/TankEnemy.cpp
    Enemy/TankEnemy.hpp
    Turret/Turret.cpp
    Turret/Turret.hpp
    Turret/TurretButton.cpp
    Turret/TurretButton.hpp
    Scene/WinScene.cpp
    Scene/WinScene.hpp
    Scene/StartScene.cpp
    Scene/StartScene.h
    Scene/SettingsScene.cpp
    Scene/SettingsScene.hpp
    Scene/ScoreBoardScene.cpp
    Scene/ScoreBoardScene.hpp
    Enemy/Tank2Enemy.hpp
    Enemy/Tank2Enemy.cpp
    Bullet/LightBullet.hpp
    Bullet/LightBullet.cpp
    Turret/LightTurret.hpp
    Turret/LightTurret.cpp
    UI/Component/Text.cpp
    UI/Component/Text.hpp
    Turret/Shovel.cpp
    Turret/Shovel.hpp
    Turret/OctoTurret.cpp
    Turret/OctoTurret.hpp
    Turret/RangeBoost.cpp
    Turret/RangeBoost.hpp
    Turret/FireRateBoost.cpp
    Turret/FireRateBoost.hpp
    Enemy/TankAnim.hpp
    Enemy/TankAnim.cpp
    UI/Component/Pause.cpp
    UI/Component/Pause.hpp
)

# Platform-specific settings
if (WIN32)
    target_include_directories(EndlessNights PUBLIC C:/allegro/include)
    target_link_directories(EndlessNights PUBLIC C:/allegro/lib)
    target_link_libraries(EndlessNights liballegro_monolith)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_main-5 allegro_font-5 allegro_dialog-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)
    target_include_directories(EndlessNights PUBLIC ${ALLEGRO5_INCLUDE_DIRS})
    target_link_directories(EndlessNights PUBLIC ${ALLEGRO5_LIBRARY_DIRS})
    target_link_libraries(EndlessNights ${ALLEGRO5_LIBRARIES})
endif()