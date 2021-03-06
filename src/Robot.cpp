///////////////////////////////////////////////////////////////////////////////
//
// Robot.cpp
//
//  Created on: Jan 7, 2017
//      Author: Silas A.
//
///////////////////////////////////////////////////////////////////////////////

#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "CommandBase.h"

#include "Commands/Autonomous/AutoShoot.h"
#include "Commands/Autonomous/AutoCrossLine.h"
#include "Commands/Autonomous/AutoPegGear.h"
#include "Commands/Autonomous/AutoPickupAndPeg.h"
#include "Commands/Autonomous/AutoPickupGear.h"

class Robot: public frc::IterativeRobot
{
private:
	std::unique_ptr<frc::Command> autonomousCommand;
	frc::SendableChooser<frc::Command*> autoModes;
	frc::SendableChooser<int> positions;

	frc::LiveWindow* lw;

public:
	void InitializeSubsystems(frc::Preferences* prefs)
	{
		CommandBase::drive.get()->Initialize(prefs);
		CommandBase::shooter.get()->Initialize(prefs);
		CommandBase::gearCollector.get()->Initialize(prefs);
		CommandBase::climber.get()->Initialize(prefs);
		CommandBase::fuelCollector.get()->Initialize(prefs);
		CommandBase::lights.get()->Initialize(prefs);
		CommandBase::visionManager.get()->Initialize(prefs);
	}

	void UpdateDashboard(bool verbose = false)
	{
		CommandBase::drive.get()->DashboardOutput(verbose);
		CommandBase::shooter.get()->DashboardOutput(verbose);
		CommandBase::gearCollector.get()->DashboardOutput(verbose);
		CommandBase::climber.get()->DashboardOutput(verbose);
		CommandBase::fuelCollector.get()->DashboardOutput(verbose);
		CommandBase::lights.get()->DashboardOutput(verbose);
		CommandBase::visionManager.get()->DashboardOutput(verbose);
	}

	void RobotInit() override
	{
		InitializeSubsystems(CommandBase::oi.get()->GetPrefs());

		positions.AddObject("1", 1);
		positions.AddObject("2", 2);
		positions.AddObject("3", 3);
		frc::SmartDashboard::PutData("Postion", &positions);

		autoModes.AddObject("Cross Baseline", new AutoCrossLine());
		autoModes.AddObject("Peg Gear", new AutoPegGear());
		autoModes.AddObject("Pickup and Peg Gear", new AutoPickupAndPeg());
		autoModes.AddObject("Pickup Gear", new AutoPickupGear());
		autoModes.AddObject("Shoot", new AutoShoot());
		frc::SmartDashboard::PutData("Auto Modes", &autoModes);

		lw = frc::LiveWindow::GetInstance();
		lw->Run();
	}

	void RobotPeriodic() override
	{
		UpdateDashboard();
	}

	/**
	 * This function is called once each time the robot enters Disabled mode.
	 * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
	 */
	void DisabledInit() override
	{

	}

	void DisabledPeriodic() override
	{
		frc::Scheduler::GetInstance()->Run();
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString code to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional commands to the
	 * chooser code above (like the commented example) or additional comparisons
	 * to the if-else structure below with additional strings & commands.
	 */
	void AutonomousInit() override
	{
		autonomousCommand.reset(autoModes.GetSelected());

		if (autonomousCommand.get() != nullptr)
		{
			autonomousCommand->Start();
		}
	}

	void AutonomousPeriodic() override
	{
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override
	{
		if (autonomousCommand != nullptr)
		{
			autonomousCommand->Cancel();
		}
	}

	void TeleopPeriodic() override
	{
		frc::Scheduler::GetInstance()->Run();
	}

	void TestPeriodic() override
	{
		frc::LiveWindow::GetInstance()->Run();
	}


};

START_ROBOT_CLASS(Robot)
