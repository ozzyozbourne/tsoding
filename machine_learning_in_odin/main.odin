package main

import "core:fmt"
import "core:math/rand"

train := [][2]f64{{0, 0}, {1, 2}, {2, 4}, {3, 6}, {4, 8}}

cost :: proc(w: f64) -> (res: f64) {
	for v, i in train {
		x := v[0]
		y := x * w
		d := y - v[1]
		res += (d * d)
	}
	res /= f64(len(train))
	return
}

main :: proc() {
	// y = x * w
	w := rand.float64() * 10
	fmt.println(cost(w))
}
