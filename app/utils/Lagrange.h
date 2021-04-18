#ifndef SATELLITE_LAGRANGE_H
#define SATELLITE_LAGRANGE_H

double interpolate(double x[], double fx[], double x1, int N) {
    double res = 0, tempSum = 0;

    for(int i = 1; i<=N; i++) {
        double tempProd = 1;         //for each iteration initialize temp product
        for(int j = 1; j<=N; j++) {
            if(i != j) {                 //if i = j, then denominator will be 0
                tempProd *= (x1 - x[j])/(x[i] - x[j]);     //multiply each term using formula
            }
        }
        tempProd *= fx[i];                //multiply f(xi)
        res += tempProd;
    }
    return res;
}


#endif //SATELLITE_LAGRANGE_H
