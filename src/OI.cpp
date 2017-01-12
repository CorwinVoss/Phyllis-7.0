///////////////////////////////////////////////////////////////////////////////
//
// OI.cpp
//
//  Created on: Jan 7, 2017
//      Author: Silas A.
//
///////////////////////////////////////////////////////////////////////////////

#include "OI.h"
#include "RobotMap.h"

#include <WPILib.h>

OI::OI() :
	m_driver(new Joystick(JOY_DRIVER_PORT))
{
#ifdef CODRIVER
	m_coDriver = new Joystick(JOY_CODRIVER_PORT);
#endif // CODRIVER
}
