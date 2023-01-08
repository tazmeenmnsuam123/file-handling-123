#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

// Function to get the total number of words in a file
int getTotalWords(ifstream &file) {
  int totalWords = 0;
  string word;

  while (file >> word) {
    totalWords++;
  }

  return totalWords;
}

// Function to calculate the percentage of similarity between two files
double getSimilarity(ifstream &file1, ifstream &file2) {
  unordered_map<string, int> words;

  // Read all words from the first file and store their frequencies in the map
  string word;
  while (file1 >> word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower); // convert to lower case
    words[word]++;
  }

  // Read all words from the second file and compare their frequencies with the map
  int commonWords = 0;
  while (file2 >> word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower); // convert to lower case
    if (words[word] > 0) {
      commonWords++;
      words[word]--;
    }
  }

  // Calculate the percentage of similarity
  int totalWords1 = getTotalWords(file1);
  int totalWords2 = getTotalWords(file2);
  double similarity = (double) commonWords / (double) (totalWords1 + totalWords2 - commonWords);
  return similarity * 100.0;
}

int main() {
  cout << "Enter the names of the two files to check for plagiarism: ";
  string fileName1, fileName2;
  cin >> fileName1 >> fileName2;

  // Open the files in text mode
  ifstream file1(fileName1);
  ifstream file2(fileName2);

  // Check if the files were opened successfully
  if (!file1 || !file2) {
    cout << "Error opening one of the files!" << endl;
    return 1;
  }

  // Get the total number of words in each file
  int totalWords1 = getTotalWords(file1);
  int totalWords2 = getTotalWords(file2);

  // Calculate the percentage of similarity between the two files
  double similarity = getSimilarity(file1, file2);

  // Print the summary
  cout << "Total words in " << fileName1 << ": " << totalWords1 << endl;
  cout << "Total words in " << fileName2 << ": " << totalWords2 << endl;
  cout << "Percentage similarity: " << similarity << "%" << endl;

  return 0;
}
