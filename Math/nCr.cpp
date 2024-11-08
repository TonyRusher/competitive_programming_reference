vll fact(200007,0), inv(200007,0), invfact(200007,0);
void factorial(){
	fact[0] = 1; inv[0] = inv[1] = 1; invfact[0] = 1;
	fore(i,1,200005) fact[i] = (fact[i-1] * i) % MOD;
	fore(i,2,200005) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;	
	fore(i,1,200005) invfact[i] = invfact[i-1] * inv[i] % MOD;
}
ll ncr(ll n, ll r){
	return fact[n] * invfact[n - r] % MOD * invfact[r] % MOD ;
}