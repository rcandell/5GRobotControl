#include <boost/system/config.hpp>
#include <boost/program_options.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <utility>

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

// printing operator
std::ostream& operator<< (std::ostream& lhs, const VelocityControllerMessage& rhs);

//serialization operators
std::istringstream& operator>> (std::istringstream& lhs, VelocityControllerMessage& rhs);
std::ostringstream& operator<< (std::ostringstream& lhs, const VelocityControllerMessage& rhs);

#define CMD_SHMEM_NAME ("cmd_shmem")



