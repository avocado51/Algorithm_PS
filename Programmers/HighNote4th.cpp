// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
using namespace std;

int answer = 0;
void dfs(int now ,int cnt) {
    if (now == 3){
        //*만 해주면 될 때 멈춘다. 
        
        return;
    }
    
}
int solution(int n) {
    //dfs를 하면서 n을 만들어나간다. 
    //set에 결과를 넣고 다르면 ok 
    //규칙에 맞는지도 확인을 해야한다. 
    dfs(n-2, 2); //마지막은 반드시 ++이므로 n-2부터 시작해도 된다. 
    
    return answer;
}