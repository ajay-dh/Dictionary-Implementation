#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

class Timer
{
  public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const
    {   
        std::chrono::duration<double,std::milli> diff =
                          std::chrono::high_resolution_clock::now() - m_time;
        return diff.count();
    }
  private:
    std::chrono::high_resolution_clock::time_point m_time;
};

void outputCallback(string anagram);
void emptyCallback(string anagram);

int main()
{
    cout << "Enter name of dictionary file: ";
    string filename;
    getline(cin, filename);
    ifstream wordFile(filename.c_str());
    if ( ! wordFile)
    {
        cout << "Cannot open " << filename << endl;
        return 1;
    }

    Dictionary dict;
    
    string word;
    while (getline(wordFile, word))
        dict.insert(word);
    wordFile.close();

    for (;;)
    {
        cout << "Enter a set of letters: ";
        string letters;
        getline(cin,letters);
        if ( ! cin  ||  letters.empty())
            break;

        cout << "Anagrams of " << letters << ":\n";

        dict.lookup(letters, outputCallback);
        
        cout << endl;

	Timer t;
        dict.lookup(letters, emptyCallback);
	double result = t.elapsed();
	
	cout << "The lookup of anagrams takes " << result << " milliseconds." << endl;
    }
}

void outputCallback(string anagram)
{
    cout << "  " << anagram;
}

void emptyCallback(string)
{
      // For timing purposes, we use a callback function that does nothing,
      // so that the cost of doing output of whatever else a callback function
      // might do doesn't enter into the timing of the lookup functionality.
}
