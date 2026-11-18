#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) 
{
    if (argc < 2) 
    {
        cerr << "Usage: " << argv[0] << " <file_path>\n";
        return 1;
    }

    string filePath = argv[1];
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filePath << "\n";
        return 1;
    }

    // Vectors to store the parsed values
    vector<string> dividends;       // Starts at line 7, every 6th line (7, 13, 19, ...)
    vector<string> divisors;       // Starts at line 9, every 6th line (9, 15, 21, ...)
    vector<string> expectedResults;// Starts at line 10, every 6th line (10, 16, 22, ...)

    string line;
    size_t line_num = 0;

    // Read the file line by line (1-indexed)
    while (getline(file, line)) {
        line_num++;

        // 1. Dividends (Lines 7, 13, 19, ...)
        if (line_num >= 7 && (line_num - 7) % 6 == 0) {
            dividends.push_back(line);
        }

        // 2. Divisors (Lines 9, 15, 21, ...)
        if (line_num >= 9 && (line_num - 9) % 6 == 0) {
            divisors.push_back(line);
        }

        // 3. Expected Results (Lines 10, 16, 22, ...)
        if (line_num >= 10 && (line_num - 10) % 6 == 0) {
            expectedResults.push_back(line);
        }
    }

    file.close();

    // Print out the results to verify
    cout << "--- Dividends --- Size: " << dividends.size() << "\n";
    for (const auto& val : dividends) cout << val << "\n";

    cout << "\n--- Divisors --- Size: " << divisors.size() << "\n";
    for (const auto& val : divisors) cout << val << "\n";

    cout << "\n--- Expected Results --- Size: " << expectedResults.size() << "\n";
    for (const auto& val : expectedResults) cout << val << "\n";

    return 0;
}