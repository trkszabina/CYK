#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <iterator>
#include <sstream>

using namespace std;

int main()
{

    map<string, string> rules = {
        {"AB", "S"},
        {"CD", "S"},
        {"CB", "S"},
        {"SS", "S"},
        {"BC", "A"},
        {"a", "A"},
        {"SC", "B"},
        {"b", "B,C"},
        {"DD", "C"},
        {"BA", "D"},
    };

    string text = "aabbaba";
    map<string, string>::iterator it;
    vector<vector<string>> pyramid;

    
    for (int i = 0; i < text.length(); i++)
    {
        string textChar(1, text[i]);

        string value = rules.at(textChar);

        vector<string> row;

        row.push_back(value);
        pyramid.push_back(row);
    }

    
    for (int i = 1; i < pyramid.size(); i++) 
    {
        for (int j = 0; j < pyramid.size() - i; j++) 
        {
            string newLetter;
            for (int k = 0; k < i; k++) 
            {
                string left = pyramid[j][k];
                string right = pyramid[j + k + 1][i - k - 1];
                string searchString;

                if (left.find(",") == string::npos && right.find(",") == string::npos)
                {
                    searchString = left + right;
                    it = rules.find(searchString);
                    if (it != rules.end())
                    {
                        if (newLetter.empty())
                        {
                            newLetter.append(it->second);
                        }
                        else
                        {
                            newLetter.append("," + it->second);
                        }
                    }
                }
                else
                {
                    vector<string> splitedLeftLetters;
                    vector<string> splitedRightLetters;

                    stringstream ssLeft(left);
                    stringstream ssRight(right);

                    string token;
                    while (getline(ssLeft, token, ','))
                    {
                        splitedLeftLetters.push_back(token);
                    }

                    while (getline(ssRight, token, ','))
                    {
                        splitedRightLetters.push_back(token);
                    }

                    for (int x = 0; x < splitedLeftLetters.size(); x++)
                    {
                        for (int y = 0; y < splitedRightLetters.size(); y++)
                        {
                            searchString = splitedLeftLetters[x] + splitedRightLetters[y];
                            it = rules.find(searchString);
                            if (it != rules.end())
                            {
                                if (newLetter.empty())
                                {
                                    newLetter.append(it->second);
                                }
                                else
                                {
                                    newLetter.append("," + it->second);
                                }
                            }
                        }
                    }
                }
            }
            if (newLetter.empty())
            {
                newLetter.append("-");
            }

            pyramid[j].push_back(newLetter);
        }
    }

  
    int i = 0;
    int j = pyramid[i].size() - 1;
    cout << string(j + 1, ' ');
    while (j >= 0)
    {

        cout << pyramid[i][j] << " ";

        if (pyramid[i].size() - 1 == j)
        {
            i = 0;
            j--;

            cout << endl;
            cout << string(j + 1, ' ');
        }
        else
        {
            i++;
        }
    }

    cout << endl;
    if (pyramid[0][pyramid[0].size() - 1] != "-")
    {
        cout << "The string could be derivated" << endl;
    }
    else
    {
        cout << "The string could not be derivated" << endl;
    }

    return 0;
}