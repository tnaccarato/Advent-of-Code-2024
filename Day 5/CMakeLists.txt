add_executable(Day5_solution d5-solution.cpp)

# Define the full path to the input file
target_compile_definitions(Day5_solution PRIVATE SAMPLE_FILE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/sample_input.txt")
target_compile_definitions(Day5_solution PRIVATE INPUT_FILE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/input.txt")