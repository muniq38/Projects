
#include <bits/stdc++.h>
using namespace std;
int Root[60]={};
string X, Y;

void f(int sx, int ex, int sy, int ey){
    if(sx>ex) return;
    for(int i=sx; i<=ex; i++){
        if(X[i]==Y[sy]){
            int shift = i-sx;
            f(sx, i-1, sy+1, sy+shift);
            f(i+1, ex, sy+shift+1, ey);
            break;
        }
    }printf("%c", Y[sy]);
}

int main()
{
    cin >> X >> Y;
    f(0,X.size()-1,0,Y.size()-1);
    return 0;
}
