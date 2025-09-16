#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    // Variable Declarations
    int x;
    double y;
    char c;
    string s;

    // 1
    cout << "Enter one integer: ";
    cin >> x;
    cout << "You entered the number: " << x << endl;

    // 2
    cout << "\nEnter four integers: ";
    cin >> x;
    cout << "You entered the numbers: " << x << " ";
    cin >> x;
    cout << x << " ";
    cin >> x;
    cout << x << " ";
    cin >> x;
    cout << x << endl;

    // 3
    cout << "\nEnter one integer and one real number: ";
    cin >> x >> y;
    cout << fixed << setprecision(3);
    cout << left << setw(16) << "The real is: " << right << setw(8) << y << endl;
    cout << "The integer is: " << right << setw(8) << x << endl;

    // 1.4
    cout << "\nEnter one real and one integer number: ";
    cin >> y >> x;
    cout << fixed << setprecision(3);
    cout << setfill('.') << left << setw(16) << "The real is: " << setfill('.') << right << setw(8) << y << endl;
    cout << "The integer is: " << setfill('.') << right << setw(8) << x << endl;

    // 5
    cout << "\nEnter a character: ";
    cin >> c;
    cout << "You entered: " << c << endl;

    // 6
    cout << "\nEnter a word: ";
    cin >> s;
    cout << "The word '" << s << "' has " << s.size() << " character(s)." << endl;

    // 7
    cout << "\nEnter an integer and a word: ";
    cin >> x >> s;
    cout << "You entered '" << x << "' and '" << s << "'." << endl;

    // 8
    cout << "\nEnter an character and a word: ";
    cin >> c >> s;
    cout << "You entered the string \"" << s << "\" and the character '" << c << "'." << endl;

    // 9
    cout << "\nEnter a word and real number: ";
    cin >> s >> y;
    cout << fixed << setprecision(3);
    cout << "You entered \"" << s << "\" and \"" << y << "\"." << endl;

    // 10
    cout << "\nEnter a text-line: ";
    cin.ignore();
    getline(cin, s);
    cout << "You entered: \"" << s << "\"" << endl;

    // 11
    cout << "\nEnter a second line of text: ";
    getline(cin, s);
    cout << "You entered: \"" << s << "\"" << endl;

    // 12
    cout << "\nEnter three words: ";
    cin >> s;
    cout << "You entered: '" << s << " ";

    cin >> s;
    cout << s << " ";
    cin >> s;
    cout << s << "'" << endl;

    return 0;
}
