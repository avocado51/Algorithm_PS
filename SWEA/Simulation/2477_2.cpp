#include <iostream>
#include <vector>
#include <queue>

using namespace std;
//차량정비소 https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV6c6bgaIuoDFAXy

int n, m, k, a, b;
int A[10], B[10], T[1001];
typedef struct User
{
    int idx, rec, rep, time, wait;
    bool chk;
    User(int i, int rc, int rp, int t, int w, bool c) : idx(i), rec(rc), rep(rp), time(t), wait(w), chk(c){};
};
bool chkA[10], chkB[10];
vector<User> waitA, waitB;
queue<User> aq, bq;

void inputWaitingB() {
    //정비 큐 만들기 

    
}
void inputWaitingA(int hour)
{
    if (waitA.size() > 0)
    {
        //이미 대기중인 사람들을 먼저 넣는다.
        for (int j = 1; j <= n; j++)
        {
            if (!chkA[j])
            {
                //비어있는 접수대
                chkA[j] = true;
                aq.push(User(waitA[0].idx, j, 0, 0, 0, true));
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
                    aq.push(User(i, j, 0, 0, 0, true));
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
        inputWaitingA(hour);
        //접수 진행
        int size = aq.size();

        while(size--) {
            //접수 진행 
        }

        inputWaitingB();

        size = bq.size();
        while(size--) {
            //정비 진행 
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

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
    return 0;
}