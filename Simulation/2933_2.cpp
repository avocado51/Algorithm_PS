#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
//BOJ 미네랄 [2933](https://www.acmicpc.net/problem/2933)

int map[101][101];
int r, c, n;
int visited[101][101];

int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

bool checkRange(int x, int y)
{
    if (x < 0 || x >= r || y < 0 || y >= c)
        return false;
    return true;
}

void draw(int idx, int h)
{
    while (h--)
    {
        for (int i = r - 2; i >= 0; i--)
        {
            for (int j = 0; j <= c; j++)
            {
                if (visited[i][j] == idx)
                {
                    map[i + 1][j] = map[i][j];
                    map[i][j] = 0;
                    visited[i + 1][j] = visited[i][j];
                    visited[i][j] = 0;
                }
            }
        }
    }
}
void drawCluster(int label)
{
    for (int i = 1; i <= label; i++)
    {
        //클러스터들이 라벨링 되어있을 때
        //바닥에서부터 가장 조금 내려와야 하는 높이를 구해서 내려준다.
        int minn = 101;
        bool flag = false;
        for (int j = 0; j < c; j++)
        {
            for (int k = r - 1; k >= 0; k--)
            {
                if (visited[k][j] == i)
                {
                    if (k == r - 1)
                    {
                        flag = true;
                        break; //바닥이랑 닿는 면이다.
                    }

                    if (visited[k + 1][j] && visited[k + 1][j] != i)
                    {
                        flag = true;
                        break; //다른 클러스터와 붙어있다. -> 내 밑이 빈공간이 아니다.
                    }

                    //내려갈 수도 있는 경우

                    minn = min(minn, r - (k + 1));

                    for (int z = k + 1; z < r; z++)
                    {
                        if (visited[z][j] && visited[z][j] != i)
                        {
                            //바닥 혹은 다른 클러스터에 닿을 때까지 얼마나 떠있는지
                            minn = min(minn, z - k - 1);
                            break;
                        }
                    }
                }
            }
            if (flag) //다음 라벨 보기
                break;
        }
        if (!flag)
        {
            //내려와야 한다.
            draw(i, minn);
        }
    }
}
void dfs(int x, int y, int label)
{
    if (visited[x][y])
        return;
    visited[x][y] = label;

    for (int j = 0; j < 4; j++)
    {
        int nx = x + dx[j];
        int ny = y + dy[j];

        if (checkRange(nx, ny) && !visited[nx][ny])
        {
            if (map[nx][ny])
                dfs(nx, ny, label);
        }
    }
}
int numberOfCluster()
{
    int label = 0;

    for (int i = r - 1; i >= 0; i--)
    {
        for (int j = c - 1; j >= 0; j--)
        {
            if (!visited[i][j] && map[i][j])
            {
                ++label;
                dfs(i, j, label);
            }
        }
    }
    return label;
}
void throwBar(int dir, int h)
{
    //제일 먼저 만나는 미네랄을 없앤다.
    if (!dir)
    {
        for (int j = 0; j < c; j++)
        {
            if (map[h][j])
            {
                map[h][j] = 0;
                break;
            }
        }
    }
    else
    {
        for (int j = c - 1; j >= 0; j--)
        {
            if (map[h][j])
            {
                map[h][j] = 0;
                break;
            }
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> r >> c;

    char k;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> k;
            if (k == 'x')
            {
                map[i][j] = 1;
            }
            else
                map[i][j] = 0;
        }
    }

    cin >> n;
    int h;
    int dir = 0; //왼-> 오
    while (n--)
    {

        cin >> h;
        int hh = r - h; //위에서부터의 위치

        throwBar(dir, hh);
        memset(visited, 0, sizeof(visited));
        int label = numberOfCluster();
        drawCluster(label);
        dir = 1 - dir;
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (map[i][j])
                cout << "x";
            else
                cout << ".";
        }
        cout << '\n';
    }
    return 0;
}