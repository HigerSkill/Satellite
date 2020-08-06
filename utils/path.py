import os
from typing import List


def get_list_of_files(path: str) -> List[str]:
    """Return list of files in directory `path`."""
    listdir = [os.path.join(path, f) for f in os.listdir(path)]
    listdir.sort()

    return listdir
