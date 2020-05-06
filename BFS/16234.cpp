#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
//BOJ 인구이동

int n, l, r;
int map[101][101];
bool flag = true;
typedef pair<int, int> pp;
int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
bool visited[101][101];
void bfs()
{
    vector<pp> united;
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i][j] && !visited[i][j])
            {
                united.clear();
                queue<pp> q;
                q.push(pp(i, j));

                visited[i][j] = true;
                int cnt = 1; //연합국의 수
                united.push_back(pp(i, j));
                int popul = map[i][j];

                while (!q.empty())
                {
                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();

                    for (int i = 0; i < 4; i++)
                    {
                        int nx = x + dx[i];
                        int ny = y + dy[i];

                        if (nx < 0 || nx >= n || ny < 0 || ny >= n || visited[nx][ny])
                            continue;
                        int dist = abs(map[nx][ny] - map[x][y]);

                        if (l <= dist && dist <= r)
                        {
                            //연합이 이루어진다.

                            united.push_back(pp(nx, ny));
                            visited[nx][ny] = true;
                            q.push(pp(nx, ny));
                            cnt++;
                            popul += map[nx][ny];
                        }
                    }
                }
                //해당 좌표에 있는 연합국들을 모두 모았음
                if (united.size() > 1)
                {
                    flag = true;
                    //나 말고도 다른 나라들이 있다면
                    int avg = popul / cnt;
                    for (auto pos : united)
                    {
                        map[pos.first][pos.second] = avg;
                    }
                }
            }
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> l >> r;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }
    int ans = 0;
    while (flag)
    {
        flag = false;

        bfs();
        if (flag)
            ans++;
    }

    cout << ans << '\n';

    return 0;
}