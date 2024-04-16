# 5GRobotControl
This code will serve as an example code base for the implementation of a teleoperation client server architecture. Robot shall be controlled by a joystick utilizing the Xinput.  Velocities are streamed to the server demonstrated by this project.

This demonstation sets up a UDP server for receiving the Xinput vector from a remote client.  A sample client program is included.  Messages as serialized as strings for transmission to enable cross-platform interoperation.

# Dependencies
This code requires Boost 1.84 or compatible.  The software design utilizes the program_options and asio libraries from Boost.



