/*************************************************************************
 * Author:          sugarfreeoh
 * Date:            19 March 2016
 * Description:     check if a bank card number is valid or not.
 *************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void DoubleDigits(string &cardNumber);
unsigned int SumDigits(string doubleCardNumber);

int main(int argc, char *argv[])
{
    ifstream inputFile;

    inputFile.open(argv[1]);

    if(inputFile.is_open())
    {
        string cardNumber;

        while(getline(inputFile,cardNumber))
        {
            unsigned int sum;

            unsigned int sumMod;

            //cout << "Card Number to validate: " << cardNumber << endl;

            DoubleDigits(cardNumber);

            //cout << "Card Number doubled: " << cardNumber << endl;

            sum = SumDigits(cardNumber);

            //cout << "Summation: " << sum << endl;

            sumMod = sum % 10;

            //cout << "Modulo: " << sumMod << endl;

            if(sumMod == 0)
            {
                cout << "1" << endl;
            }
            else
            {
                cout << "0" << endl;
            }
        }
    }
    else
    {
        cout << "Error opening input file" << endl;
    }

    return 0;
}

unsigned int SumDigits(string doubleCardNumber)
{
    stringstream ss;

    unsigned int index = 0;
    unsigned int temp = 0;
    unsigned int sum = 0;

    while(index < doubleCardNumber.size())
    {
        if(doubleCardNumber[index] != ' ')
        {
            ss << doubleCardNumber[index];
            ss >> temp;
            sum = sum + temp;

            ss.str("");
            ss.clear();
        }

        ++index;
    }

    return sum;
}

void DoubleDigits(string &cardNumber)
{
    unsigned int index = cardNumber.size();
    unsigned int temp;
    
    stringstream ss;

    bool doubleNumber = false;

    while(index > 0)
    {
        ss.str("");
        ss.clear();

        if(cardNumber[index-1] != ' '
           && doubleNumber == true)
        {
            ss << cardNumber[index-1];
            ss >> temp;

            temp = temp*2;

            if(temp > 10)
            {
                string sumString;

                unsigned int sumIndex = 0;
                unsigned int sumTemp;

                ss.str("");
                ss.clear();

                ss << temp;

                ss >> sumString;
                
                temp = 0;

                while(sumIndex < sumString.size())
                {
                    ss.str("");
                    ss.clear();
                    
                    ss << sumString[sumIndex];
                    ss >> sumTemp;

                    temp = temp + sumTemp;

                    ++sumIndex;
                }
            }
            
            ss.str("");
            ss.clear();

            ss << temp;

            cardNumber[index-1] = ss.str()[0];

            doubleNumber = false;
        }
        else if(cardNumber[index-1] != ' '
                && doubleNumber == false)
        {
            doubleNumber = true;
        }

        temp = 0;

        --index;
    }
}
