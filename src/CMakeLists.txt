find_package(Magnum REQUIRED
    MeshTools
    Primitives
    SceneGraph
    Shaders
    Text
    Sdl2Application)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CORRADE_CXX_FLAGS}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/configure.h.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/configure.h)

include_directories(${MAGNUM_INCLUDE_DIRS}
    ${MAGNUM_APPLICATION_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR})

corrade_add_resource(Rotten_Data_SRCS ../data/resources-data.conf)
corrade_add_resource(Rotten_Fonts_RCS ../data/resources-fonts.conf)
corrade_add_resource(Rotten_Shaders_RCS resources-shaders.conf)
corrade_add_resource(Rotten_Textures_RCS ../data/resources-textures.conf)

set(Rotten_SRCS
    Application.cpp
    Bag.cpp
    BagScreen.cpp
    Button.cpp
    ColoringCamera.cpp
    Dumpster.cpp
    GameScreen.cpp
    Item.cpp
    MutableTextSprite.cpp
    Player.cpp
    Rotten.cpp
    SplashScreen.cpp
    Sprite.cpp
    TextureLoader.cpp
    TextSprite.cpp

    ${Rotten_Data_SRCS}
    ${Rotten_Fonts_RCS}
    ${Rotten_Shaders_RCS}
    ${Rotten_Textures_RCS})

add_executable(rottennoodlessmuggler ${Rotten_SRCS})
target_link_libraries(rottennoodlessmuggler
    ${CORRADE_INTERCONNECT_LIBRARIES}
    ${MAGNUM_LIBRARIES}
    ${MAGNUM_PRIMITIVES_LIBRARIES}
    ${MAGNUM_SCENEGRAPH_LIBRARIES}
    ${MAGNUM_SHADERS_LIBRARIES}
    ${MAGNUM_TEXT_LIBRARIES}
    ${MAGNUM_APPLICATION_LIBRARIES})

if(CORRADE_TARGET_EMSCRIPTEN)
    # Statically link the plugins
    find_package(Magnum REQUIRED MagnumFont TgaImporter)
    target_link_libraries(rottennoodlessmuggler
        ${MAGNUM_MAGNUMFONT_LIBRARIES}
        ${MAGNUM_TGAIMPORTER_LIBRARIES}
        ${MAGNUM_LIBRARIES})

    install(TARGETS rottennoodlessmuggler DESTINATION ${CMAKE_INSTALL_PREFIX})
    install(FILES index.html EmscriptenApplication.js WebApplication.css DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()
