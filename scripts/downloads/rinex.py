import os
from ftplib import FTP_TLS
import ftplib

from config import CDDIS_EMAIL, CDDIS_HOST


def download_rinex(station: str, rinex_type: str, year: int):
    """Download RINEX specific type of files for selected year."""

    short_year = year % 100
    print(short_year)

    folder = f'../../output/rinex/{year}/{station}'
    if not os.path.exists(folder):
        os.makedirs(folder)

    ftps = FTP_TLS(host=CDDIS_HOST)
    ftps.login(user='anonymous', passwd=CDDIS_EMAIL)
    ftps.prot_p()

    for i in range(1, 366):
        if i < 10:
            day = f'00{i}'
        if 10 <= i < 100:
            day = f'0{i}'
        if 100 <= i:
            day = f'{i}'

        directory = f'/pub/gnss/data/daily/{year}/{day}/{short_year}{rinex_type}/'

        try:
            filename = f'{station}{day}0.{short_year}{rinex_type}.Z'
            ftps.cwd(directory)
            print(filename)

            ftps.retrbinary("RETR " + filename, open(f'{folder}/{filename}', 'wb').write)
        except ftplib.error_perm:
            try:
                filename = f'{station}{day}0.{short_year}{rinex_type}.gz'
                ftps.cwd(directory)
                print(filename)

                ftps.retrbinary("RETR " + filename, open(f'{folder}/{filename}', 'wb').write)
            except ftplib.error_perm as e:
                print(e)
                continue


if __name__ == '__main__':
    rinex_type = input('Input RINEX type (o - obs, n - nav, etc.): ')
    year = int(input('Input year: '))
    station = input('Input station name: ')

    download_rinex(station, rinex_type, year)