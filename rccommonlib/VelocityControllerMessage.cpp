#include <common.h>

std::ostream& operator<< (std::ostream& lhs, const VelocityControllerMessage& rhs)
{
    lhs << "VelocityControllerMessage" << std::endl
        << "Horiztonal velocity:  " << rhs.v_horizontal << std::endl
        << "Vertical velocity:  " << rhs.v_vertical << std::endl
        << "Forward velocity:  " << rhs.v_fwd << std::endl
        << "Vertiical angular velocity:  " << rhs.thetadot_vertical << std::endl
        << "Horizontal angular velocity:  " << rhs.thetadot_horizontal << std::endl
        << "Button A:  " << rhs.btnA << std::endl
        << "Button B:  " << rhs.btnB << std::endl
        << "Button X:  " << rhs.btnX << std::endl
        << "Button Y:  " << rhs.btnY;
    return lhs;
}

#define VELCTLMSG_DELIM (' ')
std::istringstream& operator>>(std::istringstream& lhs, VelocityControllerMessage& rhs)
{
    std::string token;

    int ii = 0;
    while(std::getline(lhs, token, VELCTLMSG_DELIM))
    {
        switch(ii)
        {
            case 0:
                rhs.v_horizontal = std::stof(token);
            case 1:
                rhs.v_vertical = std::stof(token);
            case 2:
                rhs.v_fwd = std::stof(token);
            case 3:
                rhs.thetadot_horizontal = std::stof(token);
            case 4:
                rhs.thetadot_vertical = std::stof(token);
            case 5:
                rhs.btnA = std::stof(token);
            case 6:
                rhs.btnB = std::stof(token);
            case 7:
                rhs.btnX = std::stof(token);
            case 8:
                rhs.btnY = std::stof(token);
            default:
                break;
        }
        ii++;
    }

    return lhs;
}

std::ostringstream& operator<< (std::ostringstream& lhs, const VelocityControllerMessage& rhs)
{
    lhs <<  rhs.v_horizontal << VELCTLMSG_DELIM <<
            rhs.v_vertical << VELCTLMSG_DELIM <<
            rhs.v_fwd << VELCTLMSG_DELIM <<

            rhs.thetadot_horizontal << VELCTLMSG_DELIM <<
            rhs.thetadot_vertical << VELCTLMSG_DELIM <<

            rhs.btnA << VELCTLMSG_DELIM <<
            rhs.btnB << VELCTLMSG_DELIM <<
            rhs.btnX << VELCTLMSG_DELIM <<
            rhs.btnY << '\0';

    return lhs;
}
