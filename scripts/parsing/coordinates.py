from typing import List, Tuple


def parse_coordinates_file(filepath: str) -> Tuple[list]:
    """Read file with coordinates X,Y,Z."""
    t, x, y, z = [], [], [], []

    with open(filepath) as f:
        for line in f.readlines():
            if (len(line)) < 6:
                continue

            line = line.split(',')

            t.append(float(line[0]))
            x.append(float(line[1]))
            y.append(float(line[2]))
            z.append(float(line[3]))

    return t, x, y, z


def parse_projections(filepath: str) -> Tuple[List, List, List]:
    """Parse file with projections `time, r, theta`."""
    times, r, theta = [], [], []

    with open(filepath) as f:
        for line in f.readlines():
            if len(line) < 6:
                continue

            line = line.split(',')

            times.append(float(line[0]))
            r.append(float(line[1]))
            theta.append(float(line[2]))

    return times, r, theta

