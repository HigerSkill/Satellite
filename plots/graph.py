from time import strftime, gmtime

import matplotlib.pyplot as plt


def plot_obs_measurement(measures, time, name):
    """Plot observations."""
    # time_axis = [strftime('%H:%M:%S', gmtime(time[i])) for i in range(len(measures))]

    # strftime('%H:%M:%S', gmtime(12345))
    # plt.xticks(measures[::10], time_axis[::10], rotation=90)
    plt.figure(figsize=(10, 10))
    plt.scatter(measures, time, s=1)
    plt.savefig(name, dpi = 100)


def plot_3d_measurements(x, y, z, name):
    ax = plt.axes(projection='3d')
    ax.scatter3D(x, y, z, c=z)
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    plt.savefig(name, dpi = 100)
    plt.show()