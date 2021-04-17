from typing import List, Tuple


def read_coordinates_file(filepath: str) -> Tuple[list]:
    """Read file with coordinates X,Y,Z."""
    x, y, z = [], [], []

    with open(filepath) as f:
        for line in f.readlines():
            if (len(line)) < 6:
                continue

            line = line.split(',')

            x.append(float(line[0]))
            y.append(float(line[1]))
            z.append(float(line[2]))

    return x, y, z
