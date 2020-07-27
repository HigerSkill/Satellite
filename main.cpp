#include "calculations/vector.cpp"
#include <dirent.h>

#include "parsers/rinex.cpp"
#include "calculations/first_differences.cpp"

int main() {
    // Test station position and files.

    // Test angle between satellite and station
//    Position station(-5105681.0404, 461564.0444, -3782181.6550, Position::Cartesian);
//    station.setGeodetic(-36.60284465, 174.83438546, 132.681);
//
//    satellite_station_angles_file(
//            "/Users/alex/Documents/master_degree/Satellite/Satellite/test_data/sp3_coords_satellite_day",
//            "angles",
//            station);

    //


//    int prn = 18;
//    string code = "L1C";
//
//    DIR *dir;
//    struct dirent *ent;
//    if ((dir = opendir ("/Users/alex/Documents/master_degree/Satellite/Satellite/.rinex")) != NULL) {
//        /* print all the files and directories within directory */
//        int i = 0;
//        while((ent = readdir (dir)) != NULL) {
//            if (string(ent->d_name).length() > 2 && i < 100) {
//                i++;
//                string rinex_file = ent->d_name;
//                obs_parser(
//                        "/Users/alex/Documents/master_degree/Satellite/Satellite/.rinex/"+rinex_file,
//                        "/Users/alex/Documents/master_degree/Satellite/Satellite/.out_files/" + code + "_" + rinex_file,
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




    int prn = 18;
    string code = "L1C";

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("/Users/alex/Documents/master_degree/Satellite/Satellite/.rinex")) != NULL) {
        /* print all the files and directories within directory */
        int i = 0;
        while((ent = readdir (dir)) != NULL) {
            if (string(ent->d_name).length() > 2 && i < 100) {
                i++;
                string rinex_file = ent->d_name;
                first_differences_file(
                        "/Users/alex/Documents/master_degree/Satellite/Satellite/.out_files/" + code + "_" + rinex_file,
                        "/Users/alex/Documents/master_degree/Satellite/Satellite/.out_files/first_diffs/" + rinex_file);
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }


    return 0;
}
