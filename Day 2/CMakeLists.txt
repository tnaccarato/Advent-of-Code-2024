add_executable(Day2_solution d2-solution.cpp)

# Define the full path to the input file
target_compile_definitions(Day2_solution PRIVATE SAMPLE_FILE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/sample_input.txt")
target_compile_definitions(Day2_solution PRIVATE INPUT_FILE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")
