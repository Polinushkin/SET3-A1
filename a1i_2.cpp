#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

using namespace std;

#define ll long long
#define ld long double
#define FOR(i, s, f) for(ll (i) = (s); (i) < (f); (i)++)

random_device rd;
mt19937 eng(rd());

struct Circle{
    ld x, y, r;
    Circle() = default;
    Circle(ld x, ld y, ld r): x(x), y(y), r(r){}
    bool is_inside(ld px, ld py){
        return ((x - px) * (x - px) + (y - py) * (y - py)) <= r * r;
    }
};

void areaMonteCarlo(const vector<Circle>& circles, bool method, int startN, int endN, int stepN) {
    ld sqrt5_half = sqrt(5.0L) / 2.0L;
    Circle A(1.0L, 1.0L, 1.0L);
    Circle B(1.5L, 2.0L, sqrt5_half);
    Circle C(2.0L, 1.5L, sqrt5_half);
    ld x_min, x_max, y_min, y_max;

    if (method) { // Способ 1
        x_min = min({A.x - A.r, B.x - B.r, C.x - C.r});
        x_max = max({A.x + A.r, B.x + B.r, C.x + C.r});
        y_min = min({A.y - A.r, B.y - B.r, C.y - C.r});
        y_max = max({A.y + A.r, B.y + B.r, C.y + C.r});
        cout << "# Method 1\n";
    } else { // Способ 2
        x_min = max({A.x - A.r, B.x - B.r, C.x - C.r});
        x_max = min({A.x + A.r, B.x + B.r, C.x + C.r});
        y_min = max({A.y - A.r, B.y - B.r, C.y - C.r});
        y_max = min({A.y + A.r, B.y + B.r, C.y + C.r});
        if (x_min >= x_max || y_min >= y_max) {
             cerr << "Invalid bounds for Method 2\n";
             cerr << "x_min: " << x_min << ", x_max: " << x_max << "\n";
             cerr << "y_min: " << y_min << ", y_max: " << y_max << "\n";
             return;
        }
        cout << "# Method 2\n";
    }
    uniform_real_distribution<ld> distr_x(x_min, x_max);
    uniform_real_distribution<ld> distr_y(y_min, y_max);

    FOR(N, startN, endN + 1) {
        // Сброс счётчиков
        ll cntin = 0;
        FOR(i, 0, N) {
            ld genx = distr_x(eng);
            ld geny = distr_y(eng);
            if (A.is_inside(genx, geny) && B.is_inside(genx, geny) && C.is_inside(genx, geny)) {
                cntin++;
            }
        }
        ld S_rect = (x_max - x_min) * (y_max - y_min);
        ld S_rec = (static_cast<ld>(cntin) / static_cast<ld>(N)) * S_rect;
        cout << N << " " << S_rec << "\n";
    }
    cout << endl;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.precision(17);
    int startN = 100;
    int endN = 100000;
    int stepN = 500;
    areaMonteCarlo({}, true, startN, endN, stepN);
    areaMonteCarlo({}, false, startN, endN, stepN);
    return 0;
}