package main

import (
	"fmt"
	"math"
)

func main() {
	var n, m int
	fmt.Scan(&n, &m)

	a := make([]int64, n) //считываем массив чисел
	for i := 0; i < n; i++ {
		fmt.Scan(&a[i])
	}

	pref := make([]int64, n+1) //префиксные суммы: pref[i] = сумма первых i элементов
	for i := 0; i < n; i++ {
		pref[i+1] = pref[i] + a[i]
	}

	var scorePavel, scoreVika int64
	pos := 0                      //текущая позиция в массиве
	lastPavel, lastVika := -1, -1 //последние ходы игроков
	pavelTurn := true             //чей сейчас ход

	for pos < n {
		lastUsed := lastPavel
		if !pavelTurn {
			lastUsed = lastVika
		}

		bestSum := int64(math.MinInt64)
		bestK := -1

		for k := 1; k <= m && pos+k <= n; k++ { //перебираем все допустимые количества чисел
			if k == lastUsed {
				continue //нельзя повторять свой последний ход
			}
			sum := pref[pos+k] - pref[pos] //сумма k чисел с позиции pos

			//выбираем максимум суммы, при равенстве — минимальное k
			//так как цикл идёт от 1 к m, при sum == best_sum мы не обновляем, тем самым сохраняя минимальное k
			if sum > bestSum {
				bestSum = sum
				bestK = k
			}
		}

		//применяем выбранный ход
		if pavelTurn {
			scorePavel += bestSum
			lastPavel = bestK
		} else {
			scoreVika += bestSum
			lastVika = bestK
		}

		pos += bestK           //продвигаемся по массиву
		pavelTurn = !pavelTurn //смена хода
	}

	//вывод результата: 1 если Павел выиграл, 0 если Вика
	if scorePavel > scoreVika {
		fmt.Println(1)
	} else {
		fmt.Println(0)
	}
}
