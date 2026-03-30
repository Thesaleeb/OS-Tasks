#include <iostream>
#include <filesystem>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

int main() {
    string path;
    int binSize;

    // Ask user for folder path
    cout << "Enter folder path: ";
    getline(cin, path);  // allows spaces in path

    // Ask user for bin size
    cout << "Enter bin size: ";
    cin >> binSize;

    vector<long long> sizes; // store file sizes

    // Go through all files in the folder
    for (auto file : fs::recursive_directory_iterator(path)) {
        if (fs::is_regular_file(file)) {
            sizes.push_back(fs::file_size(file)); // save size
        }
    }

    // Find biggest file size
    long long maxSize = 0;
    for (long long s : sizes) {
        if (s > maxSize)
            maxSize = s;
    }

    // Number of bins needed
    int numberOfBins = (maxSize / binSize) + 1;

    vector<int> bins(numberOfBins, 0); // all bins start at 0

    // Put each file into a bin
    for (long long s : sizes) {
        int index = s / binSize;
        bins[index]++;
    }

    // Print histogram
    cout << "\nHistogram:\n";

    for (int i = 0; i < numberOfBins; i++) {
        long long start = i * binSize;
        long long end = start + binSize - 1;

        cout << start << " - " << end << " : ";

        // Print stars
        for (int j = 0; j < bins[i]; j++) {
            cout << "*";
        }

        cout << " (" << bins[i] << ")" << endl;
    }

    return 0;
}