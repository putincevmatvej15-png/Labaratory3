//тест Полингтона
#include <iostream>
#include <vector>
#include <cstdint>
#include <ctime>

using namespace std;

typedef uint64_t uint64;

uint64 mul_mod(uint64 a, uint64 b, uint64 mod) { //безопасно (a * b) % mod без __int128
    uint64 res = 0;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1) res = (res + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return res;
}

uint64 power_mod(uint64 base, uint64 exp, uint64 mod) {
    uint64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = mul_mod(res, base, mod);
        base = mul_mod(base, base, mod);
        exp /= 2;
    }
    return res;
}

int main() {
    uint64 n;
    int32_t k, t;
    cout << "Введите n, k, делители q_i и t: ";
    if (!(cin >> n >> k)) return 0;

    vector<uint64> q(k);
    for (int i = 0; i < k; i++) cin >> q[i];
    cin >> t;

    srand(time(0));
    for (int i = 0; i < t; i++) {
        uint64 a = 2 + rand() % (n - 3);
        if (power_mod(a, n - 1, n) != 1) {
            cout << "false (составное)" << endl;
            return 0;
        }
        bool any_one = false;
        for (uint64 qi : q) {
            if (power_mod(a, (n - 1) / qi, n) == 1) {
                any_one = true;
                break;
            }
        }
        if (!any_one) {
            cout << "true (простое)" << endl;
            return 0;
        }
    }
    cout << "false" << endl;
    return 0;
}