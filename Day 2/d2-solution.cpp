//
// Created by tomna on 02/12/2024.
//

#include <bits/stdc++.h>

using namespace std;

/*
Read each line from file and return as 2D vector
@param fileName: The name of the file to read from
@return: A 2D vector of integers
 */
static vector<vector<int>> read_lines_from_file(const string &fileName) {
    // Initialise 2D vector
    vector<vector<int>> lines;

    // Open the file
    ifstream inputFile(fileName);

    // Handle file opening error
    if (!inputFile) {
        cerr << "Error: Unable to open the file!" << endl;
        return lines;
    }

    // Assign temporary variable to store the line
    string line;
    // Push the lines into the 2D vector
    while (getline(inputFile, line)) {
        // Create a stream from the line
        istringstream lineStream(line);
        // Create a vector to store the numbers in the line
        vector<int> numbers;
        // Assign temporary variable to store the number
        int num;
        // Push the numbers into the vector
        while (lineStream >> num) {
            numbers.push_back(num);
        }
        lines.push_back(numbers);
    }

    inputFile.close();

    // Return 2D vector of lines
    return lines;
}

/*
 * Check if a report is safe by checking the difference between each element
 * @param report: The report to check
 * @return: True if the report is safe, false otherwise
 */
bool is_report_safe(const vector<int>& report) {
    // Get report size
    size_t reportSize = report.size();

    if (reportSize <= 1) return true;

    // Set flags for increasing and decreasing
    bool increasing = true, decreasing = true;

    // Loop through the report
    for (size_t i = 0; i < reportSize - 1; i++) {
        // Calculate difference between current and next element
        int diff = report[i + 1] - report[i];

        // Check if absolute difference is less than 1 or greater than 3
        if (abs(diff) < 1 || abs(diff) > 3) return false;

        // Check if difference is positive
        if (diff > 0) decreasing = false;
        // Check if difference is negative
        if (diff < 0) increasing = false;
    }

    return increasing || decreasing;
    }

/* Check if report is safe allowing for a single element to be removed
 * @param report: The report to check
 * @return: True if the report is safe, false otherwise
 */
bool is_report_safe_with_dampener(const vector<int>& report) {
    if (is_report_safe(report)) return true; // Already safe

    size_t reportSize = report.size();

    // Try removing each level and check if the rest is safe
    for (size_t i = 0; i < reportSize; i++) {
        vector<int> modifiedReport;
        for (size_t j = 0; j < reportSize; j++) {
            if (j != i) modifiedReport.push_back(report[j]); // Skip level i
        }
        if (is_report_safe(modifiedReport)) return true; // Safe if removal works
    }

    return false; // Unsafe if no removal makes it safe
}

int main(){
    const string fileName = INPUT_FILE_PATH;
    vector<vector<int>> reports = read_lines_from_file(fileName);
    int safeReports = 0;
    for (const vector<int>& report: reports) {
        if (is_report_safe(report)) safeReports++;
    }
    cout << "Safe reports: " << safeReports << endl;
    safeReports = 0;
    for (const vector<int>& report: reports) {
        if (is_report_safe_with_dampener(report)) safeReports++;
    }
    cout << "Safe reports with tolerance: " << safeReports << endl;
    return 0;
}
