#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
//BOJ 미네랄 [2933](https://www.acmicpc.net/problem/2933)

int map[101][101];
int r, c, n;
typedef pair<int, int> pp;
bool visited[101][101];
bool chk[101][101];
bool flag;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
bool checkRange(int x, int y)
{
    if (x < 0 || x >= r || y < 0 || y >= c)
        return false;
    return true;
}

void checkCluster(int x, int y)
{
    //x, y 좌표에 있는 미네랄이 깨짐
    //주변 클러스터를 살펴본다.
    queue<pp> q;
    q.push({x, y});
    memset(visited, 0, sizeof(visited));
    visited[x][y] = true;

    while (!q.empty())
    {
        int xx = q.front().first;
        int yy = q.front().second;
        q.pop();

        for (int j = 0; j < 4; j++)
        {
            int nx = xx + dx[j];
            int ny = yy + dy[j];

            if (checkRange(nx, ny) && !visited[nx][ny])
            {
                visited[nx][ny] = true;
                if (map[nx][ny])
                {
                    //이 좌표의 밑을 검사한다.
                    int i;
                    for (i = nx-1; i >= 0; i--) {
                        if (map[i][ny]) {
                            break;
                        }
                    }
                    
                    if (i < nx-1) {
                        //밑에 하나라도 0이 있다는 뜻 
                        //내려주기 전에 이 좌표와 연결된 애들 중에 아직 클러스터가 유지되는 애들이 있는지 찾아야 한다. 
                        memset(chk, 0, sizeof(chk));
                        flag = false;
                        check(nx, ny);
                    
                        if (flag) {
                            //연결된 애들이 있다 
                            continue;
                        }
                        else {
                            //내려간다. 
                            //chk 표시 된 애들을 전부 일정 높이만큼만 내려주면 된다. 
                            //일정 높이는 내려올 수 있는 높이 중 가장 낮은 높이 
                            //가장 밑에서 chk가 true인 것들에 가장 maxx값 찾는다. 
                           
                        }
                    }
                }
            }
        }
    }
}
void dfs(int x, int y, int label) {
    if (visited[x][y]) return;
    visited[x][y] = true;

    for (int j = 0; j < 4; j++) {
        int nx = x + dx[j];
        int ny = y + dy[j];

        if (checkRange(nx, ny) && map[nx][ny]) dfs(nx, ny, label);
    }
}
int numberingCluster() {
    int label =0;
    for (int i = r-1; i>= 0; i--) {
        for (int j = c-1; j >= 0; j--) {
            if (!visited[i][j] && map[i][j]) {
                ++label;
                dfs(i, j, label);
            }
        }
    }
    return label;
}
int throwBar(int dir, int row)
{
    if (!dir)
    {
        //->
        for (int i = 0; i < c; i++)
        {
            if (map[row][i])
            {
                map[row][i] = 0; //미네랄 파괴
                break;
            }
        }
    }
    else
    {
        for (int i = c - 1; i >= 0; i--)
        {
            if (map[row][i])
            {
                map[row][i] = 0;
                break;
            }
        }
    }
}
int main()
{
    ios_base ::sync_with_stdio(0);
    cin.tie(0);

    cin >> r >> c;

    char cc;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> cc;
            if (cc == 'x')
                //미네랄
                map[i][j] = 1;

            else
                map[i][j] = 0;
        }
    }
    cin >> n;
    int dir = 0;
    int h;
    while (n--)
    {
        cin >> h; //밑에서부터 시작
        int row = r - h;

        throwBar(dir, row);
        int label = numberingCluster();
        checkCluster(label); //깨진 미네랄과 연결된 클러스터가 있다면 그 밑을 본다. -> 밑이 뚫려있다면 일단 내려갈 경우도 존재하는 상태이다.

        dir = 1 - dir;
    }

    return 0;
}