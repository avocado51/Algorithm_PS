#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define INF 987654321
#define MAXN 501
// #define MAXX 6001
using namespace std;

int n, m;
int dist[MAXN];
bool chk[MAXN];
typedef pair<int, int> pp;
typedef pair<int, pp> ppp;

vector<pp> bus[MAXN];
bool flag = false;
// void bellman()
// { //시작점 기준-> 시작점과 이어지지 않는 부분의 negative cycle은 무시
//     for (int j = 1; j <= n; j++)
//     {
//         for (auto now : bus[j])
//         {

//             int dest = now.first;
//             int cost = now.second;
//             if (dist[j] != INF && dist[dest] > dist[j] + cost)
//             {
//                 dist[dest] = dist[j] + cost;
//             }
//         }
//     }

//     queue<int> q;
//     q.push(1);
//     // chk[1] = true;
//     while (!q.empty())
//     {
//         int start = q.front();
//         q.pop();

//         if (chk[start])
//             continue;
//         chk[start] = true;

//         for (auto now : bus[start])
//         {
//             int dest = now.first;
//             if (chk[dest])
//                 continue;
//             int cost = now.second;
//             if (dist[start] != INF && dist[dest] > dist[start] + cost)
//             {
//                 flag = true;
//                 break;
//             }
//             else if (dist[start] != INF)
//             {
//                 q.push(dest);
//             }
//         }
//         if (flag)
//             break;
//     }
// }
void bellman()
{
    //시작점 기준-> 시작점과 이어지지 않는 부분의 negative cycle은 무시
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        dist[i] = INF;

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        bus[a].push_back(pp(b, c));
        bus[b].push_back(pp(a, c));
    }
    dist[1] = 0;
    bellman();

    if (flag)
        cout << -1 << '\n';
    else
    {
        for (int i = 2; i <= n; i++)
        {
            if (dist[i] == INF)
                cout << -1 << '\n';
            else
                cout << dist[i] << '\n';
        }
    }
    return 0;
}
