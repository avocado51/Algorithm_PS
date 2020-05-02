#include <iostream>
#include <vector>
#define MAXX 1000001
using namespace std;
//BOj 교환 https://www.acmicpc.net/problem/1039
//unsolved

bool visited[MAXX];

void swap(string &res, int i, int j)
{
    char tmp = res[i];
    res[i] = res[j];
    res[j] = tmp;
}
int swapping(int idx, int next, string res)
{
    if (res[0] == '0')
        return -1;
    if (visited[stoi(res)])
        return stoi(res);
    int ret = stoi(res);
    for (int i = next; i < res.size(); i++)
    {
        if (res[idx] <= res[i])
        {
            swap(res, idx, i);
            visited[stoi(res)] = true;
            ret = max(ret, swapping(idx, i + 1, res));
            visited[stoi(res)] = false;
            swap(res, idx, i);
        }
    }
    return ret;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    int k;
    cin >> s >> k;

    if (s.size() == 1)
        cout << -1 << '\n';
    else if (s.size() == 2)
    {
        //맨 뒷자리가 0이면 항상 s밖에 안됨
        if (s[1] == '0')
            cout << s << '\n';
        else
        {
            //아니면 두 개의 숫자를 계속 바꾸는 결과이다.
            if (k % 2 == 0)
            {
                //짝수번 바꾸면 원래대로
                cout << s << '\n';
            }
            else
                cout << s[1] << s[0] << '\n';
        }
    }
    else
    {
        //s의 길이가 3이상
        int ans = stoi(s);
        while (k--)
        {
            int tmp = 0;
            for (int i = 0; i < s.size() - 1; i++)
            {
                string stmp = to_string(ans);
                int res = swapping(i, i + 1, stmp);
                cout << "D " << res << '\n';
                tmp = tmp > res ? tmp : res;
            }

            ans = ans > tmp ? ans : tmp;
        }
        cout << ans << '\n';
    }

    return 0;
}
