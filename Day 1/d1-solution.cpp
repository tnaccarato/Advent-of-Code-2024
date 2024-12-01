//
// Created by tomna on 01/12/2024.
//

#include <bits/stdc++.h>

using namespace std;

class Solution {
  public:
    static tuple<vector<int>, vector<int>> read_columns_from_file(const string& fileName) {
        /*
            * Read two columns from a file and return them as vectors
            * @param fileName: The name of the file to read from
            * @return: A tuple containing two vectors of integers
        */

        // Initialise columns
        vector<int> column1;
        vector<int> column2;

        // Open the file
        ifstream inputFile(fileName);

        // Handle file opening error
        if (!inputFile) {
            cerr << "Error: Unable to open the file!" << endl;
            return {column1, column2};
        }

        // Assign temporary variables to store the columns
        int num1, num2;
        // Push the columns into the vectors
        while (inputFile >> num1 >> num2) {
            column1.push_back(num1);
            column2.push_back(num2);
        }

        inputFile.close();

        // Return tuple of the columns
        return {column1, column2};
    }
};

// Define the main function globally
int main() {
    auto [column1, column2] = Solution::read_columns_from_file("input.txt");

    // Sort the columns in descending order
    sort(column1.begin(), column1.end(), greater<>());
    sort(column2.begin(), column2.end(), greater<>());

    int distance_sum = 0;
    // Loop through columns
    while (!column1.empty()) {
        // Calculate the absolute difference between the last elements of the columns
        distance_sum += abs(column1.back() - column2.back());
        // Remove the last elements of the columns
        column1.pop_back();
        column2.pop_back();
    }

    cout << "Sum of distances: " << distance_sum << endl;

    return 0;
}
