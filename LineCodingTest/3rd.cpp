//라인테스트 3 -> 투포인터
#include <string>
#include <vector>
#include <queue>
using namespace std;
int max (const int &a, const int &b) {
    if (a >b) return a;
    return b;
}
int solution(string road, int n) {
    int answer = -1;
    int sum = 0; //원래 주어진 연속된 1의 개수 
    int cnt = 0;//최종 연결된 길의 개수 
    
    queue<int> q;
    //큐의 최대 개수는 n
    for (int i = 0; i < road.size(); i++) {
        if (road[i] == '1') {
            sum++;
            cnt++;
        }
        else {
            if (q.size() < n) {
                //N개 이상 보수하지 않았을 경우에는 큐에 넣을 수 있다. 
                q.push(sum); //지금까지 연속된 1의 개수를 넣는다.
                //만약 나중에 더 좋은 보수될 곳을 만나서 0으로 바꾸게 되면 그 앞에 있는 것들까지 모두 못 쓰는 도로이기 때문에
            }
            else {
                int tmp = q.front();
                q.pop();
                q.push(sum);
                cnt -= tmp+1; //앞에 있는 도로는 못 쓰는 도로 
            }
            cnt++;
            sum = 0;
        }
        answer = max(answer, cnt);
    }
    
    return answer;
}