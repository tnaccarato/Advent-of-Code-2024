add_executable(Day1_solution d1-solution.cpp)

# Define the full path to the input file
target_compile_definitions(Day1_solution PRIVATE INPUT_FILE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
