#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//프로그래머스 카카오 기출 [후보키]
//unsolved

int n, m;

typedef vector<vector<string>> V;
typedef vector<int> E;

bool compare(const E &a, const E &b)
{
    return a.size() > b.size();
}
bool check(V relation, E candi)
{
    //해당 컬럼들이 후보키가 될 수 있는지 확인한다.
    int size = candi.size();

    for (int j = 0; j < n - 1; j++)
    {
        for (int k = j + 1; k < n; k++)
        {
            bool flag = false;
            for (int i = 0; i < size; i++)
            {
                if (relation[j][candi[i]] != relation[k][candi[i]])
                {
                    flag = true;
                    break;
                }
            }
            if (!flag)
                return false;
        }
    }
    return true;
}

int solution(vector<vector<string>> relation)
{
    int answer = 0;
    //일단 키 한개로 후보키인지 확인하고
    //후보키가 아닌 것들의 조합을 모두 구한다. (부분집합 )
    // int status = 0;
    n = relation.size();
    m = relation[0].size();

    //chk가 false인 것들 중에 부분집합을 구해서 후보키 집합을 찾는다.
    //비트연산자로 처리한다.
    vector<vector<int>> keys;
    E candi;
    for (int i = 0; i < (1 << m); i++)
    {
        candi.clear();

        for (int j = 0; j < m; j++)
        {
            if (i & (1 << j))
            {
                //모든 부분집합을 구함
                //유일성
                //튜플을 식별하는지 확인한다.
                candi.push_back(j);
                // cout << j << ' ';
                //최소성
                //이 집합의 부분집합이 이미 되어있으면 안된다.
                // cout << relation[0][j] << ' ';
            }
        }
        if (candi.size() > 0)
        {
            if (check(relation, candi))
            {
                keys.push_back(candi);
            }
        }
        // cout << '\n';
    }
    sort(keys.begin(), keys.end(), compare);
    //내림차순 정렬
    //최소성을 만족하지 않은 것들을 지운다.

    // for (int i = 0; i < keys.size(); i++)
    // {
    //     for (int j = 0; j < keys[i].size(); j++)
    //     {
    //         cout << keys[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }
    while (!keys.empty())
    {
        E now = keys.back();
        keys.pop_back();
        answer++;
        vector<vector<int>>::iterator it;
        for (it = keys.begin(); it != keys.end();)
        {
            E next = *it;
            bool chk = false;
            //하나라도 다르면 ok
            
            if (chk)
            {
                it++;
            }
            else
            {
                keys.erase(it);
            }
        }
    }

    return answer;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<string> v1 = {"ab", "c"};
    vector<string> v2 = {"a", "bc"};
    vector<string> v3 = {"x", "xy"};
    vector<string> v4 = {"x", "c"};
    // vector<string> v5 = {"500", "muzi", "music", "3"};
    // vector<string> v6 = {"600", "apeach", "music", "2"};

    V v = {v1, v2, v3};
    cout << solution(v) << '\n';

    return 0;
}