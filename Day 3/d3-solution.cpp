//
// Created by tomna on 03/12/2024.
//
#include <bits/stdc++.h>

using namespace std;

/*
 * Read the input file and return as a single string
 * @param fileName: The name of the file to read from
 * @return: A string containing the contents of the file
 */
string read_input_file(const string &fileName) {
    // Open the file
    ifstream inputFile(fileName);

    // Handle file opening error
    if (!inputFile) {
        cerr << "Error: Unable to open the file!" << endl;
        return "";
    }

    // Read the file as a single string
    string input((istreambuf_iterator<char>(inputFile)), (istreambuf_iterator<char>()));

    inputFile.close();

    // Return the input string
    return input;
}

/*
 * Get the valid `mul` instructions
 * @param input: The input string to process
 * @return: A vector of valid `mul` instructions
 */
vector<vector<int>> valid_mul_instructions(const string& input) {
    vector<vector<int>> result;

    // Define the regex for matching valid `mul` instructions
    regex mul_regex(R"(mul\((\d{1,3}),(\d{1,3})\))");

    // Use regex_iterator to find all matches
    auto matches_begin = sregex_iterator(input.begin(), input.end(), mul_regex);
    auto matches_end = sregex_iterator();

    for (sregex_iterator i = matches_begin; i != matches_end; ++i) {
        smatch match = *i;

        // Convert the captured groups to integers
        int num1 = stoi(match[1].str());
        int num2 = stoi(match[2].str());

        // Add the numbers as a pair to the result
        result.push_back({num1, num2});
    }

    return result;
}

/*
 * Get the valid `mul` instructions with switches (do() and don't())
 * @param input: The input string to process
 * @return: A vector of valid `mul` instructions
 */
vector<vector<int>> valid_mul_instructions_with_switches(const string& input) {
    vector<vector<int>> result;
    bool active = true; // Instructions start enabled

    // Define regex for matching all commands
    regex command_regex(R"(do\(\)|don't\(\)|mul\((\d{1,3}),(\d{1,3})\))");

    // Use regex_iterator to find all commands
    auto matches_begin = sregex_iterator(input.begin(), input.end(), command_regex);
    auto matches_end = sregex_iterator();

    for (sregex_iterator i = matches_begin; i != matches_end; ++i) {
        smatch match = *i;
        string command = match.str();

        // Check for `do()` and `don't()` commands
        if (command == "do()") {
            active = true;
        } else if (command == "don't()") {
            active = false;
        }
        // Check for `mul()` commands
        else if (active && match.size() == 3) { // Ensure mul() captured two numbers
            int num1 = stoi(match[1].str());
            int num2 = stoi(match[2].str());
            result.push_back({num1, num2});
        }
    }

    return result;
}

int main () {
    // Read the input file
    const string input = read_input_file(INPUT_FILE_PATH);

    // Get the valid `mul` pairs for part 1
    vector<vector<int>> valid_instructions = valid_mul_instructions(input);
    int mul_sum = 0;
    for (const auto& instruction: valid_instructions) {
        mul_sum += instruction[0] * instruction[1];
    }
    cout << "The sum of the valid `mul` instructions is: " << mul_sum << endl;
    // Get the valid `mul` pairs for part 2
    vector<vector<int>> valid_instructions_with_switches = valid_mul_instructions_with_switches(input);
    int mul_sum_with_switches = 0;
    for (const auto& instruction: valid_instructions_with_switches) {
        mul_sum_with_switches += instruction[0] * instruction[1];
    }
    cout << "The sum of the valid `mul` instructions with switches is: " << mul_sum_with_switches << endl;
    
    return 0;
}



