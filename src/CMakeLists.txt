cmake_minimum_required(VERSION 3.12)
project(BlitzScriptInterpreter)

set(CMAKE_C_STANDARD 11)

# Add your source files here
set(SOURCES
    main.c
    # Add other .c files here
)

add_executable(BlitzScriptInterpreter ${SOURCES})

# Specify any additional include directories if needed
# include_directories(your_include_directory)

# Specify any additional libraries if needed
# target_link_libraries(BlitzScriptInterpreter your_library)

# Add compiler flags if needed (e.g., for warnings, optimizations, etc.)
# target_compile_options(BlitzScriptInterpreter PRIVATE -Wall -O2)

# You can install the executable if desired
# install(TARGETS BlitzScriptInterpreter DESTINATION bin)
