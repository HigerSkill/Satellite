#include "MovingAverage.h"

MovingAverage::MovingAverage(unsigned int period) {
    this->period = period;
    this->total = 0;
}


MovingAverage::~MovingAverage() {
    window.clear();
}


void MovingAverage::add(double val) {
    if (window.size() == period) {
        total -= window.front();
        window.pop_front();
    }

    window.push_back(val);
    total += val;
}

void MovingAverage::pop() {
    double val = window.back();
    total -= val;

    window.pop_back();
}

double MovingAverage::avg() const {
    size_t size = window.size();
    if (size == 0) {
        return 0; // No entries => 0 average
    }

    return total / (double) size; // Cast to double for floating point arithmetic
}



