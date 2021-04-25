#ifndef SATELLITE_LAGRANGE_H
#define SATELLITE_LAGRANGE_H

/*
 * Interpolation by Lagrangian Polynomials
 *
 * @param x Array values of x
 * @param fx Array valued of f(x)
 * @param x1 Point which need to find f(x1)
 * @param N Polynomial degree
 *
 * @return f(x1)
 */
double interpolate(double x[], double fx[], double x1, int N) {
    double res = 0, tempSum = 0;

    for(int i = 1; i<=N; i++) {
        // For each iteration initialize temp product
        double tempProd = 1;
        for(int j = 1; j<=N; j++) {
            // If i = j, then denominator will be 0
            if(i != j) {
                // Multiply each term using formula
                tempProd *= (x1 - x[j])/(x[i] - x[j]);
            }
        }
        // Multiply f(xi)
        tempProd *= fx[i];
        res += tempProd;
    }
    return res;
}


#endif //SATELLITE_LAGRANGE_H
