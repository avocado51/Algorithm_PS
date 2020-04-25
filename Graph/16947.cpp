#include <iostream>
#include <vector>
#include <algorithm>

#include <queue>
#define MAXX 3001
using namespace std;
// BOJ 여행가자 https://www.acmicpc.net/problem/1976

int n;
bool flag = false;
vector<int> station[MAXX];
bool chk[MAXX];

int parent[MAXX];

int find(int a)
{
    if (parent[a] == -1)
        return a;
    return find(parent[a]);
}
void unionFind(int a, int b)
{
    int pa = find(a);
    int pb = find(b);

    if (pa == pb)
        return;

    parent[pa] = pb;
}
bool isSameParent(int a, int b)
{
    int pa = find(a);
    int pb = find(b);

    if (pa == pb)
        return true;
    return false;
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        parent[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        station[a].push_back(b);
        station[b].push_back(a);
    }

    for (int i = 1; i <= n; i++)
    {
        for (int next : station[i])
        {
            int pi = find(i);
            int pn = find(n);

            if (pn == pi)
            {
                chk[i] = true;
                chk[next] = true;
            }

            unionFind(pn, pi);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << chk[i] << '\n';
    }

    return 0;
}