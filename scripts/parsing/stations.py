import json
from collections import namedtuple


def get_station_info(file: str, station_name: str) -> namedtuple:
    """Return station info like name, latitude, longitude, coordination."""
    with open(file, "r") as f:
        data = json.load(f)

        station = next(
            v for k, v in data.items()
            if station_name.lower() in k.lower()
        )

        print(
            f'Station: {station_name} \n'
            f'Lat: {station["Latitude"]} \n'
            f'Long: {station["Longitude"]} \n'
            f'X: {station["X"]} \n'
            f'Y: {station["Y"]} \n'
            f'Z: {station["Z"]} \n'
        )

    station_info = namedtuple('station', 'name lat long x y z')
    return station_info(
        station_name,
        station.get('Latitude'),
        station.get('Longitude'),
        station.get('X'),
        station.get('Y'),
        station.get('Z')
    )
