/**
 * File: follow_me.cpp
 *
 * Controls the robot to maintain a given distance to the wall directly in
 * front of it.
 *
 * This code uses Bang-Bang control or P-control to maintain the setpoint
 * distance.
 */

#include <iostream>
#include <cmath>
#include <signal.h>

#include <mbot_bridge/robot.h>  // This line imports the MBot Bridge API in C++.


bool ctrl_c_pressed;
void ctrlc(int)
{
    ctrl_c_pressed = true;
}

/**
 * Finds the distance to the nearest object in front of the robot by averaging
 * a few forward-pointing rays.
 */
float findFwdDist(const std::vector<float>& ranges, const std::vector<float>& thetas)
{
    // Simple average filter over the front rays in case a few are invalid.
    int num_range = 5;
    // Check for invalid vector lengths.
    if (ranges.size() < num_range || thetas.size() < num_range)  return -1;

    int num_scans = 0;
    float sum = 0;

    // Read the first few rays.
    for (int i = 0; i < num_range; ++i) {
        if (ranges[i] > 0) {
            sum += ranges[i] * cos(thetas[i]);
            num_scans++;
        }
    }
    // Read the last few rays.
    for (int i = ranges.size() - num_range; i < ranges.size(); ++i) {
        if (ranges[i] > 0) {
            sum += ranges[i] * cos(thetas[i]);
            num_scans++;
        }
    }

    // If we didn't find any valid scans, return an invalid value.
    if (num_scans < 1) return -1;

    return sum / num_scans;  // Return the average distance.
}


int main(int argc, const char *argv[])
{
    signal(SIGINT, ctrlc);
    signal(SIGTERM, ctrlc);

    // Initialize the robot.
    mbot_bridge::MBot robot;
    // We will store the Lidar scan data in these vectors.
    std::vector<float> ranges;
    std::vector<float> thetas;

    // *** TODO: Adjust these values and add more as needed. ***
    float setpoint = 0;  // The goal distance from the wall in meters

    while (!ctrl_c_pressed) {
        // *** TODO: Read the Lidar scan and put the resulting data in the vectors: ranges, thetas ***

        // Get the distance to the wall.
        float dist_to_wall = findFwdDist(ranges, thetas);
        if (dist_to_wall < 0) continue;

        // *** TODO: Implement the Follow Me controller. *** //

    }

    // Stop the robot.
    robot.stop();
    return 0;
}
