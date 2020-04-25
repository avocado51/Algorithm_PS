#include <iostream>
#include <vector>

using namespace std;

char replAlph[26] = {'S', 'N', 'V', 'F', 'R', 'G', 'H', 'J', 'O', 'K', 'L', ';', ',', 'M', 'P', '[', 'W', 'T', 'D', 'Y', 'I', 'B', 'E', 'C', 'U', 'X'};

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string input;
    while (getline(cin, input))
    {
        string output = "";
        for (int i = 0; i < input.size(); i++)
        {
            char c = input[i];
            if (c == '/')
            {
                output += '.';
            }
            else if (c == '1')
            {
                output += '\\`';
            }
            else if (c == '\'')
            {
                output += ';';
            }
            else if (c == ']')
            {
                output += '[';
            }
            else if (c == '.')
            {
                output += ',';
            }
            else if (c == '=')
            {
                output += '-';
            }
            else if ('0' <= c && c <= '9')
            {

                char next = (c - '0') - 1 < 0 ? '9' : c - 1;
                output += next;
            }
            else if ('-' == c)
            {
                output += '0';
            }
            else if (('A' <= c && c <= 'Z') || c == ';' || c == ',' || c == '[')
            {
                int idx = 0;
                for (int j = 0; j < 26; j++)
                {
                    if (replAlph[j] == c)
                    {
                        idx = j;
                        break;
                    }
                }
                output += 'A' + idx;
            }
            else
            {
                output += input[i];
            }
        }
        cout << output << '\n';
    }
    return 0;
}