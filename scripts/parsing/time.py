from typing import List

import datetime
import time


def parse_time_to_sec(filepath: str) -> List:
    """Read file with timestamps."""

    timestamps = []

    with open(filepath) as f:
        for line in f.readlines():
            # Parse string time like ``02/11/2021 20:08:00 GPS``
            line = line.split(' ')[1]
            x = time.strptime(line, '%H:%M:%S')
            x = datetime.timedelta(hours=x.tm_hour, minutes=x.tm_min, seconds=x.tm_sec).total_seconds()

            timestamps.append(x)

    return timestamps
