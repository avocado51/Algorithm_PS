#include <iostream>
#include <vector>

using namespace std;
//BOJ https://www.acmicpc.net/problem/2980
//unsolved

typedef pair<int, int> pp;

vector<pp> line[1001];
bool chk[1001];
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, l;
    cin >> n >> l;
    for (int i = 0; i < n; i++)
    {
        int x, r, g;
        cin >> x >> r >> g;
        line[x].push_back(pp(r, g));
        //미리 라인에 신호등 루틴을 구해놓는다.
    }

    //처음에는 모두 빨간색이다.

    int time = 0;
    for (int i = 1; i <= l;)
    {
        if (line[i].size() > 0)
        {
            //신호등이 존재
            //빨간색에 걸리는 시간이면 기다리고
            //초록색에 걸리는 시간이면 지나간다.
        }

        time++; //1초에 1미터 이동
        i++;
    }
    cout << time << '\n';
    return 0;
}