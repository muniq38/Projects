
#include <bits/stdc++.h>
using namespace std;

int main()
{
    stack<char> St, Ans;
    string S; cin >> S;
    for(int i=0; i<S.size(); i++){
        if(S[i]=='+' || S[i]=='-'){
            while(!St.empty()){
                printf("%c",St.top()); St.pop(); 
            }St.push(S[i]);
        }else if(S[i]=='*' || S[i]=='/'){
            while(!St.empty()){
                if(St.top()=='*' || St.top()=='/')
                { printf("%c",St.top()); St.pop(); }
                else break;
            }St.push(S[i]);
        }else printf("%c",S[i]);
    }while(!St.empty()){ printf("%c",St.top()); St.pop(); }
    return 0;
}
