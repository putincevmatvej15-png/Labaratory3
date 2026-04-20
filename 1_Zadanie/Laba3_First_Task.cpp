#include <iostream>
#include <cmath>

using namespace std;

double f(double x) {
    double y;
    
    if (x >= -5.0 && x <= -2.0) {
        y = -x - 2; //прямая 
    } 
    else if (x > -2.0 && x <= -1.0) {
        y = sqrt(1.0 - pow(x + 1, 2)); //окружность с центром (1;0) и R=1
    } 
    else if (x > -1.0 && x <= 1.0) {
        y = 1.0; //прямая
    } 
    else if (x > 1.0 && x <= 2.0) {
        y = -2.0 * x + 3.0; //прямая, через (1;1) и (2;-1)
    } 
    else if (x > 2.0 && x <= 4.0) {
        y = -1.0; //прямая
    } 
    else if (x > 4.0 && x <= 6.0) {
        y = 0.5 * pow(x - 4, 2) - 1.0; // парабола с вершиной в (4;-1) и коэффициентом 0.5
    } 
    else {
        y = NAN; //если выйдем за пределы
    }
    return y;
}

int main() {
    double x_start = -5.0;
    double x_end = 6.0;
    double dx = 0.5;

    cout << "x\ty = f(x)" << endl;
    cout << "----------------" << endl;

    // добавляем 0.001 для надёжного включения последнего значения из-за погрешности float
    for (double x = x_start; x <= x_end + 0.001; x += dx) {
        double y = f(x);
        
        if (!isnan(y)) {
            cout << x << "\t" << y << endl;
        }
    }
    return 0;
}