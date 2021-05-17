
#include <bits/stdc++.h>
using namespace std;

int main(){
	int T; scanf("%d", &T);
	while(T--){
		int N, M, k, D;
		scanf("%d %d %d %d", &N, &M, &k, &D);
		int S = N*M*(k*(M-1)+M*(N-1))/2;
		if(S>D) printf("-1\n");
		else printf("%d\n", (D/S)*S);
	}
}
