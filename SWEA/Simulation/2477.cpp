#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <deque>
using namespace std;
int A[10], B[10], T[1001];
int n, m, k, a, b;
int chkA[10], chkB[10];
bool chk[1001];
int ans = 0;

typedef struct User
{
    int idx, rec, rep, time, wait;
    User(int i, int rc, int rp, int t, int w) : idx(i), rec(rc), rep(rp), time(t), wait(w){};
};

bool compare(const User &a, const User &b)
{
    if (a.wait == b.wait)
    {
        return a.rec > b.rec;
    }
    else
        return a.wait < b.wait;
}

void bfs()
{
    queue<User> recq, repq;
    vector<User> waitingRec, waitingRep;

    bool flag = true;
    int sec = 0;
    while (flag)
    {
        flag = false;

        for (int i = 1; i <= k; i++)
        {
            if (!chk[i] && T[i] <= sec)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (!chkA[j])
                    {
                        chkA[j] = i;
                        chk[i] = 1;
                        recq.push(User(i, j, 0, 1, 0));
                        break;
                    }
                }
                if (!chk[i])
                {
                    //대기큐에 넣는다.
                    waitingRec.push_back(User(i, 0, 0, 0, 0));
                }
            }
        }
        ++sec;

        int size = recq.size();

        while (size--)
        {
            //사이즈 별로 하면 들어온 순서대로 처리된다.
            User now = recq.front();
            recq.pop();

            int idx = now.idx;
            int rec = now.rec;
            int rep = now.rep;
            int time = now.time;
            int wait = now.wait;

            //접수 창고 끝
            if (time >= A[rec])
            {
                if (chkA[rec] == idx)
                    chkA[rec] = 0;

                //빈 정비 창구가 없다.
                waitingRep.push_back(User(idx, rec, 0, time, wait + 1));
            }
            else
            {
                //아직 접수 창고 안끝남
                recq.push(User(idx, rec, 0, time + 1, wait));
                flag = true;
            }
        }
        //waiting을 정렬하고 빈 곳이 있으면 넣는다.
        if (waitingRep.size() > 0)
        {
            sort(waitingRep.begin(), waitingRep.end(), compare);

            // cout << "DEBBBBB" << '\n';
            // for (int i = 0; i < waiting.size(); i++)
            // {
            //     cout << waiting[i].wait << " " << waiting[i].idx << '\n';
            // }
            for (int i = 1; i <= m; i++)
            {
                if (!chkB[i] && waitingRep.size() > 0)
                {
                    User now = waitingRep.back();

                    chkB[i] = now.idx;
                    if (now.rec == a && i == b)
                    {
                        cout << now.idx << '\n';
                        ans += now.idx;
                    }
                    repq.push(User(now.idx, now.rec, i, now.time + 1, now.wait));
                    waitingRep.pop_back();
                }
            }
            if (waitingRep.size() > 0)
            {
                for (int i = 0; i < waitingRep.size(); i++)
                {
                    waitingRep[i].wait += 1;
                }
                flag = true;
            }
        }

        size = repq.size();

        while (size--)
        {
            User now = repq.front();
            repq.pop();

            int idx = now.idx;
            int rec = now.rec;
            int rep = now.rep;
            int time = now.time;
            int wait = now.wait;

            if (time >= A[rec] + B[rep])
            {
                //끝났음
                if (chkB[rep] == idx)
                    chkB[rep] = 0;
            }
            else
            {
                repq.push(User(idx, rec, rep, time + 1, wait));
                flag = true;
            }
        }
    }
}
void init()
{
    memset(chk, 0, sizeof(chk));
    memset(chkA, 0, sizeof(chkA));
    memset(chkB, 0, sizeof(chkB));
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
        //접수 창고의 개수, 장비 창구의 개수, 고객의 수, 지갑고객이 이용한 접수 창고의 번호, 정비 창구의 번호

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

        //우선순위큐를 써서 접수 창고에서 빼낸 고객은 정비 창구 큐에 넣는다.
        bfs();
        if (!ans)
            ans = -1;

        cout << "#" << tc << " " << ans << '\n';
    }

    return 0;
}