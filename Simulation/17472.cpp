#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
//BOJ 다리만들기2 [17472](https://www.acmicpc.net/problem/17472)

int n, m;
int map[11][11];
int visited[11][11];
int parent[7];
typedef pair<int, int> pp;

int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int res = 0;

typedef struct Q
{
    int len, x, y;
};
vector<Q> edge;
// dfs로 섬을 라벨링
// unionset으로 모든 섬이 연결되어있는지 확인
// 한 섬의 가장자리로 가서 다른 섬으로 이동하면서 길이를 비교해본다.

bool compare(const Q &a, const Q &b)
{
    return a.len < b.len;
}
int find(int a)
{
    int pa = parent[a];
    if (pa == a)
        return a;
    return parent[a] = find(parent[a]);
}
void unionSet(int a, int b)
{
    int pa = find(a);
    int pb = find(b);

    if (pa == pb)
        return;

    parent[pb] = pa;
}
bool sameSet(int a, int b)
{
    int pa = find(a);
    int pb = find(b);

    if (pa == pb)
        return true;
    return false;
}
// int djikstra(int start)
// {
//     priority_queue<pp, vector<pp>, greater<pp>> pq;

//     pq.push({0, start});
//     int res = 0;
//     while (!pq.empty())
//     {
//         int cost = pq.top().first;
//         int node = pq.top().second;
//         pq.pop();

//         if (chk2[node])
//             continue;
//         chk2[node] = true;
//         res += cost;
//         cout << node << " " << cost << '\n';

//         for (int i = 0; i < edge[node].size(); i++)
//         {
//             if (!chk2[edge[node][i].second])
//             {
//                 pq.push(pp(cost + edge[node][i].first, edge[node][i].second));
//             }
//         }
//     }
//     return res;
// }
bool checkRange(int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= m)
        return false;
    return true;
}
void dfs(int x, int y, int label)
{
    if (visited[x][y])
        return;
    visited[x][y] = label;

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (checkRange(nx, ny) && map[nx][ny])
        {
            dfs(nx, ny, label);
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
        }
    }

    int label = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!visited[i][j] && map[i][j])
            {
                ++label;
                dfs(i, j, label);
            }
        }
    }

    for (int i = 1; i <= label; i++)
        parent[i] = i;

    int res = 0;
    //섬의 가장자리를 찾아서 연결해준다.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j])
            {
                for (int k = 0; k < 4; k++)
                {
                    int nx = i + dx[k];
                    int ny = j + dy[k];

                    if (checkRange(nx, ny))
                    {
                        if (visited[nx][ny])
                            continue;
                        else
                        {
                            //쭉 간다.
                            int nnx = nx + dx[k];
                            int nny = ny + dy[k];

                            if (checkRange(nnx, nny))
                            {
                                if (!map[nnx][nny])
                                {
                                    int len = 2;
                                    bool flag = false;
                                    while (checkRange(nnx + dx[k], nny + dy[k]))
                                    {
                                        nnx += dx[k];
                                        nny += dy[k];

                                        if (!map[nnx][nny])
                                            len++;
                                        else if (visited[nnx][nny] != visited[i][j])
                                        {
                                            //다른 섬에 도착함

                                            flag = true;
                                            break;
                                        }
                                        else
                                        {
                                            break;
                                        }
                                    }
                                    if (flag)
                                    {
                                        int first = visited[i][j];
                                        int second = visited[nnx][nny];

                                        edge.push_back({len, first, second});
                                    }
                                    //두 개의 섬이 이미 연결되어있는지 확인하고, 연결이 되어있지 않으면 연결한다.
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int line = 0;
    sort(edge.begin(), edge.end(), compare);

    for (int i = 0; i < edge.size(); i++)
    {
        if (!sameSet(edge[i].x, edge[i].y))
        {
            res += edge[i].len;
            unionSet(edge[i].x, edge[i].y);
            line++;
        }
    }

    if (label - 1 != line)
    {
        res = -1;
    }
    else if (!res)
    {
        res = -1;
    }

    cout << res << '\n';
    return 0;
}