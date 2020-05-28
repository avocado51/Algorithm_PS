#include <queue>

using namespace std;

#define INF 987654321

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

typedef struct Pos
{
    int x, y, d, maxx;
};

int cost[4][30][30];
int MAXX = INF;

int solution(vector<vector<int>> board)
{
    int answer = 0;
    int n = board.size();

    for (int k = 0; k < 4; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cost[k][i][j] = INF;
            }
        }
    }

    queue<Pos> q;
    for (int i = 0; i < 4; i++)
    {
        q.push({0, 0, i, 0});
        cost[i][0][0] = 0;
    }

    while (!q.empty())
    {

        int cx = q.front().x;
        int cy = q.front().y;
        int cd = q.front().d;
        int cm = q.front().maxx;
        q.pop();

        //도착
        if (cx == n - 1 && cy == n - 1)
        {
            MAXX = min(MAXX, cm);
            continue;
        }

        for (int i = 0; i < 4; i++)
        {
            //방향 전환을 위해
            int nd = (cd + i) % 4;
            int nx = cx + dx[nd];
            int ny = cy + dy[nd];

            if (nx < 0 || nx >= n || ny < 0 || ny >= n)
            {
                continue;
            }

            if (!board[nx][ny])
            {
                if (nd == cd)
                {
                    // 방향이 같으면 100원만 더한다.
                    if (cost[nd][nx][ny] > cm + 100)
                    {
                        cost[nd][nx][ny] = cm + 100;
                        q.push({nx, ny, nd, cost[nd][nx][ny]});
                    }
                }

                else
                {
                    // 현재 방향과 다르면 600원을 더한다.
                    if (cost[nd][nx][ny] > cm + 600)
                    {
                        cost[nd][nx][ny] = cm + 600;
                        q.push({nx, ny, nd, cost[nd][nx][ny]});
                    }
                }
            }
        }
    }

    answer = MAXX;
    return answer;
}
