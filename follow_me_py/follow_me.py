import time
import numpy as np
from mbot_bridge.api import MBot

# Get distance to wall
def find_fwd_dist(ranges, thetas, window=5):
    """Find the distance to the nearest object in front of the robot.

    Args:
        ranges (list): The ranges from the Lidar scan.
        thetas (list): The angles from the Lidar scan.
        window (int, optional): The window to average ranges over. Defaults to 5.

    Returns:
        float: The distance to the nearest obstacle in front of the robot.
    """
    if len(ranges) < window or len(thetas) < 0:
        return -1
    # Grab the rays near the front of the scan.
    fwd_ranges = np.array(ranges[:window] + ranges[-window:])
    fwd_thetas = np.array(thetas[:window] + thetas[-window:])
    # Grab just the positive values.
    valid_idx = (fwd_ranges > 0).nonzero()
    fwd_ranges, fwd_thetas = fwd_ranges[valid_idx], fwd_thetas[valid_idx]

    # Compute forward distances.
    fwd_dists = fwd_ranges * np.cos(fwd_thetas)
    return np.mean(fwd_dists)  # Return the mean.


# Initialize a robot object.
robot = MBot()
setpoint = 0  # TODO: Pick your setpoint.

try:
    # Loop forever.
    while True:
        # TODO: Read the latest Lidar scan and save the values in these vectors.
        ranges, thetas = [], []

        # Get the distance to the wall in front of the robot.
        dist_to_wall = find_fwd_dist(ranges, thetas)

        # TODO: Implement the follow me controller to drive the robot based on
        # the distance to the wall in front.

        # Optionally, sleep for a bit before reading a new scan.
        time.sleep(0.1)

except:
    # Catch any exception, including the user quitting, and stop the robot.
    robot.stop()
