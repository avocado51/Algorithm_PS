#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//BOJ 개미 

int n, m;
string A, B;
typedef pair<char, bool> cb;
int t;
vector<cb> combine;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();

    cin >> n >> m;
    string A, B;
    cin >> A >> B;

    for (int i = n - 1; i >= 0; i--)
    {
        combine.push_back({A[i], 0});
    }
    int idx = 0;
    for (int i = 0; i < m; i++)
    {
        combine.push_back({B[i], 1});
    }

    cin >> t;

    while (t--)
    {
        bool flag = false;
        for (int i = 0; i < combine.size() - 1; i++)
        {
            if (combine[i].second == 0 && combine[i + 1].second == 1)
            {
                swap(combine[i], combine[i + 1]);
                flag = true;
                i++;
            }
            else
            {
                continue;
            }
        }
        if (!flag)
            break;
    }

    for (int i = 0; i < combine.size(); i++)
    {
        cout << combine[i].first;
    }
    cout << '\n';
    return 0;
}