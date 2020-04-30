#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int map[7][7];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
typedef pair<int, int> pp;
bool visited[7][7];
void drop(int y, int x)
{
    int row = y;

    int next_row = row + 1;
    while (next_row <= 6 && map[next_row][x] == 0)
    {
        next_row++;
    }
    next_row--;

    swap(map[y][x], map[next_row][x]);
}

// 하나라도 터지면 true, 하나도 터지지 않으면 false
bool bfs(int sy, int sx, int color)
{
    queue<pp> q;

    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            visited[i][j] = false;
        }
    }
    q.push(pp(sy, sx));
    visited[sy][sx] = true;
    int cnt = 1;

    while (!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (1 <= ny && ny <= 6 && 1 <= nx && nx <= 6)
            {
                if (visited[ny][nx] == false && map[ny][nx] == color)
                {
                    q.push({ny, nx});
                    visited[ny][nx] = true;
                    cnt += 1;
                }
            }
        }
    }

    if (cnt >= 3)
    {
        for (int i = 1; i < 7; i++)
        {
            for (int j = 1; j < 7; j++)
            {
                if (visited[i][j] == true)
                {
                    map[i][j] = 0;
                }
            }
        }
        // 터짐
        // 나머지들을 다 떨어뜨린다.
        for (int i = 6; i >= 1; i--)
        {
            for (int j = 6; j >= 1; j--)
            {
                if (map[i][j] != 0)
                {
                    drop(i, j);
                }
            }
        }
        return true;
    }

    // 하나도 안 터졌다
    return false;
}

vector<string> solution(vector<vector<int>> macaron)
{
    vector<string> answer;
    int macaron_size = macaron.size();
    for (int i = 0; i < macaron_size; i++)
    {
        int num = macaron[i][0];
        int color = macaron[i][1];

        int row = 1;
        while (row <= 6 && map[row][num] == 0)
        {
            row++;
        }
        row--;

        map[row][num] = color;

        while (true)
        {
            bool chk = false;
            for (int i = 1; i <= 6; i++)
            {
                for (int j = 1; j <= 6; j++)
                {
                    if (map[i][j] != 0)
                    {
                        chk = bfs(i, j, map[i][j]);
                    }
                }
            }

            // 더 이상 부실 것이 없다.
            if (!chk)
            {
                break;
            }
        }
    }

    for (int i = 1; i <= 6; i++)
    {
        string s;
        for (int j = 1; j <= 6; j++)
        {
            s += to_string(map[i][j]);
        }
        answer.push_back(s);
    }

    return answer;
}

int main(void)
{
    int n;
    cin >> n;
    vector<vector<int>> macaron(n, vector<int>(2));
    for (int i = 0; i < n; i++)
    {
        cin >> macaron[i][0] >> macaron[i][1];
    }

    vector<string> v_s = solution(macaron);
    for (int i = 0; i < v_s.size(); i++)
    {
        cout << v_s[i] << '\n';
    }
    return 0;
}