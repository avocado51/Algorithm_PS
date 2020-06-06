#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;
//SWEA 무선충전 [5644](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRDL1aeugDFAUo)

vector<int> map[11][11];
int m, a;
int moveDirA[101], moveDirB[101];
bool visited[11][11];
bool chk[9][2];

typedef struct BC
{
    int x, y, c, p;
};
typedef struct Q
{
    int cnt;
    BC bc;
};
BC bcs[9];
int dx[5] = {0, -1, 0, 1, 0}, dy[5] = {0, 0, 1, 0, -1};

bool checkRange(int x, int y)
{
    if (x < 1 || x > 10 || y < 1 || y > 10)
        return false;
    return true;
}

int calc()
{
    int maxx = 0;
    for (int i = 1; i <= a; i++)
    {
        for (int j = 1; j <= a; j++)
        {
            //각 BC에 true 표시가 되어있다면 사용자들이 들렀던 곳이고 그 중에서 최대값을 뽑아내본다.
            int res = 0;
            if (chk[i][0])
            {
                if (chk[j][1])
                {
                    res = i == j ? bcs[j].p : bcs[i].p + bcs[j].p;
                }
                else
                {
                    res = bcs[i].p;
                }
            }
            else
            {
                if (chk[j][1])
                    res = bcs[j].p;
            }
            maxx = max(maxx, res);
        }
    }
    return maxx;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        cin >> m >> a;
        for (int i = 1; i <= 10; i++)
        {
            for (int j = 1; j <= 10; j++)
            {
                map[i][j].clear();
            }
        }
        moveDirA[0] = 0;
        moveDirB[0] = 0;
        for (int i = 1; i <= m; i++)
        {
            //이동 정보
            cin >> moveDirA[i];
        }

        for (int i = 1; i <= m; i++)
        {
            //이동 정보
            cin >> moveDirB[i];
        }

        int x, y, c, p;
        for (int i = 1; i <= a; i++)
        {
            //Bc의 정보
            cin >> x >> y >> c >> p;
            bcs[i] = {y, x, c, p};
        }

        //충전소의 c만큼 퍼트린다.
        for (int i = 1; i <= a; i++)
        {
            queue<Q> q;
            q.push({0, bcs[i]});
            memset(visited, 0, sizeof(visited));

            while (!q.empty())
            {
                Q now = q.front();
                q.pop();

                int x = now.bc.x;
                int y = now.bc.y;
                int depth = now.cnt;

                map[x][y].push_back(i);
                visited[x][y] = true;

                if (depth >= now.bc.c)
                    continue;

                for (int j = 1; j <= 4; j++)
                {
                    int nx = x + dx[j];
                    int ny = y + dy[j];

                    if (checkRange(nx, ny) && !visited[nx][ny])
                    {
                        visited[nx][ny] = true;
                        q.push({depth + 1, {nx, ny, now.bc.c, now.bc.p}});
                    }
                }
            }
        }

        //A, B 움직이기
        int Ax = 1, Ay = 1;
        int Bx = 10, By = 10;
        int ans = 0;

        for (int i = 0; i <= m; i++)
        {
            int nAx = Ax + dx[moveDirA[i]];
            int nAy = Ay + dy[moveDirA[i]];
            int nBx = Bx + dx[moveDirB[i]];
            int nBy = By + dy[moveDirB[i]];

            //같은 BC에 접속한 상황일 때
            //BC는 여러개가 있을 수 있음
            //갈 수 있는 곳을 모두 표시함
            memset(chk, 0, sizeof(chk));
            for (int i = 0; i < map[nAx][nAy].size(); i++)
            {
                chk[map[nAx][nAy][i]][0] = true;
            }
            for (int i = 0; i < map[nBx][nBy].size(); i++)
            {
                chk[map[nBx][nBy][i]][1] = true;
            }
            // cout << ans << '\n';
            ans += calc();

            Ax = nAx;
            Ay = nAy;
            Bx = nBx;
            By = nBy;
        }
        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}