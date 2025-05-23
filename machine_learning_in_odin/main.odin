package main

import "core:fmt"
import "core:math/rand"

train := [][2]f32{{0, 0}, {1, 2}, {2, 4}, {3, 6}, {4, 8}}


main :: proc() {
	// y = x * w
	w := rand.float32()
	fmt.printfln("The Weight is -> %f", w)
	for v, i in train {
		x := v[0]
		y := x * w
		fmt.printfln("Actual: %f   Expected: %f", y, v[1])
	}
}
