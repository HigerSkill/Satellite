def read_obs_measurements(filename):
    """Return list with obs measurements from the file."""
    result = []

    with open(filename) as file:
        for line in file.readlines():
            if line != 'Gluing\n':
                result.append(float(line))

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
                time.append(int(line))

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
