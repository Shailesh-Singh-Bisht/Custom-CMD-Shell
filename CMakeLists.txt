cmake_minimum_required(VERSION 3.10)
project(MiniShellReactOS)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Make sure the source file exists or update the filename below
add_executable(minishell MyShell.cpp resource.rc)

if(MINGW)
    target_compile_options(minishell PRIVATE -m32)
    target_link_options(minishell PRIVATE -m32 -Wl,--subsystem,console)
else()
    set_target_properties(minishell PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
endif()
