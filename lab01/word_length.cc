#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    ifstream file("example.txt");

    if (file.peek() == ifstream::traits_type::eof()) // found peek method from google gemini (prompt: how do you see if a file is empty in c++?)
    {
        cerr << "ERROR: File is empty" << endl;
        return 1;
    }

    string current_word, shortest_word, longest_word;
    int word_count{0}, char_count{0};

    while (file >> current_word)
    {
        ++word_count;
        char_count += current_word.length();
        if (word_count == 1)
        {
            shortest_word = current_word;
            longest_word = current_word;
        }
        else
        {
            if (current_word.length() < shortest_word.length())
            {
                shortest_word = current_word;
            }
            if (current_word.length() > longest_word.length())
            {
                longest_word = current_word;
            }
        }
    }

    file.close();

    cout << fixed << setprecision(2);

    cout << "There are " << word_count << " words in the file." << endl;
    cout << "The shortest word was \"" << shortest_word << "\" with " << shortest_word.length() << " character(s)." << endl;
    cout << "The longest word was \"" << longest_word << "\" with " << longest_word.length() << " character(s)." << endl;
    cout << "The average length was " << static_cast<double>(char_count) / word_count << " character(s)." << endl;

    return 0;
}