
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string S; cin >> S; 
    long long Ans=0, Temp=0; int Mode=1;
    for(int i=0; i<S.size(); i++){
        if(S[i]<='9' && S[i]>='0'){
            Temp*=10; Temp+=(S[i]-'0');
        }else{
            Ans += Mode*Temp; Temp=0;
            if(S[i]=='-') Mode=-1;
            else Mode=1;
        }
    }Ans += Mode*Temp;
    printf("%lld\n", Ans);
    return 0;
}
