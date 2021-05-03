import datetime
import os

from scripts.parsing import coordinates

import matplotlib.pyplot as plt


def draw_observations(filepath: str, timestamps: bool = False):
    """Draw graph of observation data."""

    times, r, theta = coordinates.parse_projections(filepath=filepath)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='polar')

    # Add timestamps to plot
    if timestamps:
        for i in range(len(r)):
            timea = str(datetime.timedelta(seconds=times[i]))
            ax.annotate(timea, (theta[i], r[i]),)

    ax.scatter(theta, r)

    plt.show()


if __name__ == '__main__':
    # draw_observations('/home/alex/Documents/glonass_satellite/output_files/MAFixed2018/0010.txt')
    # draw_observations('/home/alex/Documents/glonass_satellite/cmake-build-debug/outPROJ1.txt')
    # draw_observations('/home/alex/CLionProjects/Satellite/output/projection_1.txt')

    dir = '/home/alex/CLionProjects/Satellite/output/20_glonass/'

    times = []
    r = []
    theta = []

    for i in range(1, 366):
        if i < 10:
            day = f'00{i}0.txt'
        if 10 <= i < 100:
            day = f'0{i}0.txt'
        if 100 <= i:
            day = f'{i}0.txt'

        print(day)
        try:
            times1, r1, theta1 = coordinates.parse_projections(filepath=os.path.join(dir, day))
        except:
            continue
        times.extend(times1)
        r.extend(r1)
        theta.extend(theta1)

    fig = plt.figure()

    ax = fig.add_subplot(111, projection='polar')

    ax.scatter(theta, r, alpha=0.5)
    plt.show()

    # plt.savefig(f'/home/alex/Documents/glonass_satellite/apps/graphs/aruc/ARUC_{prn}.png', dpi=300)
