#ifndef SATELLITE_MOVINGAVERAGE_H
#define SATELLITE_MOVINGAVERAGE_H

#include <stddef.h>
#include <assert.h>
#include <list>


class MovingAverage {
private:
    unsigned int period;

    // Holds the values to calculate the average of.
    std::list<double> window;

    // Cache the total so we don't sum everything each time.
    double total;

public:
    /*
     * Constructor moving average.
     *
     * @param period Period of the moving average.
     */
    MovingAverage(unsigned int period);

    /*
     * Destructor moving average.
     */
    ~MovingAverage();

    /*
     * Adds a value to the average, pushing one out if necessary.
     *
     * @param val Value which will be added.
     */
    void add(double val);

    /*
    * Remove last element from the window.
    *
    * @param val Value which will be added.
    */
    void pop();


    /*
     * Returns the average of the last P elements added to this Moving Average.
     * If no elements have been added yet, returns 0.0
     */
    double avg() const;

};


#endif //SATELLITE_MOVINGAVERAGE_H
