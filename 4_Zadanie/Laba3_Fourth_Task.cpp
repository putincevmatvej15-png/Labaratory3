#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    //префиксные суммы: pref[i] = сумма первых i элементов
    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + a[i];
    }
    
    long long score_pavel = 0, score_vika = 0;
    int pos = 0;                        //текущая позиция в массиве
    int last_pavel = -1, last_vika = -1; //последние ходы игроков
    bool pavel_turn = true;           //чей сейчас ход
    
    while (pos < n) {
        int last_used = pavel_turn ? last_pavel : last_vika;
        long long best_sum = LLONG_MIN;
        int best_k = -1;
        //перебираем все допустимые количества чисел
        for (int k = 1; k <= m && pos + k <= n; k++) {
            if (k == last_used) continue;//нельзя повторять свой последний ход
            
            long long sum = pref[pos + k] - pref[pos];//сумма k чисел с позиции pos
            
            //выбираем максимум суммы, при равенстве — минимальное k
            if (sum > best_sum) {
                best_sum = sum;
                best_k = k;
            }
        }
        //применяем выбранный ход
        if (pavel_turn) {
            score_pavel += best_sum;
            last_pavel = best_k;
        } else {
            score_vika += best_sum;
            last_vika = best_k;
        }
        
        pos += best_k;              //продвигаемся по массиву
        pavel_turn = !pavel_turn;   //смена хода
    }
    cout << (score_pavel > score_vika ? 1 : 0) << endl;
    return 0;
}