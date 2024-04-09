#include <iostream>

// structure for a command message from the client
typedef struct {

  // velocities for movement in workplane
  // Comes from LEFT Thumb Controller
  float v_horizontal;     // LEFT/RIGHT
  float v_vertical;       // UP/DN

  // velocities for movement forward and backwards
  // comes from left and right trigger buttons
  float v_fwd;      // Forward is positive, backward is negative

  // velocities for rotation of end effector
  // Comes from RIGHT Thumb Controller
  float thetadot_horizontal;
  float thetadot_vertical;

  // indication messages
  // Comes from the buttons
  bool  btnA, btnB, btnX, btnY;

} VelocityControllerMessage;

std::ostream& operator<< (std::ostream& lhs, const VelocityControllerMessage& rhs);

