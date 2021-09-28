from ftplib import FTP_TLS

from config import CDDIS_EMAIL, CDDIS_HOST
import os

import gnsscal


def download_sp3(sp3_type: str, year: int):
    """Download sp3 file that are between `week_start` and `week_end`."""
    week_start, _ = gnsscal.yrdoy2gpswd(year, 1)
    week_end, _ = gnsscal.yrdoy2gpswd(year, 365)

    folder = f'../../output/sp3/{year}'
    if not os.path.exists(folder):
        os.makedirs(folder)

    for week in range(week_start, week_end + 1):
        for day in range(0, 7):
            filename = f'{sp3_type}{week}{day}.sp3.Z'
            directory = f'/pub/gps/products/{week}'

            ftps = FTP_TLS(host=CDDIS_HOST)
            ftps.login(user='anonymous', passwd=CDDIS_EMAIL)
            ftps.prot_p()
            ftps.cwd(directory)

            print(filename)

            ftps.retrbinary("RETR " + filename, open(f'{folder}/{filename}', 'wb').write)


if __name__ == '__main__':
    sp3_type = input('Input SP3 type (igs, igl, etc.): ')
    year = int(input('Input year: '))

    download_sp3(sp3_type, year)



