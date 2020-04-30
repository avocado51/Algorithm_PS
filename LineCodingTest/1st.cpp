#include <string>
#include <vector>

using namespace std;

int solution(string input) {
    int answer = -1;
    int c1 = 0, c2 = 0, c3= 0, c4=0;
    int cnt = 0;
    
    int n = input.size();
    for (int i = 0; i < n; i++) {
        switch(input[i]) {
            case '(':
                c1++;
                break;
            case ')':
                {
                    if (!c1) return -1;
                    c1--;
                    cnt++;
                    break;
                }
            case '{' :
                c2++;
                break;
            case '}':
                {
                    if (!c2) return -1;
                    c2--;
                    cnt++; //정상적인 괄호의 수를 증가시켜준다. 
                    break;
                }
            case '[' :
                c3++;
                break;
            case ']':
                {
                    if (!c3) return -1;
                    c3--;
                    cnt++; //정상적인 괄호의 수를 증가시켜준다. 
                    break;
                }
            case '<' :
                c4++;
                break;
            case '>':
                {
                    if (!c4) return -1;
                    c4--;
                    cnt++; //정상적인 괄호의 수를 증가시켜준다. 
                    break;
                }
        }
        
    }
    if (c1 || c2 || c3 || c4) return -1;//문자열을 모두 봤을 때 하나라도 남아있으면 제대로된 괄호가 아님 
    answer = cnt;
    
    return answer;
}