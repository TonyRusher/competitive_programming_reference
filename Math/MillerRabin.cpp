typedef __int128 i128;
//powerModCode
bool singleTest( i128 a, i128 n ){//test a ^( (n - 1)/2^k )= 1 (mod n)
	i128 exp = n - 1;
	while (~exp & 1) exp >>= 1;// while exp is even
	if( powerMod(a, exp, n) == 1 ) return true; // a^exp = a^( (n - 1)/2^k ) = 1 (mod n)
	while ( exp < n - 1) {
		if( powerMod(a, exp, n) == n - 1 ) return true;
		exp <<= 1;
	}
	return false;
}

bool MillerRabin(lli n){
    if(n < 2) return false;
    if(n <= 3) return true;
    if( ~n & 1) return false;
    for(lli a: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
        if(n == a) return true;
		if(!singleTest(a, n)) return false;
    }
    return true; //Probability = 1 - (1/4)^size_of(vector_a)
}

bool MillerRabinOther(lli n){
    if(n < 2) return false;
    if(n <= 3) return true;
    if( ~n & 1) return false;
    lli d = n-1, s = 0; //n-1 = 2^s*k
    for(;(~d&1); d >>= 1, s++); //d = k
    for(lli a: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
        if(n == a) return true;
        i128 residuo = powerMod(a, d, n);
        if(residuo == 1 or residuo == n-1) continue;
        lli x = s;
        while(--x){
            residuo = (residuo * residuo) % n;
            if(residuo == n-1) break;
        }
        if(x==0) return false;
    }
    return true; //Probability = 1 - (1/4)^size_of(vector_a)
}