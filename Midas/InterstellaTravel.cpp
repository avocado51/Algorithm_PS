
#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#define INF 987654321
using namespace std;

int n;
vector<int> connect[27];
int dist[27];
bool visited[27];
int candidate;
int parent[27];
int ans = 0;
typedef pair<int, int> pp;
int find(int a)
{
    int pa = parent[a];
    if (pa == a)
        return a;
    return parent[pa] = find(pa);
}
void union_find(int a, int b)
{
    int pa = find(a);
    int pb = find(b);

    if (pa == pb)
        return;
    parent[pb] = pa;
}
bool isSameSet(int a, int b)
{
    int pa = find(a);
    int pb = find(b);

    if (pa == pb)
        return true;
    return false;
}
void bfs()
{
    priority_queue<pp, vector<pp>, greater<pp>> q;
    q.push(pp(0, 0));

    while (!q.empty())
    {
        int now = q.top().second;
        int cnt = q.top().first;
        q.pop();

        if (now == 25)
            ans = cnt;
        if (visited[now])
            continue;
        visited[now] = true;

        for (int next : connect[now])
        {
            if (!visited[next])
            {
                if (dist[next] > cnt + 1)
                {
                    dist[next] = cnt + 1;
                    q.push(pp(dist[next], next));
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
    for (int i = 0; i < 27; i++)
    {
        dist[i] = INF;
        parent[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        string input;
        cin >> input;
        int a = input[0] - 'A';
        int b = input[2] - 'A';

        union_find(a, b);
        connect[a].push_back(b); //단방향 연결
    }
    char can;
    cin >> can;
    candidate = can - 'A';

    if (!isSameSet('A' - 'A', 'Z' - 'A') || !isSameSet('A' - 'A', candidate))
        cout << -1 << '\n';
    else
    {
        dist[0] = 0;
        bfs();
        for (int i = 0; i < 27; i++)
            cout << dist[i] << '\n';
        cout << ans << '\n';
    }

    return 0;
}