#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define MAXX 4001
using namespace std;

typedef struct Atomic
{
    int x, y, d, e;
    bool alive;
} A;

vector<A> atoms;
typedef pair<int, A> ia;
int n, map[MAXX][MAXX], ans = 0; //총 합
int dy[4] = {1, -1, 0, 0}, dx[4] = {0, 0, -1, 1};

void print()
{
    for (A a : atoms)
    {
        if (!a.alive)
            continue;
    }
}
bool check()
{
    for (A a : atoms)
    {
        if (a.alive)
            return false;
    }
    return true;
}
bool checkRange(int x, int y)
{
    if (x < 0 || x >= MAXX || y < 0 || y >= MAXX)
        return false;
    return true;
}
int removeAtoms()
{
    int res = 0;
    for (int i = 0; i < atoms.size(); i++)
    {
        if (!atoms[i].alive)
        {
            //죽은 원자들
            continue;
        }

        int x = atoms[i].x;
        int y = atoms[i].y;
        if (map[y][x] >= 2)
        {
            //여러개의 원자가 있을 경우
            atoms[i].alive = false;
            res += atoms[i].e;
            for (int j = 0; j < atoms.size(); j++)
            {
                if (i == j)
                    continue;
                if (!atoms[j].alive)
                    continue;
                if (atoms[j].x == x && atoms[j].y == y)
                {
                    atoms[j].alive = false;
                    res += atoms[j].e;
                }
            }
            map[y][x] = 0;
        }
    }

    return res;
}
void moveAtoms()
{

    while (1)
    {

        int sum = 0;
        if (check())
        {
            //모두 죽으면 끝
            break;
        }
        for (int i = 0; i < atoms.size(); i++)
        {
            if (!atoms[i].alive)
                continue;

            int x = atoms[i].x;
            int y = atoms[i].y;
            int d = atoms[i].d;
            map[y][x] = 0;

            int nx = x + dx[d];
            int ny = y + dy[d];

            if (checkRange(nx, ny))
            {
                map[ny][nx]++;
                atoms[i].x = nx;
                atoms[i].y = ny;
            }
            else
            {
                atoms[i].alive = false;
                continue;
            }
        }

        sum = removeAtoms();
        // cout << "do after" << '\n';
        // print();
        ans += sum;
    }
}
// void moveAtoms()
// {
//     //더 이상 움직임이 없을 때까지 움직인다.
//     queue<ia> q;

//     for (int i = 0; i < atoms.size(); i++)
//     {
//         q.push(ia(i, atoms[i]));
//     }

//     bool flag = true;
//     while (!q.empty() && flag)
//     {
//         int size = q.size();
//         flag = false;
//         while (size--)
//         {
//             A now = q.front().second;
//             int idx = q.front().first;

//             q.pop();

//             if (!now.alive)
//                 continue;
//             //이미 죽은 원자

//             int x = now.x;
//             int y = now.y;
//             int d = now.d;
//             map[y][x] = 0;

//             int nx = x + dx[d];
//             int ny = y + dy[d];

//             if (checkRange(nx, ny))
//             {
//                 map[ny][nx]++;

//                 atoms[idx].x = nx;
//                 atoms[idx].y = ny;
//                 q.push(ia(idx, atoms[idx]));
//                 flag = true;
//             }
//         }
//         if (flag)
//             ans += removeAtoms();
//     }
// }
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        memset(map, 0, sizeof(map));
        cin >> n;
        atoms.clear();
        ans = 0;

        for (int i = 0; i < n; i++)
        {
            int x, y, d, e;
            cin >> x >> y >> d >> e;

            Atomic atom;
            int yy = (y + 1000) * 2;
            int xx = (x + 1000) * 2;

            atom.y = yy;
            atom.x = xx;
            atom.e = e;
            atom.d = d;
            atom.alive = true;
            atoms.push_back(atom);
            map[yy][xx] = 1;
        }

        moveAtoms();
        cout << "#" << tc << " " << ans << '\n';
    }

    return 0;
}