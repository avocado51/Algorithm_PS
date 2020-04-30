#include <iostream>
#include <vector>
#include <stack>
#define MAXX 1000001
using namespace std;
//BOJ 오큰수 https://www.acmicpc.net/problem/17298

typedef pair<int, int> pp;

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    int res[MAXX];
    int num[MAXX];

    stack<pp> st;

    for (int i = 0; i < n; i++)
        res[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;

        while (!st.empty())
        {
            if (st.top().second < x)
            {
                res[st.top().first] = x;
                st.pop();
            }
            else
                break;
        }
        st.push(pp(i, x));
    }

    for (int i = 0; i < n; i++)
    {
        cout << res[i] << ' ';
    }
    return 0;
}

/*
5
1 1 1 3 4

5
2 4 6 8 10 

20
5 4 6 9 8 41 3 2 1 5 4 7 5 52 4 5 5 4 5 45
*/