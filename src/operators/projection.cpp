#include "projection.hpp"

void project_hodge_decomp(FluidArray& xvel, FluidArray& yvel, FluidArray& p, FluidArray& div, double dx, size_t nsteps) {
	for (int i = 1; i < xvel.nx() - 1; ++i) {
		for (int j = 1; j < xvel.ny() - 1; ++j) {
			div(i, j) = -0.5 * dx * (xvel(i + 1, j) - xvel(i - 1, j) + yvel(i, j + 1) - yvel(i, j - 1));
			p(i, j) = 0.0;
		}
	}

	for (int istep = 0; istep < nsteps; ++istep) {
		for (int i = 1; i < xvel.nx() - 1; ++i) {
			for (int j = 1; j < xvel.ny() - 1; ++j) {
				p(i, j) = div(i, j) / 4.0;
				for (int n = 0; n < 4; ++n) {
					p(i, j) += p(i + IADJ[n], j + JADJ[n]) / 4.0;
				}
			}
		}
	}

	for (int i = 1; i < xvel.nx() - 1; ++i) {
		for (int j = 1; j < xvel.ny() - 1; ++j) {
			xvel(i, j) -= 0.5 * (p(i + 1, j) - p(i - 1, j)) / dx;
			yvel(i, j) -= 0.5 * (p(i, j + 1) - p(i, j - 1)) / dx;
		}
	}

}