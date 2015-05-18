#include "diffusion.hpp"

void diffuse_simple(const FluidArray& input, FluidArray& output, double diff, double dx, double dt) {

	double a = dt * diff / (dx * dx);

	for (int i = 1; i < input.nx() - 1; ++i) {
		for (int j = 1; j < input.ny() - 1; ++j) {
			output(i, j) = input(i, j);
			for (int n = 0; n < 4; ++n) {
				output(i, j) += a * input(i + IADJ[n], j + JADJ[n]);
			}
			output(i, j) -= 4.0 * a * input(i, j);
		}
	}
}

void diffuse_gauss_seidel(const FluidArray& input, FluidArray& output, double diff, double dx, double dt, size_t nsteps) {

	double a = dt * diff / (dx * dx);

	for (int istep = 0; istep < nsteps; ++istep) {
		for (int i = 1; i < input.nx() - 1; ++i) {
			for (int j = 1; j < input.ny() - 1; ++j) {
				output(i, j) = input(i, j) / (1 + (4 * a));
				for (int n = 0; n < 4; ++n) {
					output(i, j) += a * output(i + IADJ[n], j + JADJ[n]) / (1.0 + (4.0 * a));
				}
			}
		}
	}
}





