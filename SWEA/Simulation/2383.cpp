#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

#define INF 987654321
using namespace std;

int n;
int map[11][11];
bool chk[11];

typedef struct Person
{
    int idx, wait, dist, time;
    Person(){};

    Person(int i, int t, int d, int w) : idx(i), time(t), dist(d), wait(w){};
} P;

typedef struct Stair
{
    int x, y, l;
} S;

S st[2];
typedef pair<int, int> pp;
vector<pp> person;

int ans = INF;

void print()
{
    for (int i = 0; i < person.size(); i++)
    {
        cout << chk[i] << ' ';
    }
    cout << '\n';
}
bool operator<(P a, P b)
{
    if (a.time == b.time)
        return a.dist > b.dist;
    return a.time > b.time;
}
int abs(const int &a, const int &b)
{
    if (a > b)
        return a - b;
    else
        return b - a;
}
int min(const int &a, const int &b)
{
    if (a > b)
        return b;
    return a;
}
void descendingStair(priority_queue<P> q)
{
    int time = 0;               //걸린 시간
    int inStairCnt[2] = {0, 0}; //3명 초과하면 안됨

    while (!q.empty())
    {
        P now = q.top();
        q.pop();

        time = now.time;
        if (now.dist >= time)
        {
            //1. dist가 적은 순?  -> 정렬이 조건 필요
            q.push(Person(now.idx, now.time + 1, now.dist, now.wait));
            continue; //아직 계단에 다다르지 못함
        }
        if (now.wait)
        {
            //계단 내려가는 중
            if (now.wait == st[now.idx].l)
            {
                //계단 끝에 다다름-> 얘를 제외한 상태로 진행
                inStairCnt[now.idx]--;
                continue;
            }

            q.push(Person(now.idx, now.time + 1, now.dist, now.wait + 1));
            continue;
        }
        if (inStairCnt[now.idx] == 3)
        {
            //조금더 기다림
            q.push(Person(now.idx, now.time + 1, now.dist, now.wait));
        }
        else
        {
            inStairCnt[now.idx]++;
            q.push(Person(now.idx, now.time + 1, now.dist, now.wait + 1));
        }
    }

    ans = min(ans, time);
}
void moveToStair()
{
    priority_queue<P> stair;
    for (int i = 0; i < person.size(); i++)
    {
        if (chk[i])
        {
            int dist = abs(st[0].x, person[i].first) + abs(st[0].y, person[i].second);

            stair.push(Person(0, 0, dist, 0));
        }
        else
        {
            int dist = abs(st[1].x, person[i].first) + abs(st[1].y, person[i].second);

            stair.push(Person(1, 0, dist, 0));
        }
    }
    descendingStair(stair);
}

void dfs(int idx, int cnt)
{
    if (cnt == person.size())
    {
        //사람을 다 나눴으면

        moveToStair();
        return;
    }
    else
    {
        chk[idx] = true;
        dfs(idx + 1, cnt + 1);
        chk[idx] = false;
        dfs(idx + 1, cnt + 1);
    }
    // for (int i = idx; i < person.size(); i++)
    // {
    //     if (!chk[i])
    //     {
    //         chk[i] = true;
    //         dfs(i + 1, cnt + 1);
    //         chk[i] = false;
    //     }
    // }
}
void init()
{
    memset(chk, 0, sizeof(chk));
    ans = INF;
    person.clear();
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; ++tc)
    {

        init();
        cin >> n;

        int sidx = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> map[i][j];

                if (2 <= map[i][j] && map[i][j] <= 10)
                {
                    //계단
                    S tst;
                    tst.x = i;
                    tst.y = j;
                    tst.l = map[i][j];
                    st[sidx++] = tst;
                }
                else if (map[i][j] == 1)
                {
                    person.push_back(pp(i, j));
                }
            }
        }

        dfs(0, 0); //조합을 구한다.

        cout << "#" << tc << " " << ans << '\n';
    }

    return 0;
}