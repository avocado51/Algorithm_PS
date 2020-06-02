#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

int ans, total = 0;
int map[21][21];
bool visited[21][21];

int n, m; //m은 비용
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
typedef struct Q
{
    int x, y;
};

void bfs()
{
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            queue<Q> q;
            q.push({x, y});
            memset(visited, 0, sizeof(visited));

            visited[x][y] = true;
            int cnt = 0;
            if (map[x][y])
                cnt++;

            int k = 1;
            while (!q.empty())
            {
                //calc
                int cost = cnt * m; //집들이 내는 비용
                int res = k * k + (k - 1) * (k - 1);
                if (cost >= res)
                {
                    ans = max(ans, cnt);
                }
                if (cost > total * m)
                    break;
                if (k > n)
                    break;

                int size = q.size();
                while (size--)
                {
                    Q qq = q.front();
                    q.pop();

                    int xx = qq.x;
                    int yy = qq.y;

                    for (int d = 0; d < 4; d++)
                    {
                        int nx = xx + dx[d];
                        int ny = yy + dy[d];

                        if (nx < 0 || nx >= n || ny < 0 || ny >= n || visited[nx][ny])
                            continue;
                        visited[nx][ny] = true;

                        if (map[nx][ny])
                            cnt++; //집
                        q.push({nx, ny});
                    }
                }

                ++k;
            }
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //운영 비용 = K * K + (K - 1) * (K - 1)
    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        ans = 0;

        cin >> n >> m;

        total = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> map[i][j];
                if (map[i][j])
                    total++;
            }
        }

        bfs();
        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}