//
// Created by tomna on 01/12/2024.
//

#include <bits/stdc++.h>

using namespace std;

/*
    * Read two columns from a file and return them as vectors
    * @param fileName: The name of the file to read from
    * @return: A tuple containing two vectors of integers
*/
static tuple<vector<int>, vector<int> > read_columns_from_file(const string &fileName) {
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

/*
     * Calculate the sum of the absolute differences between the columns
     * @param file_name: The name of the file to read from
     * @return: The sum of the absolute differences between the columns
 */
int calculate_distance_sum(vector<int> column1, vector<int> column2) {
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

    return distance_sum;
}

/*
    * Calculate the similarity score by adding up the product of the value in column1 and the frequency of the value
    * in column2
    * @param file_name: The name of the file to read from
    * @return: The similarity score
*/
int calculate_similarity_score(const vector<int> &column1, const vector<int> &column2) {
    // Initialise a hash map to store the frequency of values in column2
    unordered_map<int, int> frequency_map;

    // Loop through column2 and store the frequency of each value in the hash map
    for (int value: column2) {
        frequency_map[value]++;
    }

    // Initialise the similarity score
    int similarity_score = 0;

    // if the value in column1 is in column2, add the product of the value in column1 and the frequency of the value
    // in column2 to the similarity score
    for (int value: column1) {
        if (frequency_map.find(value) != frequency_map.end()) {
            similarity_score += value * frequency_map[value];
        }
    }

    return similarity_score;
}

int main() {
    const string file_name = INPUT_FILE_PATH;
    auto [column1, column2] = read_columns_from_file(file_name);
    cout << calculate_distance_sum(column1, column2) << endl;
    cout << calculate_similarity_score(column1, column2) << endl;
    return 0;
}
