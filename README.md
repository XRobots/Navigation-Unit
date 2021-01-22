# Navigation-Unit

Drop-in naviation unit for ny robot using an RPLIDAR A1 and and Intel Realsense T265 Tracking Camera.

Code in the Arduino directory is to control a differental drive robot with two wheels using 4 PWM lines. I used IBT4 drivers. There are no wheel encoders on my robot, so the scaling from the cmd_vel topic was done by trial and error. Encoders would of course make the robot velocity more reliable, however in this example encoders are not required since Odometry is provided by the T265 tracking camera.
