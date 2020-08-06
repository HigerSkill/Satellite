from time import strftime, gmtime

import matplotlib.pyplot as plt


def plot_obs_measurement(measures, time):
    """Plot observations."""
    time_axis = [strftime('%H:%M:%S', gmtime(time[i])) for i in range(len(measures))]

    # strftime('%H:%M:%S', gmtime(12345))
    # plt.xticks(measures[::10], time_axis[::10], rotation=90)
    plt.scatter(measures, time, s=1)
    plt.show()
