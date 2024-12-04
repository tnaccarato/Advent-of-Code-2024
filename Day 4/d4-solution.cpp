#include <bits/stdc++.h>
using namespace std;

/* Read input file into a 2D vector of characters
 * @param fileName: The name of the file to read from
 * @return: A 2D vector of characters
 */

vector<vector<char> > readFileAs2DVector(const string &filename) {
    vector<vector<char> > grid;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return grid;
    }

    string line;
    while (getline(file, line)) {
        // Convert the line to a vector of chars and add to the grid
        grid.emplace_back(line.begin(), line.end());
    }

    file.close();
    return grid;
}

/* Search for a word in a 2D grid starting from a given coordinate
 * @param grid: The 2D grid to search in
 * @param row: The row index to start searching from
 * @param col: The column index to start searching from
 * @param word: The word to search for
 * @return: The number of times the word is found starting from this cell
 */
int search2D(const vector<vector<char> > &grid, int row, int col, const string &word) {
    int m = grid.size();
    int n = grid[0].size();
    int count = 0;

    // Return 0 if the starting cell does not match the first character of the word
    if (grid[row][col] != word[0]) return 0;

    int len = word.length();

    // x and y direction vectors
    int x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int y[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    // Search word in all 8 directions starting from (row, col)
    for (int dir = 0; dir < 8; dir++) {
        // Initialize starting point for current direction
        int k, rd = row + x[dir], cd = col + y[dir];

        // First character is already checked, match remaining characters
        for (k = 1; k < len; k++) {
            // If out of bounds, break
            if (rd >= m || rd < 0 || cd >= n || cd < 0) break;

            // If not matched, break
            if (grid[rd][cd] != word[k]) break;

            // Move in the current direction
            rd += x[dir], cd += y[dir];
        }

        // If all characters matched, count this occurrence
        if (k == len) count++;
    }

    return count;
}

/* Count the occurrences of a word in a 2D grid
 * @param grid: The 2D grid to search in
 * @param word: The word to search for
 * @return: The count of the word's occurrences in the grid
 */
int countOccurrences(const vector<vector<char> > &grid, const string &word) {
    int totalCount = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    // Search for the word in all cells of the grid
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            totalCount += search2D(grid, row, col, word);
        }
    }

    return totalCount;
}

/* Check if a valid X-MAS pattern exists centred at (row, col) */
bool isValidXMAS(const vector<vector<char> > &grid, int row, int col) {
    int m = grid.size();
    int n = grid[0].size();

    // Check boundaries to ensure the X pattern fits
    if (row - 1 < 0 || row + 1 >= m || col - 1 < 0 || col + 1 >= n)
        return false;

    // Check the two diagonals for "MAS" (forwards or backwards)
    // Top-left to bottom-right diagonal
    bool diagonal1 = (grid[row - 1][col - 1] == 'M' &&
                      grid[row][col] == 'A' &&
                      grid[row + 1][col + 1] == 'S');

    bool diagonal1Reversed = (grid[row - 1][col - 1] == 'S' &&
                              grid[row][col] == 'A' &&
                              grid[row + 1][col + 1] == 'M');

    // Top-right to bottom-left diagonal
    bool diagonal2 = (grid[row - 1][col + 1] == 'M' &&
                      grid[row][col] == 'A' &&
                      grid[row + 1][col - 1] == 'S');

    bool diagonal2Reversed = (grid[row - 1][col + 1] == 'S' &&
                              grid[row][col] == 'A' &&
                              grid[row + 1][col - 1] == 'M');

    // Return true if both diagonals form valid "MAS" patterns
    return (diagonal1 || diagonal1Reversed) && (diagonal2 || diagonal2Reversed);
}

/* Count the number of valid X-MAS patterns in the grid */
int countXMASPatterns(const vector<vector<char> > &grid) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (isValidXMAS(grid, row, col)) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    string filename = INPUT_FILE_PATH;
    vector<vector<char> > grid = readFileAs2DVector(filename);
    if (grid.empty()) {
        cerr << "Error: Could not read grid data. Exiting." << endl;
        return 1;
    }

    int count = countOccurrences(grid, "XMAS");
    cout << "The word 'XMAS' occurs " << count << " times in the grid." << endl;

    int XMASPatterns = countXMASPatterns(grid);

    cout << "There are " << XMASPatterns << " valid X-MAS patterns in the grid." << endl;

    return 0;
}
