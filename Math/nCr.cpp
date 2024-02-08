vll fact(100007,0), inv(100007,0), invfact(100007,0);
void factorial(){
	fact[0] = 1; inv[0] = inv[1] = 1; invfact[0] = 1;
	fore(i,1,100005) fact[i] = (fact[i-1] * i) % MOD;
	fore(i,2,100005) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;	
	fore(i,1,100005) invfact[i] = invfact[i-1] * inv[i] % MOD;
}
ll ncr(ll n, ll r){
	return fact[n] * invfact[n - r] % MOD * invfact[r] % MOD ;
}