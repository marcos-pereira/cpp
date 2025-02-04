/**
(C) Copyright 2019-2020 DQ Robotics Developers

This file is part of DQ Robotics.

    DQ Robotics is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DQ Robotics is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with DQ Robotics.  If not, see <http://www.gnu.org/licenses/>.

Contributors:
- Murilo M. Marinho (murilo@nml.t.u-tokyo.ac.jp)
*/

#ifndef DQ_ROBOTICS_KUKAYOUBOT_DH_H
#define DQ_ROBOTICS_KUKAYOUBOT_DH_H

#include<dqrobotics/robots/KukaYoubotRobot.h>
#include<dqrobotics/utils/DQ_Constants.h>
#include<dqrobotics/robot_modeling/DQ_HolonomicBase.h>
#include<dqrobotics/robot_modeling/DQ_SerialManipulatorDH.h>
#include<memory>

namespace DQ_robotics
{

DQ_SerialWholeBody KukaYoubotRobot::kinematics()
{
    const double pi2 = pi/2.0;
    MatrixXd arm_DH_matrix(5,5);
    arm_DH_matrix <<    0,    pi2,       0,      pi2,        0,
                    0.147,      0,       0,        0,    0.218,
                        0,  0.155,   0.135,        0,        0,
                      pi2,      0,       0,      pi2,        0,
                        0,      0,       0,        0,        0;

    auto arm = std::make_shared<DQ_SerialManipulatorDH>(DQ_SerialManipulatorDH(arm_DH_matrix));
    auto base = std::make_shared<DQ_HolonomicBase>(DQ_HolonomicBase());

    DQ x_bm= 1 + E_*0.5*(0.22575*i_ + 0.1441*k_);

    base->set_frame_displacement(x_bm);

    DQ_SerialWholeBody kin(std::static_pointer_cast<DQ_Kinematics>(base));
    kin.add(std::static_pointer_cast<DQ_Kinematics>(arm));

    return kin;
}

}

#endif
