#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[3] = {1, -1, 2};
string lines[2];
int n, k;
int visited[2][100001];
typedef pair<int, int> pp;

void bfs()
{
    queue<pp> q;
    q.push(pp(0, 0));
    //0은 왼쪽, 1는 오른쪽

    int time = 0; //유저가 지나간 칸은 시간이 지나감에 따라 사라진다.
    visited[0][0] = 0;
    while (!q.empty())
    {
        int size = q.size();
        while (size--)
        {
            int line = q.front().first;
            int now = q.front().second;
            q.pop();

            if (now >= n - 1)
            {
                cout << 1 << '\n';
                return;
            }

            for (int i = 0; i < 3; i++)
            {
                int nx = now;
                if (i == 0)
                {
                    nx += dx[i];
                    if (visited[line][nx] != -1 || visited[line][nx] == now)
                        continue;
                    if ((lines[line][nx] - '0'))
                    {
                        //1이면 안전한 칸v

                        visited[line][nx] = now;
                        q.push(pp(line, nx));
                    }
                }
                else if (i == 1)
                {
                    //한 칸 뒤로
                    nx += dx[i];

                    if (nx < 0 || nx <= time)
                        continue;
                    else
                    {
                        if (visited[line][nx] != -1 || visited[line][nx] == now)
                            continue;
                        if ((lines[line][nx] - '0'))
                        {
                            visited[line][nx] = now;
                            q.push(pp(line, nx));
                        }
                    }
                }
                else
                {
                    //다른 줄로 갈아탄다. k번 점프를 해야하낟.
                    nx = now + k;
                    if (nx > n)
                    {
                        cout << 1 << '\n';
                        return;
                    }
                    if (visited[1 - line][nx] != -1 || visited[line][nx] == now)
                        continue;
                    if ((lines[1 - line][nx] - '0'))
                    {
                        visited[1 - line][nx] = now;
                        q.push(pp(1 - line, nx));
                    }
                }
            }
        }
        time++;
    }
    cout << 0 << '\n';
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;

    for (int i = 0; i <= n; i++)
    {
        visited[0][i] = visited[1][i] = -1;
    }
    cin >> lines[0] >> lines[1];
    bfs();

    return 0;
}
/*
8 3
11001001
01110011
ans = 0

8 2
11001001
01110011
ans = 1
*/