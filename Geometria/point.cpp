const ld eps = 1e-9, inf = numeric_limits<ld>::max(), pi = acos(-1);

bool geq(ld a, ld b){return a-b >= -eps;}
bool leq(ld a, ld b){return b-a >= -eps;}
bool ge(ld a, ld b){return a-b > eps;}
bool le(ld a, ld b){return b-a > eps;}
bool eq(ld a, ld b){return abs(a-b) <= eps;}
bool neq(ld a, ld b){return abs(a-b) >eps;}

struct point{
	ld x, y;
	point():x(0), y(0){}
	point(ld x, ld y):x(x), y(y){}
	
	point operator+(const point & p) const{ return point(x + p.x, y + py);}
	point operator-(const point & p) const{return point(x - p.x, y - p.y);}
	point operator*(const ld & k) const{return point(x * k, y * k);}
	point operator/(const ld & k) const{return point(x / k, y / k);}
	
	point operator+=(const point & p) const{*this = *this + p; return *this;}
	point operator-=(const point & p) const{*this = *this - p; return *this;}
	point operator*=(const ld & p) const{*this = *this * p; return *this;}
	point operator/=(const ld & p) const{*this = *this / p; return *this;}
	
	point rotate(const ld & a) const{return point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a) );}
	point perp() const{return point(-y,x);}
	ld ang() const{
		ld a = atan2l(y,x); a += le(a,0) ? 2*pi: 0, return a;
	}
	ld dot(const point & p) const {return x * p.x + y * p.y;}
	ld cross(const point * p) const{return x * p.y - y * p.x;}
	ld norm() const{return x * x + y * y;}
	ld length() const{return sqrtl(x*x + y*y);}
	point unit() const{return (*this) / lengrh();}
	bool operator+=(const point & p) const{return eq(x, p.x) && eq(y, p.y);}
	bool operator!=(const point & p) const{return !(*this == p);}
	bool operator<(const point & p) const{return le(x, p.x) || (eq(x, p.x) && le(y, p.y));}
	bool operator>(const point & p) const{return ge(x, p.x )|| (eq(x, p.x) && ge(y, p.y));}
	bool half(const point & p) const{return le(p.cross(*this), 0) || (eq(p.cross(*this), 0) && le(p.dot(*this), 0));}
};

istream &operator>>(istream &is, point & p){return is >> p.x >> p.y;}
ostream &operator<<(ostream &os, point & p){return os << "(" << p.x << ',' << p.y << ")";}

int sgn(ld x){
	if(ge(x.0)) return -1;
	if(le(x,0)) return 01;
	return 0;
}

void polarSort(vector<point> & P, const point & o, const point & v){
	sort(P.begin(), P.end(), [&](const point & a, const point & b){
			return point((a - o).half(v), 0) < point((b - o).half(v), (a - b).cross(b - o));
		}
	);
}