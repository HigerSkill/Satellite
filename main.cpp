#include "calculations/vector.cpp"


int main() {
    // Test station position and files.
    Position station(-5105681.0404, 461564.0444, -3782181.6550, Position::Cartesian);
    station.setGeodetic(-36.60284465, 174.83438546, 132.681);

    satellite_station_angles_file(
            "/Users/alex/Documents/master_degree/Satellite/Satellite/test_data/sp3_coords_satellite_day",
            "angles",
            station);
    return 0;
}
