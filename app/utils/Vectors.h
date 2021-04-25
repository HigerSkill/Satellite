#ifndef SATELLITE_VECTORS_H
#define SATELLITE_VECTORS_H

#include <vector>
#include <math.h>


/**
 * Calculate n-vector for latitude and longitude of station.
 * Equation is exact both for spherical and ellipsoidal Earth model.
 *
 * @param latitude
 * @param longitude
 * @return Coordinates of n-vector.
 */
gpstk::Position nVector(double latitude, double longitude) {
    double a = cos(latitude) * cos(longitude);
    double b = cos(latitude) * sin(longitude);
    double c = sin(latitude);

    gpstk::Position normal(a, b, c);

    return normal;
}

/**
 * Calculate module of vector
 *
 * @param a
 * @param b
 * @return Module of vector.
 */
double absVector(gpstk::Position vec) {
    return sqrt(vec.X() * vec.X() + vec.Y() * vec.Y() + vec.Z() * vec.Z());
}

/**
 * Calculate vector multiply
 *
 * @param a
 * @param b
 * @return Scalar multiply a x b.
 */
gpstk::Position vectorMultiply(gpstk::Position a, gpstk::Position b) {
    return gpstk::Position(a.Y()*b.Z() - a.Z()*b.Y(), a.Z()*b.X() - a.X()*b.Z(), a.X()*b.Y() - a.Y()*b.X());
}

/**
 * Calculate scalar multiply
 *
 * @param a
 * @param b
 * @return Scalar multiply a*b.
 */
double vectorScalar(gpstk::Position a, gpstk::Position b) {
    return a.X() * b.X() + a.Y() * b.Y() + a.Z() * b.Z();
}

/**
 * Get vector by two points
 *
 * @param a
 * @param b
 * @return Vector by a and b.
 */
gpstk::Position getVector(gpstk::Position a, gpstk::Position b) {
    return gpstk::Position(b.X() - a.X(), b.Y() - a.Y(), b.Z() - a.Z());
}

/**
 * Find cos of the angle between vectors.
 *
 * @param a Vector a.
 * @param b Vector b.
 * @return Cosines of the angle between vectors.
 */
double getCosAngle(std::vector<double> a, std::vector<double> b) {
    double scalar = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];

    double len_a = sqrt(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2));
    double len_b = sqrt(pow(b[0], 2) + pow(b[1], 2) + pow(b[2], 2));

    double cosAngle = scalar / (len_a * len_b);

    return cosAngle;
}


/**
 * Find angle between vectors.
 *
 * @param a Vector a.
 * @param b Vector b.
 * @return Angle between vectors in radians.
 */
double getAngle(std::vector<double> a, std::vector<double> b) {
    return acos(getCosAngle(a, b));
}


#endif //SATELLITE_VECTORS_H
