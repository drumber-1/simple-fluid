#pragma once

namespace util {
	int wrap(int x, int max) {
		x %= max;
		if (x < 0) {
			return x + max;
		} else {
			return x;
		}
	}
}
