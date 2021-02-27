# Navigation-Unit

Video: https://youtu.be/xB9tfi_Bzs8

Drop-in naviation unit for my robot using an RPLIDAR A1 and and Intel Realsense T265 Tracking Camera.

This is not a tutorial, you'll require some prior ROS knowledge.

Code in the Arduino directory is to control a differental drive robot with two wheels using 4 PWM lines. I used IBT4 drivers. There are no wheel encoders on my robot, so the scaling from the cmd_vel topic was done by trial and error. Encoders would of course make the robot velocity more reliable, however in this example encoders are not required since Odometry is provided by the T265 tracking camera.

How to make it work:

Install ROS & create a Catkin Workspace. I used ROS Melodic on Ubuntu 18.04 on both my Jetson Nano mounted on the robot, and my workstation:

http://wiki.ros.org/melodic/Installation/Ubuntu

http://wiki.ros.org/catkin/Tutorials/create_a_workspace

Install the Intel Realsense Dev kit and ROS drivers:

https://github.com/IntelRealSense/librealsense/blob/development/doc/distribution_linux.md

https://github.com/IntelRealSense/realsense-ros

Install the LIDAR ROS node, I used an RPLIDAR A1:

https://github.com/Slamtec/rplidar_ros

Install the ROS navigation stack, and GMapping:

https://github.com/ros-planning/navigation

https://github.com/ros-perception/slam_gmapping

Install the ROSserial node:

https://github.com/ros-drivers/rosserial

You'll also need some way to drive the robot manually. I have a ROS remote, ut you can use Keyboard teleop:

https://github.com/ros-teleop/teleop_twist_keyboard

I repurposed the Really Useful Robot navigation code for my robot.

https://github.com/XRobots/ReallyUsefulRobot/tree/main/ROS/rur_navigation

Since the robot is not using wheel Odometry, one thing will need to be changed in move_base.launch to match the Odom topic fromt he camera. On line 4:

change: default="odom"
to: default="/camera/odom/sample"

https://github.com/XRobots/ReallyUsefulRobot/blob/main/ROS/rur_navigation/launch/move_base.launch

Lanuch the following nodes. The last one launches the ROSserial node to communicate with the Arduino controlling the robot hardware.

<code>roslaunch rplidar_ros rplidar.launch</code>

<code>roslaunch realsense2_camera rs_t265.launch</code>

<code>rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0</code>

I pubished three transforms to stick everything together (yes they should be in a URDF file):

<code>rosrun tf static_transform_publisher 0.0 0.0 0.2 3.141592 0.0 0.0 camera_link laser 100</code>

<code>rosrun tf static_transform_publisher 0.0 0.0 0.0 0.0 0.0 0.0 odom camera_odom_frame 100</code>

<code>rosrun tf static_transform_publisher -0.09 0.0 0.0 0.0 0.0 0.0 camera_link base_link 100</code>

Run GMapping:

<code>rosrun gmapping slam_gmapping scan:=scan</code>

Run RVIZ and add: TF, Laser, Map (and connect to the relevent topics). Driving the robot manually should produce the map. Save the map with:

<code>rosrun map_server map_saver -f ~/map</code>

Launch the modified RUR robot navigation node wch now looks at the Odom topic from the camera and the map:

<code>roslaunch rur_navigation rur_navigation.launch map_file:=$HOME/map.yaml</code>

