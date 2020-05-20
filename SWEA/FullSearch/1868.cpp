#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
//SWEA 파핑파핑 지뢰찾기 [1868](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5LwsHaD1MDFAXc&)
int n;
char map[301][301]; //8개 인접한 칸에 몇개의 지뢰가 있는지 저장
bool cnt[301][301];
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

typedef struct Q
{
    int value, x, y;
};
bool operator<(const Q &a, const Q &b)
{
    return a.value > b.value;
}

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        cin >> n;
        memset(cnt, 0, sizeof(cnt));

        int total = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> map[i][j];
                if (map[i][j] == '.')
                    total++;
            }
        }

        priority_queue<Q> pq;

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (map[i][j] == '.')
                {
                    int c = 0;
                    for (int k = 0; k < 8; k++)
                    {
                        int nx = i + dx[k];
                        int ny = j + dy[k];

                        if (nx < 0 || nx >= n || ny < 0 || ny >= n)
                            continue;
                        if (map[nx][ny] == '*')
                            c++;
                    }
                    map[i][j] = c + '0';
                    pq.push({map[i][j], i, j});
                }
            }
        }
        // print();
        // cout << total << '\n';
        //map[][] 의 값이 0이면 주변의 값들을 전부
        while (!pq.empty() && total)
        {
            Q qq = pq.top();
            pq.pop();

            if (cnt[qq.x][qq.y])
            {
                if (!(map[qq.x][qq.y] - '0'))
                {
                    //인접한 칸을 모두 처리해주고 카운트는 올리지 않는다.
                    for (int k = 0; k < 8; k++)
                    {
                        int nx = qq.x + dx[k];
                        int ny = qq.y + dy[k];

                        if (nx < 0 || nx >= n || ny < 0 || ny >= n || map[nx][ny] == '*')
                            continue;

                        if (!cnt[nx][ny])
                        {
                            cnt[nx][ny] = true;
                            total--;
                            if (!total)
                                break;
                        }
                    }
                }
                continue;
            }

            ans++;
            cnt[qq.x][qq.y] = true;
            total--;
            if (!total)
                break;

            if (!(map[qq.x][qq.y] - '0'))
            {
                for (int k = 0; k < 8; k++)
                {
                    int nx = qq.x + dx[k];
                    int ny = qq.y + dy[k];

                    if (nx < 0 || nx >= n || ny < 0 || ny >= n || map[nx][ny] == '*')
                        continue;

                    if (!cnt[nx][ny])
                    {
                        cnt[nx][ny] = true;
                        total--;
                        if (!total)
                            break;
                    }
                }
            }
        }

        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}