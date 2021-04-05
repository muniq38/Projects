
#include <bits/stdc++.h>
using namespace std;

long long parse(string s){
    int idx=0; stack<char> St;
    long long Ans=0;
    if(s.size()==0) return 1;
    for(int i=0; i<s.size(); i++){
        if(s[i]==')'){
            St.pop();
            if(St.empty()){ Ans += 2*parse(s.substr(idx+1,i-idx-1)); idx=i+1; }
        }else if(s[i]==']'){
            St.pop();
            if(St.empty()){ Ans += 3*parse(s.substr(idx+1,i-idx-1)); idx=i+1; }
        }else St.push(s[i]);
    }return Ans;
}

int main()
{
    string s; cin >> s;
    int a=0, b=0;
    stack<char> St;
    for(int i=0; i<s.size(); i++){
        if(s[i]==')' && (St.empty() || St.top()!='(')){ printf("0\n"); return 0; }
        if(s[i]==']' && (St.empty() || St.top()!='[')){ printf("0\n"); return 0; }
        if(s[i]==')' || s[i]==']') St.pop();
        else St.push(s[i]);
    }printf("%lld\n", parse(s));
    return 0;
}

