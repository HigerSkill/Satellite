#include "calculations/vector.cpp"
#include <dirent.h>

#include "angles_fullway.cpp"

//#include "parsers/rinex.cpp"
//#include "calculations/first_differences.cpp"
//#include "parsers/sp3.cpp"
//#include "algorithm"

//int angle_sat_station() {
//    // Test angle between satellite and station
//    Position station(-5105681.0404, 461564.0444, -3782181.6550, Position::Cartesian);
//    station.setGeodetic(-36.60284465, 174.83438546, 132.681);
//
//    satellite_station_angles_file(
//            "/Users/aleksandrdimov/Documents/masdeg/Satellite/coords",
//            "angles",
//            station);
//
//    return 0;
//}
//
//int parse_obs() {
//    // Test parser obs files with time
//    int prn = 18;
//    string code = "L1C";
//
//    DIR *dir;
//    struct dirent *ent;
//    if ((dir = opendir ("/Users/aleksandrdimov/Documents/masdeg/Satellite/.rinex")) != NULL) {
//        /* print all the files and directories within directory */
//        int i = 0;
//        while((ent = readdir (dir)) != NULL) {
//            if (string(ent->d_name).length() > 2 && i < 100) {
//                i++;
//                string rinex_file = ent->d_name;
//                obs_parser_file(
//                        "/Users/aleksandrdimov/Documents/masdeg/Satellite/.rinex/"+rinex_file,
//                        "/Users/aleksandrdimov/Documents/masdeg/Satellite/.out_files/" + code + "_" + rinex_file,
//                        code,
//                        prn);
//            }
//        }
//        closedir (dir);
//    } else {
//        /* could not open directory */
//        perror ("");
//        return EXIT_FAILURE;
//    }
//
//    return 0;
//}
//
//int first_diffs_rinex() {
//    // Test get first differences between rinex files and save it in file
//    differences(
//            "/Users/aleksandrdimov/Documents/master_degree/Satellite/Satellite/.rinex/a.20o",
//            "/Users/aleksandrdimov/Documents/master_degree/Satellite/Satellite/.rinex/adis1500.20o",
//            "/Users/aleksandrdimov/Documents/master_degree/Satellite/Satellite/.out_files/out.txt");
//
//    return 0;
//}


//int first_diffs_prepared_files() {
//    // Test get first differences from prepared files with obs measuruments and save it in file
//    int prn = 18;
//    string code = "L1C";
//
//    DIR *dir;
//    struct dirent *ent;
//    if ((dir = opendir ("/Users/aleksandrdimov/Documents/masdeg/Satellite/.rinex")) != NULL) {
//        /* print all the files and directories within directory */
//        int i = 0;
//        while((ent = readdir (dir)) != NULL) {
//            if (string(ent->d_name).length() > 2 && i < 30) {
//                i++;
//                string rinex_file = ent->d_name;
//                first_differences_file(
//                        "/Users/aleksandrdimov/Documents/masdeg/Satellite/.out_files/" + code + "_" + rinex_file,
//                        "/Users/aleksandrdimov/Documents/masdeg/Satellite/.out_files/first_diffs/" + rinex_file);
//            }
//        }
//        closedir (dir);
//    } else {
//        /* could not open directory */
//        perror ("");
//        return EXIT_FAILURE;
//    }
//
//    return 0;
//}

int main() {
    // Test station position and files.
//    parse_obs();
//    coordinates_in_file(
//            "/Users/aleksandrdimov/Documents/masdeg/Satellite/.sp3/150/igs21075.sp3",
//            "/Users/aleksandrdimov/Documents/masdeg/Satellite/sat_coord.sp3",
//            18);
//    angle_sat_station();

//    DIR *dir;
//    struct dirent *ent;
//    if ((dir = opendir ("/Users/aleksandrdimov/Documents/masdeg/Satellite/.sp3res")) != NULL) {
//        /* print all the files and directories within directory */
//        int i = 0;
//        while((ent = readdir (dir)) != NULL) {
//            if (!(string(ent->d_name).find("time") != std::string::npos) && !(string(ent->d_name).find(".") != std::string::npos)) {
//                ifstream myfile ("/Users/aleksandrdimov/Documents/masdeg/Satellite/antenna_position");
//                string line;
//                while (getline(myfile, line)) {
//                    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
//                    if (line.find(string(ent->d_name)) != string::npos) {
//                        getline(myfile,line);
//                        line.erase(std::remove(line.begin(), line.end(), '('), line.end());
//                        line.erase(std::remove(line.begin(), line.end(), ')'), line.end());
//                        line.erase(std::remove(line.begin(), line.end(), ','), line.end());
//                        stringstream ss(line);
//                        double x; ss >> x;
//                        double y; ss >> y;
//                        double z; ss >> z;
//                        Position station(x, x, z, Position::Cartesian);
//
//                        satellite_station_angles_file(
//                                "/Users/aleksandrdimov/Documents/masdeg/Satellite/.sp3res/"+string(ent->d_name),
//                                "/Users/aleksandrdimov/Documents/masdeg/Satellite/.sp3res/angles/angles_"+string(ent->d_name),
//                                station);
//                    }
//                }
//            }
//        }
//        closedir (dir);
//    } else {
//        /* could not open directory */
//        perror ("");
//        return EXIT_FAILURE;
//    }

    get_angles_and_coords(
            "/Users/aleksandrdimov/Documents/masdeg/Satellite/.rinex/iisc1500.20o",
            "/Users/aleksandrdimov/Documents/masdeg/Satellite/.sp3/150/igs21075.sp3",
            18);



    return 0;
}
