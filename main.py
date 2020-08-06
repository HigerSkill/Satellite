import os
from utils.path import get_list_of_files
from utils.read_files import read_time_file, read_obs_measurements, read_first_differences
from plots.graph import plot_obs_measurement

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

    obs, time = read_first_differences('.out_files/out.txt')
    plot_obs_measurement(time, obs)