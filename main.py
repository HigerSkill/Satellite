import os
from utils.path import get_list_of_files
from utils.read_files import read_time_file, read_obs_measurements, read_first_differences, read_coords, read_time_sec
from plots.graph import plot_obs_measurement, plot_3d_measurements
from utils.write_files import list_to_file
import glob
import datetime
import time

if __name__ == '__main__':
    rinex_path = '.out_files/rinex/'
    first_diff_path = '.out_files/first_diffs/'
    #
    # rinex_files = get_list_of_files(rinex_path)
    # first_diff_files = get_list_of_files(first_diff_path)
    #
    # time = read_time_file(rinex_files[1])
    # obs = read_obs_measurements(rinex_files[0])
    # plot_obs_measurement(obs, time)
    #
    # time = read_time_file(rinex_files[5])
    # obs = read_obs_measurements(rinex_files[4])
    # plot_obs_measurement(obs, time)

    # obs, time = read_first_differences('.out_files/out.txt')
    # plot_obs_measurement(time, obs)

    # time_sp3 = read_time_file('trash/sp3_time.sp3')
    # time_rinex = read_time_file('trash/L1C_auck1500_time')
    #
    # coord = read_obs_measurements('trash/sat_coord.sp3')
    # coord_new = []
    # time_new = []
    #
    # for time in time_rinex:
    #     try:
    #         ind = time_sp3.index(time)
    #         time_new.append(time_sp3.pop(ind))
    #         coord_new.append(coord.pop(ind))
    #     except:
    #         pass

    # list_to_file(time_new, 'trash/time')
    # list_to_file(coord_new, 'trash/coords')
    # print(time_new)
    # print(coord_new)

    # time_sp3 = read_time_file('sp3_time.sp3')
    # files = glob.glob('.out_files/*time')
    # coord = read_obs_measurements('sat_coord.sp3')
    # for file in files:
    #     station = file.split('_')[2].split('1500')[0]
    #     time_res = []
    #     coord_res = []
    #     rnx_time = read_time_file(file)
    #
    #     for time in rnx_time:
    #         try:
    #             ind = time_sp3.index(time)
    #             time_res.append(time_sp3[ind])
    #             coord_res.append(coord[ind])
    #         except:
    #             pass
    #
    #     list_to_file(time_res, f'.sp3res/{station}_time')
    #     list_to_file(coord_res, f'.sp3res/{station}')


    # files = glob.glob('.sp3res/angles/angles*')
    # print(files)
    # i = 0
    # for file in files:
    #     # if i > 0:
    #     #     break
    #     # i+=1
    #     station = file.split('_')[1]
    #     angles = read_obs_measurements(file)
    #     print(station)
    #     times = []
    #     for file in glob.glob(f".sp3res/{station}_time"):
    #         with open(file) as f:
    #             for line in f.readlines():
    #                 x = time.strptime(line.split('\n')[0], '%H:%M:%S')
    #                 x = datetime.timedelta(hours=x.tm_hour,minutes=x.tm_min,seconds=x.tm_sec).total_seconds()
    #                 times.append(int(x))
    #
    #     plot_obs_measurement(times, angles, f'.sp3res/plots/{station}.png')



    angles = read_obs_measurements('/Users/aleksandrdimov/Documents/masdeg/Satellite/cmake-build-debug/IISC_angles')
    print(angles)

    times = []
    with open('/Users/aleksandrdimov/Documents/masdeg/Satellite/cmake-build-debug/IISC_time') as f:
        for line in f.readlines():
            x = line.split('\n')[0]
            times.append(int(x))


    plot_obs_measurement(times, angles, f'iisc_angles.png')

    # x, y, z = read_coords(
    #     '/Users/aleksandrdimov/Documents/masdeg/Satellite/cmake-build-debug/IISC_coords'
    # )
    # time = read_time_sec(
    #     '/Users/aleksandrdimov/Documents/masdeg/Satellite/cmake-build-debug/IISC_time'
    # )
    # plot_3d_measurements(x, y, z, 'iisc')