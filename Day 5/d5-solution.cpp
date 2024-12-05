#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Parses the ordering rules from the given lines.
 *
 * @param rulesLines A vector of strings representing the ordering rules in the format "before|after".
 * @param orderingRules A map that stores the ordering rules where the key is the page that must be printed before,
 * and the value is a set of pages that must follow.
 */
void parseOrderingRules(const vector<string>& rulesLines, unordered_map<int, unordered_set<int>>& orderingRules) {
    for (const string& line : rulesLines) {
        istringstream iss(line);
        int before, after;
        char separator;
        // For X|Y, before = X, after = Y, separator = '|'
        iss >> before >> separator >> after;
        orderingRules[before].insert(after);
    }
}

/**
 * @brief Reads the input file and separates ordering rules and update sequences.
 *
 * @param filename The path to the input file.
 * @param orderingRulesLines A vector to store the lines representing ordering rules.
 * @param updatesLines A vector to store the lines representing page updates.
 * @return true if the file was successfully read, false otherwise.
 */
bool readInputFile(const string& filename, vector<string>& orderingRulesLines, vector<string>& updatesLines) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    bool isReadingUpdates = false;

    // Read the input file line by line, distinguishing between ordering rules and updates.
    while (getline(inputFile, line)) {
        if (line.empty()) {
            isReadingUpdates = true;
            continue;
        }
        if (isReadingUpdates) {
            updatesLines.push_back(line);
        } else {
            orderingRulesLines.push_back(line);
        }
    }
    inputFile.close();
    return true;
}

/**
 * @brief Checks if an update sequence is in the correct order according to the given ordering rules.
 *
 * @param update A vector of integers representing the page update sequence.
 * @param orderingRules A map that stores the ordering rules.
 * @return true if the update sequence follows the ordering rules, false otherwise.
 */
bool isCorrectOrder(const vector<int>& update, const unordered_map<int, unordered_set<int>>& orderingRules) {
    unordered_map<int, int> position;
    // Store the position of each page in the update sequence for quick lookups.
    for (size_t i = 0; i < update.size(); ++i) {
        position[update[i]] = i;
    }

    // Iterate over the ordering rules to check if the sequence respects them.
    for (const auto& rule : orderingRules) {
        int before = rule.first;
        if (position.find(before) == position.end()) continue; // Skip if "before" page is not in the update sequence.
        for (int after : rule.second) {
            if (position.find(after) == position.end()) continue;
            if (position[before] > position[after]) {
                return false; // Rule violation: "before" page appears after "after" page.
            }
        }
    }
    return true;
}

/**
 * @brief Gets the middle element from the update sequence.
 *
 * @param update A vector of integers representing the page update sequence.
 * @return The middle element of the update sequence.
 */
int getMiddleElement(const vector<int>& update) {
    return update[update.size() / 2];
}


/**
 * @brief Sums the middle pages of the update sequences that follow the ordering rules.
 *
 * @param updatesLines The vector of strings representing the update sequences.
 * @param orderingRules The <int, unordered_set<int>> map representing the ordering rules.
 * @return Integer representing the sum of the middle pages of the update sequences that follow the ordering rules.
 */
int sumMiddlePages(vector<string> updatesLines, unordered_map<int, unordered_set<int>> orderingRules) {
    int sum = 0;
    for (const string& updateLine : updatesLines) {
        istringstream iss(updateLine);
        vector<int> update;
        int page;
        while (iss >> page) {
            update.push_back(page);
            if (iss.peek() == ',') iss.ignore(); // Ignore the comma separator.
        }

        // If the update sequence is in the correct order, add its middle element to the sum.
        if (isCorrectOrder(update, orderingRules)) {
            sum += getMiddleElement(update);
        }
    }
    return sum;
}

int main() {
    string filename = INPUT_FILE_PATH;
    vector<string> orderingRulesLines;
    vector<string> updatesLines;

    // Read the input file
    if (!readInputFile(filename, orderingRulesLines, updatesLines)) {
        // If the file was not read successfully, return 1 to indicate an error.
        cout << "Error reading the input file: " << filename << endl;
        return 1;
    }

    // Parse ordering rules
    unordered_map<int, unordered_set<int>> orderingRules;
    parseOrderingRules(orderingRulesLines, orderingRules);

    // Parse updates and check order
    int sumOfMiddlePages = sumMiddlePages(updatesLines, orderingRules);


    // Output the result
    cout << "Sum of middle pages: " << sumOfMiddlePages << endl;

    return 0;
}
