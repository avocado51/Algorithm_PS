#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

//BOJ 과외맨 [5213](https://www.acmicpc.net/problem/5213)

int n;
int tiles[501][1002];
int nums[501][1002];
typedef struct Q
{
    int cnt, x, y;
};
typedef pair<int, int> pp;

int visited[501][1002];

int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, 1, -1};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    int a, b;
    int idx = 1;
    for (int j = 1; j <= n; j++)
    {
        if (j % 2 == 0)
        {
            for (int i = 2; i <= 2 * n - 1; i += 2)
            {
                cin >> a >> b;
                tiles[j][i] = a;
                tiles[j][i + 1] = b;
                nums[j][i] = idx;
                nums[j][i + 1] = idx++;
            }
        }
        else
        {
            for (int i = 1; i <= 2 * n; i += 2)
            {
                cin >> a >> b;

                tiles[j][i] = a;
                tiles[j][i + 1] = b;
                nums[j][i] = idx;
                nums[j][i + 1] = idx++;
            }
        }
    }

    queue<Q> q;
    q.push({1, 1, 1});

    visited[1][1] = 1;

    int lastX = 0; //마지막 행을 저장
    while (!q.empty())
    {
        //왼쪽 타일에서 오른쪽 타일로 이동하낟.
        Q qq = q.front();
        q.pop();

        int cnt = qq.cnt;
        int x = qq.x;
        int y = qq.y;

        lastX = lastX < x ? x : lastX;

        if (x == n && y == n)
        {
            //도착 -> 경로 출력
            //서로를 가르키는 영역을 찾아간다.
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            //타일의 값이 같아야지 넘어갈 수 있다. (같은 타일내는 X)
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 1 || nx > 2 * n || ny < 1 || ny >= 2 * n)
                continue;

            if (visited[nx][ny] && visited[nx][ny] <= cnt)
                continue;

            if (!tiles[nx][ny])
                continue;

            if (x % 2 == 0)
            {
                //짝수일 때는 짝수번째는 왼쪽 타일이다.
                if (y % 2 == 0)
                {
                    if (i == 2)
                    {
                        visited[nx][ny] = cnt;

                        q.push({cnt, nx, ny});
                    }
                    else
                    {
                        if (tiles[x][y] == tiles[nx][ny])
                        {
                            visited[nx][ny] = cnt + 1;

                            q.push({cnt + 1, nx, ny});
                        }
                    }
                }
                else
                {
                    //홀수 일때는 오른쪽 타일이다.
                    if (i == 3)
                    {
                        visited[nx][ny] = cnt;

                        q.push({cnt, nx, ny});
                    }

                    else
                    {
                        if (tiles[x][y] == tiles[nx][ny])
                        {
                            visited[nx][ny] = cnt + 1;

                            q.push({cnt + 1, nx, ny});
                        }
                    }
                }
            }
            else
            {
                //홀수 번째 타일이 왼쪽이다.
                if (y % 2)
                {
                    if (i == 2)
                    {
                        visited[nx][ny] = cnt;

                        q.push({cnt, nx, ny});
                    }
                    else
                    {
                        if (tiles[x][y] == tiles[nx][ny])
                        {
                            visited[nx][ny] = cnt + 1;

                            q.push({cnt + 1, nx, ny});
                        }
                    }
                }
                else
                {
                    if (i == 3)
                    {
                        visited[nx][ny] = cnt;

                        q.push({cnt, nx, ny});
                    }

                    else
                    {
                        if (tiles[x][y] == tiles[nx][ny])
                        {
                            visited[nx][ny] = cnt + 1;

                            q.push({cnt + 1, nx, ny});
                        }
                    }
                }
            }
        }
    }

    bool visit[501][1002];
    set<int> res;

    pp last;
    if (lastX % 2 == 0)
    {
        //짝수면 가장 마지막 숫자가 2*n-1에 있다.
        last = pp(lastX, 2 * n - 1);
    }
    else
    {
        last = pp(lastX, 2 * n);
    }

    visit[last.first][last.second] = true;
    for (int j = last.second; j >= 1; j--)
    {
        if (visited[last.first][j])
        {
            //가장 마지막으로 들른 곳을 찾는다.
            last = {last.first, j};
            break;
        }
    }
    visit[last.first][last.second] = true;
    int end = visited[last.first][last.second];
    res.insert(nums[last.first][last.second]);
    
    int tmp = end;
    while (1)
    {
        int xx = last.first;
        int yy = last.second;

        bool find = false;
        for (int j = 0; j < 4; j++)
        {
            int nx = xx + dx[j];
            int ny = yy + dy[j];

            if (nx < 1 || nx >= 2 * n || ny < 1 || ny >= 2 * n)
                continue;
            if (!visited[nx][ny])
                continue;
            if (visit[nx][ny])
                continue;
            if (visited[nx][ny] == visited[xx][yy] - 1 && nums[nx][ny] < nums[xx][yy])
            {
                last = pp(nx, ny);
                find = true;
                break;
            }
        }

        if (!find)
        {
            if (yy - 1 >= 1 && nums[xx][yy - 1] == nums[xx][yy])
            {
                last = pp(xx, yy - 1);
            }
            else if (yy + 1 <= 2 * n && nums[xx][yy + 1] == nums[xx][yy])
            {
                last = pp(xx, yy + 1);
            }
        }
        end = visited[last.first][last.second];
        visit[last.first][last.second] = true;
        res.insert(nums[last.first][last.second]);

        if (end == 1)
        {
            break;
        }
    }

    cout << res.size() << '\n';
    set<int>::iterator it = res.begin();
    for (; it != res.end(); it++)
        cout << *it << ' ';

    return 0;
}