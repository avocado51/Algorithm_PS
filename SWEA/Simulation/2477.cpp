#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
//차량정비소 https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV6c6bgaIuoDFAXy

int n, m, k, a, b, ans = 0;
int A[10], B[10], T[1001];
typedef struct User
{
    int idx, rec, rep, time, wait;
    bool chk;
    User(int i, int rc, int rp, int t, int w, bool c) : idx(i), rec(rc), rep(rp), time(t), wait(w), chk(c){};
} User;
bool chkA[10], chkB[10], finished[1001];
vector<User> waitA, waitB;
queue<User> aq, bq;

bool compare(const User &a, const User &b)
{
    if (a.wait == b.wait)
    {
        return a.rec < b.rec;
    }
    return a.wait > b.wait;
}
bool check()
{
    for (int i = 1; i <= k; i++)
    {
        if (!finished[i])
            return false;
    }
    return true;
}
void inputWaitingB()
{
    //정비 큐 만들기
    //wait의 값이 같다면 접수 창구의 번호가 작은 순으로 정렬하낟.

    if (waitB.size() > 0)
    {
        sort(waitB.begin(), waitB.end(), compare);
        //이전에 대기하던 사람이 있었다면
        for (int j = 1; j <= m; j++)
        {
            //정비 창구에 남는 곳이 있는지 확인한다.
            if (!chkB[j])
            {
                chkB[j] = true;
                if (waitB[0].rec == a && j == b)
                {
                    ans += waitB[0].idx;
                }
                bq.push(User(waitB[0].idx, waitB[0].rec, j, waitB[0].time + 1, waitB[0].wait, waitB[0].chk));
                waitB.erase(waitB.begin());
                if (!waitB.size())
                    break;
            }
        }

        if (waitB.size() > 0)
        {
            //wiat를 하나씩 늘려준다.
            for (int j = 0; j < waitB.size(); j++)
            {
                waitB[j].wait += 1;
            }
        }
    }
}
void inputWaitingA(int hour)
{
    // cout << hour << " " << waitA.size() << '\n';
    if (waitA.size() > 0)
    {
        //이미 대기중인 사람들을 먼저 넣는다.
        for (int j = 1; j <= n; j++)
        {
            if (!chkA[j])
            {
                //비어있는 접수대
                chkA[j] = true;
                aq.push(User(waitA[0].idx, j, 0, 1, 0, true));
                waitA.erase(waitA.begin());
                if (!waitA.size())
                    break;
            }
        }
    }
    for (int i = 1; i <= k; i++)
    {

        if (T[i] == hour)
        {
            bool chk = false;
            for (int j = 1; j <= n; j++)
            {
                if (!chkA[j])
                {
                    chkA[j] = true;
                    aq.push(User(i, j, 0, 1, 0, true));
                    chk = true;
                    break;
                }
            }
            if (!chk)
                waitA.push_back(User(i, 0, 0, 0, 0, false));
        }
    }
}
void bfs()
{
    /*
    접수 창구의 우선순위는 아래와 같다.

   ① 여러 고객이 기다리고 있는 경우 고객번호가 낮은 순서대로 우선 접수한다.
   ② 빈 창구가 여러 곳인 경우 접수 창구번호가 작은 곳으로 간다.


정비 창구의 우선순위는 아래와 같다.

   ① 먼저 기다리는 고객이 우선한다.
   ② 두 명 이상의 고객들이 접수 창구에서 동시에 접수를 완료하고 정비 창구로 이동한 경우, 이용했던 접수 창구번호가 작은 고객이 우선한다.
   ③ 빈 창구가 여러 곳인 경우 정비 창구번호가 작은 곳으로 간다.

    */
    int hour = 0;
    while (1)
    {
        if (check())
        {
            //모두 다 할 일을 끝냈는지 확인한다.
            break;
        }

        inputWaitingA(hour);
        //접수 진행
        ++hour;
        int size = aq.size();

        while (size--)
        {
            //접수 진행
            //접수가 다 끝나면 바로 waiting에 넣어버린다.
            User now = aq.front();
            aq.pop();

            // cout << now.idx << " " << now.rec << " " << now.time << "\n";
            if (now.time == A[now.rec])
            {
                //끝마쳤음
                chkA[now.rec] = false;
                waitB.push_back(now);
            }
            else
            {
                aq.push(User(now.idx, now.rec, now.rep, now.time + 1, now.wait, now.chk));
            }
        }

        inputWaitingB();

        size = bq.size();
        while (size--)
        {
            //정비 진행
            User now = bq.front();
            bq.pop();

            if (now.time == A[now.rec] + B[now.rep])
            {
                chkB[now.rep] = false;
                finished[now.idx] = true;
            }
            else
            {
                bq.push(User(now.idx, now.rec, now.rep, now.time + 1, now.wait, now.chk));
            }
        }
    }
}
void init()
{
    memset(finished, 0, sizeof(finished));
    memset(chkA, 0, sizeof(chkA));
    memset(chkB, 0, sizeof(chkB));
    waitB.clear();
    waitA.clear();
    ans = 0;
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        init();
        cin >> n >> m >> k >> a >> b;

        for (int i = 1; i <= n; i++)
        {
            cin >> A[i];
        }
        for (int i = 1; i <= m; i++)
        {
            cin >> B[i];
        }
        for (int i = 1; i <= k; i++)
        {
            cin >> T[i];
        }

        bfs();
        if (!ans)
            ans = -1;

        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}