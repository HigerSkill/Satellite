def read_obs_measurements(filename):
    """Return list with obs measurements from the file."""
    result = []

    with open(filename) as file:
        for line in file.readlines():
            if line != 'Gluing\n':
                result.append(float(line.split('\n')[0]))

    return result

def read_time_sec(filename):
    """Return list with time from the file."""
    result = []

    with open(filename) as file:
        for line in file.readlines():
            if line != 'Gluing\n':
                result.append(int(line.split('\n')[0]))

    return result


def read_time_file(filename, sec=True):
    """Get time from file."""
    time = []
    with open(filename) as file:
        for line in file.readlines():
            if 'GPS' in line:
                # Get only time from string like: "05/29/2020 01:43:30 GPS"
                time.append(line.split(' ')[1])
            else:
                pass
                # time.append(int(line))

    return time


def read_first_differences(filename):
    obs = []
    time = []
    with open(filename) as file:
        for line in file.readlines():
            value, sec = line.split('|')
            obs.append(float(value))
            time.append(int(sec))

    return obs, time


def read_coords(filename):
    x, y, z = [], [], []

    with open(filename) as file:
        for line in file.readlines():
            vx, vy, vz = line.split(' ')
            x.append(float(vx))
            y.append(float(vy))
            z.append(float(vz))

    return x, y, z