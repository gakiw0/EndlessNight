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
    # Engine Files
    Engine/Allegro5Exception.cpp
    Engine/Allegro5Exception.hpp
    Engine/AudioHelper.cpp
    Engine/AudioHelper.hpp
    Engine/Collider.cpp
    Engine/Collider.hpp
    Engine/GameEngine.cpp
    Engine/GameEngine.hpp
    Engine/Group.cpp
    Engine/Group.hpp
    Engine/IControl.cpp
    Engine/IControl.hpp
    Engine/IObject.cpp
    Engine/IObject.hpp
    Engine/IScene.cpp
    Engine/IScene.hpp
    Engine/LOG.cpp
    Engine/LOG.hpp
    Engine/Point.cpp
    Engine/Point.hpp
    Engine/Resources.cpp
    Engine/Resources.hpp
    Engine/Sprite.cpp
    Engine/Sprite.hpp
    Engine/AutoScroller.hpp
    Engine/AutoScroller.cpp
    Engine/Animation.hpp
    Engine/Animation.cpp
    Engine/User.hpp
    Engine/User.cpp

    # UI Components
    UI/Component/Image.cpp
    UI/Component/Image.hpp
    UI/Component/ImageButton.cpp
    UI/Component/ImageButton.hpp
    UI/Component/Label.cpp
    UI/Component/Label.hpp
    UI/Component/Slider.cpp
    UI/Component/Slider.hpp
    UI/Component/Text.cpp
    UI/Component/Text.hpp
    UI/Component/Pause.cpp
    UI/Component/Pause.hpp
    UI/Component/MiniMap.cpp
    UI/Component/MiniMap.hpp
    UI/Component/TextInput.hpp
    UI/Component/TextInput.cpp

    # UI Animations

    # Scenes
    Scene/PlayScene.cpp
    Scene/PlayScene.hpp
    Scene/WinScene.cpp
    Scene/WinScene.hpp
    Scene/LoseScene.cpp
    Scene/LoseScene.hpp
    Scene/StartScene.h
    Scene/StartScene.cpp
    Scene/SettingsScene.hpp
    Scene/SettingsScene.cpp
    Scene/StoryScene.hpp
    Scene/StoryScene.cpp
    Scene/ScoreBoardScene.hpp
    Scene/ScoreBoardScene.cpp
    Scene/LoginScene.cpp
    Scene/LoginScene.hpp
    Scene/RegisterScene.cpp
    Scene/RegisterScene.hpp
    Scene/LoginOrRegisterScene.cpp
    Scene/LoginOrRegisterScene.hpp

    #Players
    Player/Player.hpp
    Player/Player.cpp

    #Enemies
    Enemy/Enemy.hpp
    Enemy/Enemy.cpp

    #Bullets
    Bullet/Bullet.hpp
    Bullet/Bullet.cpp

    #Item
    Item/Item.hpp
    Item/Item.cpp
    Item/Coin.hpp
    Item/Coin.cpp
    Item/Heal.hpp
    Item/Heal.cpp
    Item/DamageFlask.hpp
    Item/DamageFlask.cpp
    Item/SpeedFlask.hpp
    Item/SpeedFlask.cpp

    # Main
    main.cpp
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