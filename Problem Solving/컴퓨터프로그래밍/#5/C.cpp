
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int O=0;
    string Str; cin >> Str;
    for(int i=0; i<Str.size(); i++){
        if(Str[i]=='(') O++;
        else O--;
        if(O<0){ printf("NO\n"); return 0; } 
    }if(O) printf("NO\n");
    else printf("YES\n");
    return 0;
}
