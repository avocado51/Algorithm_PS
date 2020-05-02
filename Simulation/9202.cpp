#include <iostream>
#include <vector>
#include <map>
using namespace std;
//boj boggle https://www.acmicpc.net/problem/9202
//unsolved

int w, b;
map<string, int> trie;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> w;

    for (int i = 0; i < w; i++)
    {
        //사전 단어를 입력
        string s;
        cin >> s;

        string tmp;
        for (int j = 0; j < s.size(); j++)
        {
            string x(1, s[j]);
            tmp += x;
            if (trie[tmp])
            {
                trie[tmp] = trie[tmp] + 1;
            }
            else
                trie[tmp] = 1;
        }
    }

    map<string, int>::iterator it;
    cout << "debug ";
    for (it = trie.begin(); it != trie.end(); it++)
    {
        cout << it->first << " " << it->second << '\n';
    }
    cout << '\n';

    cin >> b;

    return 0;
}
