# Navigation-Unit

Drop-in naviation unit for ny robot using an RPLIDAR A1 and and Intel Realsense T265 Tracking Camera.

Code in the Arduino directory is to control a differental drive robot with two wheels using 4 PWM lines. I used IBT4 drivers. There are no wheel encoders on my robot, so the scaling from the cmd_vel topic was done by trial and error. Encoders would of course make the robot velocity more reliable, however in this example encoders are not required since Odometry is provided by the T265 tracking camera.

How to make it work:

Install ROS & create a Catkin Workspace. I used ROS Melodic on Ubuntu 18.0 4 on both my Jetson Nano mounted on the robot, and my workstation:

http://wiki.ros.org/melodic/Installation/Ubuntu

http://wiki.ros.org/catkin/Tutorials/create_a_workspace

Install the Intel Realsense Dev kit and ROS drivers:

https://github.com/IntelRealSense/librealsense/blob/development/doc/distribution_linux.md

https://github.com/IntelRealSense/realsense-ros
