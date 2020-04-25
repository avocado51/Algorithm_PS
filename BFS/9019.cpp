#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define MINN 0
#define MAXX 9999

using namespace std;

int a, b;
bool visited[MAXX + 1];
typedef pair<string, int> pp;

void bfs()
{
    queue<pp> q;
    q.push(pp("", a));
    visited[a] = true;
    int cnt = 0;
    while (!q.empty())
    {
        int size = q.size();
        while (size--)
        {
            int now = q.front().second;
            string dir = q.front().first;
            q.pop();

            if (now == b)
            {
                cout << dir << '\n';
                return;
            }

            for (int i = 0; i < 4; i++)
            {
                int next = now;
                if (i == 0)
                {
                    next *= 2;

                    if (next * 2 > MAXX)
                    {
                        next %= 10000;
                    }
                    if (visited[next])
                        continue;
                    q.push(pp(dir + "D", next));
                }
                else if (i == 1)
                {
                    next -= 1;

                    if (next < MINN)
                        next = MAXX;
                    if (visited[next])
                        continue;
                    q.push(pp(dir + "S", next));
                }
                else if (i == 2)
                {
                    //왼쪽 회전
                    string s;
                    s = to_string(now);
                    char tmp = s[0];
                    for (int i = 0; i < s.size() - 1; i++)
                    {
                        s[i] = s[i + 1];
                    }
                    s[s.size() - 1] = tmp;
                    if (visited[stoi(s)])
                        continue;
                    q.push(pp(dir + "L", stoi(s)));
                }
                else if (i == 3)
                {
                    //왼쪽 회전
                    string s;
                    s = to_string(now);
                    char tmp = s[s.size() - 1];
                    for (int i = s.size() - 1; i > 0; i--)
                    {
                        s[i] = s[i - 1];
                    }
                    s[0] = tmp;
                    if (visited[stoi(s)])
                        continue;
                    q.push(pp(dir + "R", stoi(s)));
                }
            }
        }
        ++cnt;
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--)
    {

        cin >> a >> b;
        //a-> b로 만들기
        memset(visited, 0, sizeof(visited));
        bfs();
    }
    return 0;
}