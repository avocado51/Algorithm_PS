#include <vector>
#include <map>
#include <iostream>

using namespace std;
map <long , long> m;

long long find(long long key){

    if(!m[key]) return key;
    return m[key] = find(m[key]); //일종의 압축과정

}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;

    for(int i = 0; i < room_number.size(); i++){

        long long cur = room_number[i];
        if(!m[cur]){
            answer.push_back(cur);
            m[cur] = find(cur + 1);
        }else{
            long long temp = find(cur);
            answer.push_back(temp);
            m[temp] = find(temp + 1);
        }
    }
    for(int i = 0; i < answer.size(); i++)
        cout<<answer[i]<<endl;
    return answer;
}

int main(){
    solution(10, {1,3,4,1,3,1});
}