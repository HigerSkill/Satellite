import datetime
import os

from scripts.parsing import coordinates

import matplotlib.pyplot as plt


def draw_trajectory(filepath: str, timestamps: bool = False):
    """Draw graph of observation data."""

    t, x, y, z = coordinates.parse_coordinates_file(filepath=filepath)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    plt.xlabel('X', fontsize=10, rotation = 0)
    plt.ylabel('Y', fontsize=10, rotation = 0)
    ax.set_zlabel('Z', fontsize=10, rotation = 0)

    # Add timestamps to plot
    if timestamps:
        for i in range(len(t)):
            timea = str(datetime.timedelta(seconds=t[i]))
            ax.annotate(timea, (x[i], y[i], z[i]),)

    ax.scatter(x, y, z, label='Траектория движения НКА')
    # ax.legend()

    plt.show()

if __name__ == '__main__':
    draw_trajectory('../../output/sp3_3.txt')

