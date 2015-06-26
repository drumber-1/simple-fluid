#include "../common.hpp"

inline float limit(float x, float min, float max);

template <size_t NX, size_t NY>
void advect_linear_backtrace(const FluidArray<NX, NY>& input, FluidArray<NX, NY>& output, const FluidArray<NX, NY>& xvel, const FluidArray<NX, NY>& yvel, float dx, float dt) {

    float dt0 = dt / dx;
    for (size_t i = 1; i < NX - 1; ++i) {
        for (size_t j = 1; j < NY - 1; ++j) {
            float x = i - dt0 * xvel(i, j);
            float y = j - dt0 * yvel(i, j);

            x = limit(x, 0.5f, NX - 1.5f);
            y = limit(y, 0.5f, NY - 1.5f);

            unsigned int i0 = (unsigned int)x;
            unsigned int i1 = i0 + 1;
            unsigned int j0 = (unsigned int)y;
            unsigned int j1 = j0 + 1;

            float x1 = x - i0;
            float x0 = 1 - x1;
            float y1 = y - j0;
            float y0 = 1 - y1;

            output(i, j) = x0 * (y0 * input(i0, j0) + y1 * input(i0, j1)) +
                           x1 * (y0 * input(i1, j0) + y1 * input(i1, j1));

        }
    }
}

inline float limit(float x, float min, float max) {
    if (x < min) {
        x = min;
    } else if (x > max) {
        x = max;
    }
    return x;
}