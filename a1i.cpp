#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

#define ll long long
#define ld long double
#define FOR(i, s, f) for(ll (i) = (s); (i) < (f); (i)++)

random_device rd;
mt19937 eng(rd());
uniform_real_distribution<double> distr_double(0, 1);

ld genD(){return distr_double(eng);}

struct Circle{
    ld x, y, r;
    Circle() = default;
    Circle(ld x, ld y, ld r): x(x), y(y), r(r){}
    friend istream& operator>>(istream& in, Circle &A);
    bool is_inside(ld px, ld py){
        return ((x - px) * (x - px) + (y - py) * (y - py)) <= r * r;
    }
};
istream& operator>>(istream &in, Circle &A){
    in >> A.x >> A.y >> A.r;
    return in;
}

void solve(){
    Circle A, B, C;
    cin >> A >> B >> C;
    ld maxr = max(A.r, max(B.r, C.r));
    ll cntin = 0, cnttest = 10000000;
    FOR(i, 0, cnttest){
        ld genx = genD() * (2 * maxr + 1) - maxr, geny = genD() * (2 * maxr + 1) - maxr;
        if (A.is_inside(genx, geny) && B.is_inside(genx, geny) && C.is_inside(genx, geny)) cntin++;
    }
    cout << (2 * maxr + 1) * (2 * maxr + 1) * cntin / cnttest;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.precision(64);
    solve();
    return 0;
}
