find_package(Magnum REQUIRED
    SceneGraph
    Sdl2Application)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CORRADE_CXX_FLAGS}")
include_directories(${MAGNUM_INCLUDE_DIRS} ${MAGNUM_APPLICATION_INCLUDE_DIRS})

set(Rotten_SRCS
    Application.cpp
    GameScreen.cpp)

add_executable(rottennoodlessmuggler ${Rotten_SRCS})
target_link_libraries(rottennoodlessmuggler
    ${MAGNUM_LIBRARIES}
    ${MAGNUM_SCENEGRAPH_LIBRARIES}
    ${MAGNUM_APPLICATION_LIBRARIES})

if(CORRADE_TARGET_EMSCRIPTEN)
    install(TARGETS rottennoodlessmuggler DESTINATION ${CMAKE_INSTALL_PREFIX})
    install(FILES index.html EmscriptenApplication.js WebApplication.css DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()
