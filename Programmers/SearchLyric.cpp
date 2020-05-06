#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
//Programmers 카카오 기출 가사검색 https://programmers.co.kr/learn/courses/30/lessons/60060
//unsolved

vector<int> solution(vector<string> words, vector<string> keyword)
{
    vector<int> answer;
    int n = words.size();
    map<string, int> trie;

    for (int i = 0; i < n; i++)
    {
        int m = words[i].size();
        string tmp;
        for (int j = 0; j < m; j++)
        {
            string x(1, words[i][j]);
            tmp += x;
            if (!trie[tmp])
            {
                //새로 만들기
                trie[tmp] = 1;
            }
            else
                trie[tmp] = trie[tmp] + 1;
        }
    }

    int k = keyword.size();
    for (int j = 0; j < k; j++)
    {

        for (auto it : trie)
        {
        }
    }

    return answer;
}