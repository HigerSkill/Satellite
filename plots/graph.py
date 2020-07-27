import matplotlib.pyplot as plt


def plot_obs_measurement(measures, time):
    """Plot observations."""
    time_axis = [time[i] for i in range(len(measures))]

    plt.plot(time_axis, measures)
    plt.show()


def read_time_file(filename):
    """Get time from file."""
    time = []
    with open(filename) as file:
        for line in file.readlines():
            # Get only time from string like: "05/29/2020 01:43:30 GPS"
            time.append(line.split(' ')[1])

    return time
