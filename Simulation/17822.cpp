#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <cstring>

using namespace std;

//BOJ 원판돌리기 [17822](https://www.acmicpc.net/problem/17822)

int n, m, t;
vector<int> plate[51];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
typedef pair<int, int> pp;
bool visited[51][51];

void print()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (plate[i][j] < 0)
                cout << "x" << ' ';
            else
                cout << plate[i][j] << ' ';
        }
        cout << '\n';
    }
}
void calc()
{
    queue<pp> q;
    memset(visited, 0, sizeof(visited));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (plate[i][j] > 0)
                q.push(pp(i, j));
        }
    }

    while (!q.empty())
    {
        //바로 블락 처리하면 안됨 -> 그 부분과 연결된 부분을 확인할 수 없다.
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (y == 0 || y == m - 1)
        {
            //m-1 번째와도 확인을 해야한다.
            if (plate[x][0] == plate[x][m - 1])
            {
                visited[x][0] = true;
                visited[x][m - 1] = true;
            }
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx <= 0 || nx > n || ny < 0 || ny >= m)
                continue;
            if (plate[nx][ny] < 0)
                continue;
            if (plate[x][y] == plate[nx][ny])
            {
                visited[x][y] = true;
                visited[nx][ny] = true;
            }
        }
    }

    bool flag = false;
    int sum = 0, cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (visited[i][j])
            {
                plate[i][j] = -1;
                flag = true;
            }
            if (plate[i][j] > 0)
            {
                sum += plate[i][j];
                cnt++;
            }
        }
    }
    if (!flag)
    {
        double avg = (double)((double)sum / (double)cnt);
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j < m; j++)
            {

                if (plate[i][j] > 0)
                {
                    if (plate[i][j] > avg)
                        plate[i][j]--;
                    else if (plate[i][j] < avg)
                        plate[i][j]++;
                }
            }
        }
    }
}
void rotate(int x, int d, int k)
{
    deque<int> dq;
    for (int i = x; i <= n; i++)
    {
        if (i % x == 0)
        {
            //돌릴 원판
            int cnt = k;
            vector<int> v;
            // cout << "before\n";
            for (int j = 0; j < m; j++)
            {
                // cout << plate[i][j] << ' ';
                dq.push_back(plate[i][j]);
            }
            // cout << '\n';
            while (cnt--)
            {
                dq.push_front(dq.back());
                dq.pop_back();
            }
            // cout << "after\n";
            for (int j = 0; j < m; j++)
            {
                // cout << dq.front() << ' ';
                v.push_back(dq.front());
                dq.pop_front();
            }
            plate[i] = v;
            // cout << '\n';
        }
    }
    //모두 돌렸으면 계산
    calc();
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> t;

    int tmp = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> tmp;
            plate[i].push_back(tmp);
        }
    }

    int x, d, k;
    for (int i = 1; i <= t; i++)
    {
        cin >> x >> d >> k;
        //d가 0이면 시계, 1이면 반시계
        if (d == 0)
            rotate(x, d, k);
        else
            rotate(x, d, m - k);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (plate[i][j] > 0)
            {
                ans += plate[i][j];
            }
        }
    }
    cout << ans << '\n';
    return 0;
}