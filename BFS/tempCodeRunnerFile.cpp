#include <iostream>
#include <vector>
#include <queue>
#include <deque>

#include <algorithm>
#define MAXX 9999
#define MINN 0
using namespace std;

int visited[MAXX + 1];
char op[MAXX + 1];

void bfs(int start, int dest)
{
    queue<int> q;
    q.push(start);
    visited[start] = -2; //경로의 시작 => 이전 경로

    while (!q.empty())
    {
        int now = q.front();
        q.pop();

        if (now == dest)
        {
            //경로 역추적
            vector<char> res;
            int pos = now;

            while (1)
            {
                res.push_back(op[pos]);
                pos = visited[pos];
                if (visited[pos] == -2)
                    break;
            }

            for (int i = res.size() - 1; i >= 0; i--)
            {
                cout << res[i];
            }
            cout << '\n';
            return;
        }
        // cout << now << '\n';
        for (int i = 0; i < 4; i++)
        {
            int next = now;
            if (i == 0)
            {
                //D
                next *= 2;

                if (next > MAXX)
                {
                    next %= 10000;
                }

                if (visited[next] != -1 || visited[next] == -2)
                    continue;
                visited[next] = now;
                op[next] = 'D';
                q.push(next);
            }
            else if (i == 1)
            {
                next -= 1;
                if (next < MINN)
                {
                    next = MAXX;
                }
                if (visited[next] != -1 || visited[next] == -2)
                    continue;
                visited[next] = now;
                op[next] = 'S';
                q.push(next);
            }
            else if (i == 2)
            {
                //l
                int n = next % 1000;
                int tmp = (next % 1000) * 10;
                next = tmp + n;
                if (visited[next] != -1 || visited[next] == -2)
                    continue;
                visited[next] = now;
                op[next] = 'L';
                q.push(next);
            }
            else if (i == 3)
            {
                int n = next % 10;
                int tmp = next / 10;
                next = tmp + n;
                if (visited[next] != -1 || visited[next] == -2)
                    continue;

                visited[next] = now;
                op[next] = 'R';
                q.push(next);
            }
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        int a, b;
        cin >> a >> b;

        //a-> b로 만들기
        for (int i = 0; i < MAXX + 1; i++)
        {
            visited[i] = -1;
        }

        bfs(a, b);

        // for (int i = 0; i < MAXX + 1; i++)
        // {
        //     if (visited[i] != -1)
        //         cout << i << " " << op[i] << '\n';
        // }
        // cout << '\n';
    }
    return 0;
}