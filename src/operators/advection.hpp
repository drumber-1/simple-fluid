#include "common.hpp"

inline double limit(double x, double min, double max);

template <size_t NX, size_t NY>
void advect_linear_backtrace(const FluidArray<NX, NY>& input, FluidArray<NX, NY>& output, const FluidArray<NX, NY>& xvel, const FluidArray<NX, NY>& yvel, double dx, double dt) {

    double dt0 = dt / dx;
    for (int i = 1; i < NX - 1; ++i) {
        for (int j = 1; j < NY - 1; ++j) {
            double x = i - dt0 * xvel(i, j);
            double y = j - dt0 * yvel(i, j);

            x = limit(x, 0.5, NX - 1.5);
            y = limit(y, 0.5, NY - 1.5);

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