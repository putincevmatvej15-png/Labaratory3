#include <iostream>
#include <vector>

using namespace std;

long long gcd(long long a, long long b) { //ф-я для вычисления НОД
    a = abs(a);
    b = abs(b);
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    int a, b;
    cin >> a >> b;
    
    if (b == 1) { //если b = 1, ряд расходится
        cout << "infinity" << endl;
        return 0;
    }
    
    vector<vector<long long>> A(a + 1, vector<long long>(a + 1, 0));
    A[0][0] = 1;
    
    for (int n = 1; n <= a; n++) {
        A[n][0] = 1;
        for (int k = 1; k < n; k++) {
            A[n][k] = (k + 1) * A[n-1][k] + (n - k) * A[n-1][k-1];
        }
        A[n][n-1] = 1;
    }
    
    //ф-ла: sum(n^a/b^n) = (b * sum(A[a][k] * b^(a-1-k))) / (b-1)^(a+1)
    //вычисляем числитель: sum(A[a][k] * b^(a-1-k)) для k от 0 до a-1
    long long poly = 0;
    long long power = 1;
    
    //вычисляем степени b
    vector<long long> powers(a + 1);
    powers[0] = 1;
    for (int i = 1; i <= a; i++) {
        powers[i] = powers[i-1] * b;
    }
    
    for (int k = 0; k < a; k++) {
        poly += A[a][k] * powers[a - 1 - k];
    }
    //числитель окончательной дроби
    long long numerator = poly * b;
    //знаменатель: (b-1)^(a+1)
    long long denominator = 1;
    for (int i = 0; i < a + 1; i++) {
        denominator *= (b - 1);
    }
    
    //сокращаем дробь
    long long g = gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;
    
    cout << numerator << "/" << denominator << endl;
    
    return 0;
}