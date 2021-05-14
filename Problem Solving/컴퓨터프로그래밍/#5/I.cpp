
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
stack<char> sym;
stack<lint> num;

lint Res(lint a, lint b, char s){
    if(s=='*') return a*b;
    if(s=='/') return a/b;
    if(s=='+') return a+b;
    if(s=='-') return a-b;
}

void Work(){
    lint b = num.top(); num.pop();
    lint a = num.top(); num.pop();
    char s = sym.top(); sym.pop();
    num.push(Res(a,b,s));
}

int main()
{
    string str; cin >> str;
    lint temp=0;
    for(int i=0; i<str.size(); i++){
        if('0'<=str[i] && str[i]<='9'){ temp *= 10; temp += str[i]-'0'; }
        else{
            if('0'<=str[i-1] && str[i-1]<='9'){ num.push(temp); temp=0; }
            if(str[i]=='(') sym.push(str[i]);
            else if(str[i]=='*'||str[i]=='/') 
                while(!sym.empty() && (sym.top()=='*' || sym.top()=='/')) Work();
            else while(!sym.empty() && sym.top()!='(') Work();
            if(str[i]==')') sym.pop(); 
            else if(str[i]!='(') sym.push(str[i]);
        }
    }if('0'<=str[str.size()-1] && str[str.size()-1]<='9') num.push(temp);
    while(!sym.empty()) Work();
    printf("%lld\n", num.top());
    return 0;
}
