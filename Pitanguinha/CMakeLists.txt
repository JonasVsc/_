﻿include_directories(3rdparty/imgui)
include_directories(3rdparty/imgui/backends)

add_library(Pitanguinha SHARED 
    "src/Pitanguinha/stb_image.h"
    "src/Pitanguinha/Log.h"
    
    "src/Pitanguinha/Core.h" 

    "src/Pitanguinha/Application.h"
    "src/Pitanguinha/Application.cpp"
     
    "src/Pitanguinha/EntryPoint.h"

    "src/Pitanguinha/Window.h"
    "src/Pitanguinha/Window.cpp"

    "src/Pitanguinha.h"
    "src/pch.h"

    "src/Pitanguinha/Events/Event.h" 
    "src/Pitanguinha/Events/WindowEvent.h" 
    "src/Pitanguinha/Events/EventDispatcher.h"

    #imgui
    "3rdparty/imgui/imgui.cpp"
    "3rdparty/imgui/imgui_demo.cpp"
    "3rdparty/imgui/imgui_draw.cpp"
    "3rdparty/imgui/imgui_tables.cpp"
    "3rdparty/imgui/imgui_widgets.cpp"
    "3rdparty/imgui/backends/imgui_impl_opengl3.cpp" 
    "3rdparty/imgui/backends/imgui_impl_glfw.cpp"    
)

target_precompile_headers(Pitanguinha PRIVATE "src/pch.h")
target_include_directories(Pitanguinha PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(3rdparty/glfw)
add_subdirectory(3rdparty/glad)
add_subdirectory(3rdparty/glm)


target_include_directories(Pitanguinha PRIVATE 3rdparty/glad/include)
target_include_directories(Pitanguinha PRIVATE 3rdparty/glfw/include)
target_link_libraries(Pitanguinha PRIVATE glfw glad glm)


if(WIN32)
    target_compile_definitions(Pitanguinha PRIVATE 
        PTG_PLATFORM_WINDOWS 
        PTG_BUILD_DLL)
endif()

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${EXECUTABLE_OUTPUT_PATH}/assets
)



file(COPY ${CMAKE_SOURCE_DIR}/Pitanguinha/logo DESTINATION ${CMAKE_BINARY_DIR}/Sandbox)