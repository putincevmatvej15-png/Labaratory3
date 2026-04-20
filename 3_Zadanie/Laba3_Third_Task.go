package main

import (
	"fmt"
)

func gcd(a, b int64) int64 { //ф-я для вычисления НОД
	if a < 0 {
		a = -a
	}
	if b < 0 {
		b = -b
	}
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func main() {
	var a, b int
	fmt.Scan(&a, &b)

	if b == 1 { //если b = 1, ряд расходится
		fmt.Println("infinity")
		return
	}

	A := make([][]int64, a+1)
	for i := range A {
		A[i] = make([]int64, a+1)
	}
	A[0][0] = 1

	for n := 1; n <= a; n++ {
		A[n][0] = 1
		for k := 1; k < n; k++ {
			A[n][k] = int64(k+1)*A[n-1][k] + int64(n-k)*A[n-1][k-1]
		}
		A[n][n-1] = 1
	}
	//ф-ла: sum(n^a/b^n) = (b * sum(A[a][k] * b^(a-1-k))) / (b-1)^(a+1)
	//вычисляем числитель: sum(A[a][k] * b^(a-1-k)) для k от 0 до a-1
	var poly int64 = 0
	powers := make([]int64, a+1)
	powers[0] = 1
	for i := 1; i <= a; i++ {
		powers[i] = powers[i-1] * int64(b)
	}

	for k := 0; k < a; k++ {
		poly += A[a][k] * powers[a-1-k]
	}

	numerator := poly * int64(b)
	var denominator int64 = 1
	for i := 0; i < a+1; i++ {
		denominator *= int64(b - 1)
	}

	g := gcd(numerator, denominator) //сокращаем дробь
	numerator /= g
	denominator /= g

	fmt.Printf("%d/%d\n", numerator, denominator)
}
