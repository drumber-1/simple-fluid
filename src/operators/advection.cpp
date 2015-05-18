#include "advection.hpp"

inline double limit(double x, double min, double max);

void advect_linear_backtrace(const FluidArray& input, FluidArray& output, const FluidArray& xvel, const FluidArray& yvel, double dx, double dt) {

	double dt0 = dt / dx;
	for (int i = 1; i < input.nx() - 1; ++i) {
		for (int j = 1; j < input.ny() - 1; ++j) {
			double x = i - dt0 * xvel(i, j);
			double y = j - dt0 * yvel(i, j);

			x = limit(x, 0.5, input.nx() + 0.5);
			y = limit(y, 0.5, input.ny() + 0.5);

			int i0 = (int)x; int i1 = i0 + 1;
			int j0 = (int)y; int j1 = j0 + 1;

			double x1 = x - i0;
			double x0 = 1 - x1;
			double y1 = y - j0;
			double y0 = 1 - y1;

			output(i, j) = x0 * (y0 * input(i0, j0) + y1 * input(i0, j1)) +
						   x1 * (y0 * input(i1, j0) + y1 * input(i1, j1));

		}
	}
}

inline double limit(double x, double min, double max) {
	if (x < min) {
		x = min;
	} else if (x > max) {
		x = max;
	}
	return x;
}