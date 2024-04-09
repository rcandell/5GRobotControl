#include <common.h>


std::ostream& operator<< (std::ostream& lhs, const VelocityControllerMessage& rhs)
{
    lhs << "VelocityControllerMessage" << std::endl
        << "Vertical velocity:  " << rhs.v_vertical << std::endl
        << "Horiztonal velocity:  " << rhs.v_horizontal << std::endl
        << "Forward velocity:  " << rhs.v_fwd << std::endl
        << "Vertiical angular velocity:  " << rhs.thetadot_vertical << std::endl
        << "Horizontal angular velocity:  " << rhs.thetadot_horizontal << std::endl
        << "Button A:  " << rhs.btnA << std::endl
        << "Button B:  " << rhs.btnB << std::endl
        << "Button X:  " << rhs.btnX << std::endl
        << "Button Y:  " << rhs.btnY;
    return lhs;
}
