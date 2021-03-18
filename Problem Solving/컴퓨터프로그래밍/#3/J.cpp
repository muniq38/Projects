
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

lint Gcd(lint A, lint B){ // 항상 A>=B
    if(!(A%B)) return B;
    return Gcd(B,A%B);
}

int main()
{
    lint N, M; scanf("%lld %lld", &N, &M);
    printf("%lld\n", 3*(N-Gcd(N,M))); // Gcd(N,M) * 3 * (N/Gcd(N,M)-1)
    return 0;
}
