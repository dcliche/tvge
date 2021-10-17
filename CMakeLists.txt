cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

project(tvge)

function(add_shader TARGET SHADER)
    find_program(GLSLC glslc)

    set(current-shader-path ${CMAKE_CURRENT_SOURCE_DIR}/shaders/${SHADER})
    set(current-output-path ${CMAKE_BINARY_DIR}/shaders/${SHADER}.spv)

    # Add a custom command to compile GLSL to SPIR-V.
    get_filename_component(current-output-dir ${current-output-path} DIRECTORY)
    file(MAKE_DIRECTORY ${current-output-dir})

    add_custom_command(
           OUTPUT ${current-output-path}
           COMMAND ${GLSLC} -o ${current-output-path} ${current-shader-path}
           DEPENDS ${current-shader-path}
           IMPLICIT_DEPENDS CXX ${current-shader-path}
           VERBATIM)

    # Make sure our build depends on this output.
    set_source_files_properties(${current-output-path} PROPERTIES GENERATED TRUE)
    target_sources(${TARGET} PRIVATE ${current-output-path})
endfunction()

function(add_symlink_dir TARGET DIRNAME)
    set (source "${CMAKE_SOURCE_DIR}/${DIRNAME}")
    set (destination "${CMAKE_CURRENT_BINARY_DIR}/${DIRNAME}")
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination} 
        DEPENDS ${destination}
        COMMENT "symbolic link directory from ${source} => ${destination}"
    )
endfunction()

set (CMAKE_CXX_STANDARD 17)

set (SRC
    camera.cpp
    camera.hpp
    device.cpp
    device.hpp
    first_app.cpp
    first_app.hpp
    game_object.hpp
    keyboard_movement_controller.cpp
    keyboard_movement_controller.hpp
    main.cpp
    model.cpp
    pipeline.cpp
    pipeline.hpp
    renderer.cpp
    renderer.hpp
    simple_render_system.cpp
    simple_render_system.hpp
    swap_chain.cpp
    swap_chain.hpp
    window.cpp
    window.hpp
)

set (SHADER_SRC
    simple_shader.frag
    simple_shader.vert
)

add_executable(${PROJECT_NAME} ${SRC})
foreach(FILE IN LISTS SHADER_SRC)
    add_shader(${PROJECT_NAME} ${FILE})
endforeach()
add_symlink_dir(${PROJECT_NAME} "models")

find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)

find_library(COCOA_LIBRARY Cocoa)
find_library(IOKIT_LIBRARY IOKit)
find_library(COREVIDEO_LIBRARY CoreVideo)

target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan glfw glm::glm tinyobjloader::tinyobjloader)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif()

