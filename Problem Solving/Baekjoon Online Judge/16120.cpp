
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string S; cin >> S; int PCount=0; 
    for(int i=0; i<S.size(); i++){
        if(S[i]=='P') PCount++;
        else if(PCount<2){ printf("NP"); return 0; }
        else if(i==S.size()-1 || S[i+1]=='A'){ printf("NP"); return 0; }
        else PCount -= 2;
    }if(PCount!=1){ printf("NP"); return 0; }
    printf("PPAP");
    return 0;
}

