int sq = 5;
// const lli sqrt5 = 383008016;//mod1e9+9
const ll mod = 1000000007;//is important to be CONST
struct EX {
	ll re, im;
	EX (ll re = 0, ll im = 0) : re(re), im(im){}
	
	EX& operator = (EX oth) {
		return re = oth.re, im = oth.im, *this; 
	}
	int norm () const { 
		return trim((1ll * re * re - 1ll * sq * im % mod * im) % mod);
	}
	EX conj () const { 
		return {re, trim(-im)}; 
	} 
	EX operator * (EX ot) const {
		return {
			int((1ll * re * ot.re + 1ll * sq * im % mod * ot.im) % mod),
			int((1ll * re * ot.im + 1ll * im * ot.re) % mod)
		};
	};
	EX& operator *= (const EX& ot) {
		*this = *this * ot; return *this;
	}
	EX operator * (ll k) const {
		k = ((k % mod) + mod ) % mod;
		return { (re * k) % mod, (im * k) % mod };
	};
	EX operator / (ll n) const { 
		return { re * inv(n) % mod, im * inv(n) % mod };
	}
	EX operator / (EX ot) const {
		return *this * ot.conj() / ot.norm();
	}
	EX& operator /= (const EX& ot) {
		*this = *this / ot; return *this;
	}
	EX operator + (EX ot) const {
		return { trim(re + ot.re),  trim(im + ot.im) };
	}
	EX& operator += (const EX& ot) {
		*this = *this + ot; return *this;
	}
	EX operator - (EX ot) const {
		return { trim(re - ot.re),  trim(im - ot.im) };
	}
	EX& operator -= (const EX& ot) {
		*this = *this - ot; return *this;
	}
	EX pow (ll p) const {
		EX res(1), b = *this;
		while (p) {
			if (p & 1) res *= b; b *= b; p /= 2;
		}
		return res;
	}
	
	bool operator == (EX ot) const {
		return re == ot.re && im == ot.im; 
	}
	bool operator != (EX ot) const {
		return !(*this == ot);
	}
	
	static ll trim(ll a) {
		if (a >= mod) a -= mod;
		if (a < 0) a += mod;
		return a;
	}
	static ll inv (ll b) {
		ll res = 1, p = mod - 2;
		while (p) {
			if (p & 1) res = 1ll * res * b % mod;
			b = 1ll * b * b % mod;
			p /= 2;
		}
		return res;
	};
};