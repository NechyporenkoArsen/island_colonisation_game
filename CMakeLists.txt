cmake_minimum_required(VERSION 3.20)
project(isl_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "C:/Libraries/SFML-3.0.0/lib/cmake/SFML")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(isl_game
	Main.cpp
	code/menu/MainMenu.cpp
	code/localisation/loc.cpp
)

target_include_directories(isl_game PRIVATE code/headers)
target_include_directories(isl_game PRIVATE include)

target_link_libraries(isl_game
    SFML::Graphics
    SFML::Window
    SFML::System
)

add_custom_command(TARGET isl_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "C:/Libraries/SFML-3.0.0/bin"
    $<TARGET_FILE_DIR:isl_game>
)

add_custom_command(TARGET isl_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:isl_game>/assets"
)

add_custom_command(TARGET isl_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/localization"
    "$<TARGET_FILE_DIR:isl_game>/localization"
)

add_custom_command(TARGET isl_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_SOURCE_DIR}/game_set.txt"
    "$<TARGET_FILE_DIR:isl_game>/game_set.txt"
)