#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    // INPUT PART
    float first_price, last_price, stride, tax_percent;

    cout << "INPUT PART" << endl;
    cout << "==========" << endl;

    do
    {
        cout << left << setw(17) << "Enter first price" << ": ";
        cin >> first_price;
        if (first_price < 0.0)
        {
            cerr << "ERROR: First price must be at least 0 (zero) SEK" << endl;
        }
    } while (first_price < 0.0);

    do
    {
        cout << left << setw(17) << "Enter last price" << ": ";
        cin >> last_price;
        if (last_price < first_price)
        {
            cerr << "ERROR: Last price must be greater than or equal to first price" << endl;
        }
    } while (last_price < first_price);

    do
    {
        cout << left << setw(17) << "Enter stride" << ": ";
        cin >> stride;
        if (stride < 0.01)
        {
            cerr << "ERROR: Stride must be at least 0.01" << endl;
        }
    } while (stride < 0.01);

    do
    {
        cout << left << setw(17) << "Enter tax percent" << ": ";
        cin >> tax_percent;
        if (tax_percent < 0 or tax_percent > 100)
        {
            cerr << "ERROR: Tax percentage must be between 0 and 100 percent (%)" << endl;
        }
    } while (tax_percent < 0 or tax_percent > 100);

    // TAX TABLE
    cout << "\nTAX TABLE\n"
         << "=========" << endl;
    cout << right << setw(12) << "Price"
         << right << setw(17) << "Tax"
         << right << setw(20) << "Price with tax" << endl;
    cout << setfill('-') << setw(49) << "" << setfill(' ') << endl;

    // CALCULATIONS
    float price, tax;
    cout << fixed << setprecision(2);

    for (int i;; ++i)
    {
        price = first_price + i * stride;
        if (price > last_price)
        {
            break;
        }
        tax = price * (tax_percent / 100);
        cout << right << setw(12) << price
             << right << setw(17) << tax
             << right << setw(20) << price + tax << endl;
    }

    return 0;
}