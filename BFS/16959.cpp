#include <iostream>
#include <vector>
#include <queue>
#define KNIGHT 0
#define BISHOP 1
#define ROOK 2

using namespace std;
int n, ans = 987654321;
int chess[11][11];
typedef pair<int, int> pp;
typedef pair<pp, pp> pppp;

int rdx[4] = {-1, 1, 0, 0}, rdy[4] = {0, 0, -1, 1}; //룩 움직임
int dx[4] = {-1, -1, 1, 1}, dy[4] = {-1, 1, -1, 1}; //그 외

typedef struct Q
{
    int x, y, depth, cnt, value, prev;
    Q(int _x, int _y, int d, int c, int v, int p) : x(_x), y(_y), depth(d), cnt(c), value(v), prev(p){};
};

bool checkRange(int nx, int ny)
{
    if (nx < 0 || nx >= n || ny < 0 || ny >= n)
        return false;
    return true;
}
int min(const int &a, const int &b)
{
    if (a > b)
        return b;
    return a;
}
void bfs(pp start)
{
    queue<Q> q;
    int x = start.first;
    int y = start.second;
    q.push(Q(x, y, 0, 0, KNIGHT, 1));
    q.push(Q(x, y, 0, 0, BISHOP, 1));
    q.push(Q(x, y, 0, 0, ROOK, 1));

    while (!q.empty())
    {
        int size = q.size();

        while (size--)
        {
            Q now = q.front();
            q.pop();
            if (now.depth >= 3)
                continue;

            int x = now.x;
            int y = now.y;
            int cnt = now.cnt;
            int depth = now.depth;
            int value = now.value;

            if (now.prev == n * n)
            {
                ans = min(ans, cnt);
                continue;
            }
            //다 들렀는지 확인하는 과정???????
            //말을 바꾸는 과정도 해야한다.

            cout << chess[x][y] << " " << cnt << " " << now.prev << '\n';
            for (int v = 0; v <= 2; v++)
            {
                if (v == 0)
                {
                    for (int d = 0; d < 4; d++)
                    {
                        int nx = x + rdx[d];
                        int ny = y + rdy[d];

                        while (checkRange(nx, ny))
                        {
                            if (chess[nx][ny] == now.prev + 1)
                            {
                                //구해야 할 다음 수를 지금 찾음
                            }
                            else
                            {
                            }
                            nx += rdx[d];
                            ny += rdy[d];
                        }
                    }
                }
                else if (v == 1)
                {
                    //비숍
                    for (int d = 0; d < 4; d++)
                    {
                        int nx = x + dx[d];
                        int ny = y + dy[d];

                        while (checkRange(nx, ny))
                        {
                            if (chess[nx][ny] == now.prev + 1)
                            {
                                //구해야 할 다음 수를 지금 찾음
                                q.push(Q(nx, ny, 0, cnt + 1, v, chess[nx][ny]));
                            }
                            else
                            {
                                q.push(Q(nx, ny, depth + 1, cnt + 1, v, now.prev));
                            }
                            nx += dx[d];
                            ny += dy[d];
                        }
                    }
                }
                else if (v == 2)
                {
                    //나이트
                    for (int d = 0; d < 4; d++)
                    {
                        int nx = x + dx[d];
                        int ny = y + dy[d];

                        while (checkRange(nx, ny))
                        {
                            if (d == 0)
                            {
                                int nnx = nx + dx[0];
                                int nny = ny + dy[0];

                                if (checkRange(nnx, nny))
                                {
                                    if (chess[nnx][nny] == now.prev + 1)
                                    {
                                        q.push(Q(nnx, nny, 0, cnt + 1, v, chess[nx][ny]));
                                    }
                                    else
                                    {
                                        q.push(Q(nnx, nny, depth + 1, cnt + 1, v, now.prev));
                                    }
                                }
                                nnx = nx + dx[2];
                                nny = ny + dy[2];
                                if (checkRange(nnx, nny))
                                {
                                    if (chess[nnx][nny] == now.prev + 1)
                                    {
                                        q.push(Q(nnx, nny, 0, cnt + 1, v, chess[nx][ny]));
                                    }
                                    else
                                    {
                                        q.push(Q(nnx, nny, depth + 1, cnt + 1, v, now.prev));
                                    }
                                }
                            }
                            else if (d == 1)
                            {

                                int nnx = nx + dx[0];
                                int nny = ny + dy[0];

                                if (checkRange(nnx, nny))
                                {
                                    if (chess[nnx][nny] == now.prev + 1)
                                    {
                                        q.push(Q(nnx, nny, 0, cnt + 1, v, chess[nx][ny]));
                                    }
                                    else
                                    {
                                        q.push(Q(nnx, nny, depth + 1, cnt + 1, v, now.prev));
                                    }
                                }
                                nnx = nx + dx[3];
                                nny = ny + dy[3];
                                if (checkRange(nnx, nny))
                                {
                                    if (chess[nnx][nny] == now.prev + 1)
                                    {
                                        q.push(Q(nnx, nny, 0, cnt + 1, v, chess[nx][ny]));
                                    }
                                    else
                                    {
                                        q.push(Q(nnx, nny, depth + 1, cnt + 1, v, now.prev));
                                    }
                                }
                            }
                            else if (d == 2)
                            {

                                int nnx = nx + dx[2];
                                int nny = ny + dy[2];

                                if (checkRange(nnx, nny))
                                {
                                    if (chess[nnx][nny] == now.prev + 1)
                                    {
                                        q.push(Q(nnx, nny, 0, cnt + 1, v, chess[nx][ny]));
                                    }
                                    else
                                    {
                                        q.push(Q(nnx, nny, depth + 1, cnt + 1, v, now.prev));
                                    }
                                }
                                nnx = nx + dx[1];
                                nny = ny + dy[1];
                                if (checkRange(nnx, nny))
                                {
                                    if (chess[nnx][nny] == now.prev + 1)
                                    {
                                        q.push(Q(nnx, nny, 0, cnt + 1, v, chess[nx][ny]));
                                    }
                                    else
                                    {
                                        q.push(Q(nnx, nny, depth + 1, cnt + 1, v, now.prev));
                                    }
                                }
                            }
                            else if (d == 3)
                            {
                                int nnx = nx + dx[3];
                                int nny = ny + dy[3];

                                if (checkRange(nnx, nny))
                                {
                                    if (chess[nnx][nny] == now.prev + 1)
                                    {
                                        q.push(Q(nnx, nny, 0, cnt + 1, v, chess[nx][ny]));
                                    }
                                    else
                                    {
                                        q.push(Q(nnx, nny, depth + 1, cnt + 1, v, now.prev));
                                    }
                                }
                                nnx = nx + dx[1];
                                nny = ny + dy[1];
                                if (checkRange(nnx, nny))
                                {
                                    if (chess[nnx][nny] == now.prev + 1)
                                    {
                                        q.push(Q(nnx, nny, 0, cnt + 1, v, chess[nx][ny]));
                                    }
                                    else
                                    {
                                        q.push(Q(nnx, nny, depth + 1, cnt + 1, v, now.prev));
                                    }
                                }
                            }
                        }
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

    cin >> n;

    pp start;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> chess[i][j];
            if (chess[i][j] == 1)
                start = pp(i, j);
        }
    }

    bfs(start);

    cout << ans << '\n';
    return 0;
}