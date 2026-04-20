package main

import (
	"fmt"
	"math"
)

func f(x float64) float64 {
	var y float64

	if x >= -5.0 && x <= -2.0 {
		y = -x - 2 //прямая
	} else if x > -2.0 && x <= -1.0 {
		y = math.Sqrt(1.0 - math.Pow(x+1, 2)) //окружность с центром (1;0) и R = 1
	} else if x > -1.0 && x <= 1.0 {
		y = 1.0 //прямая
	} else if x > 1.0 && x <= 2.0 {
		y = -2.0*x + 3.0 //прямая, через (1;1) и (2;-1)
	} else if x > 2.0 && x <= 4.0 {
		y = -1.0 //прямая
	} else if x > 4.0 && x <= 6.0 {
		y = 0.5*math.Pow(x-4, 2) - 1.0 // парабола с вершиной в (4;-1) и коэффициентом 0.5
	} else {
		y = math.NaN() //если выйдем за пределы
	}

	return y
}

func main() {
	xStart := -5.0
	xEnd := 6.0
	dx := 0.5

	fmt.Println("x\ty = f(x)")
	fmt.Println("----------------")

	// добавляем 0.001 для надёжного включения последнего значения из-за погрешности float
	for x := xStart; x <= xEnd+0.001; x += dx {
		y := f(x)

		if !math.IsNaN(y) {
			fmt.Printf("%g\t%g\n", x, y)
		}
	}
}
