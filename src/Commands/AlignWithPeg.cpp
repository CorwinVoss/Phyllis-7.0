#include "AlignWithPeg.h"
#include "WaitForPeg.h"

#include <Preferences.h>

AlignWithPeg::AlignWithPeg(frc::JoystickButton* abortBtn)
{
	Requires(drive.get());
	Requires(visionManager.get());
	Requires(gearCollector.get());

	frc::Preferences* prefs = oi.get()->GetPrefs();

	m_pid = new frc::PIDController(
			prefs->GetDouble("align_drive_p"),
			prefs->GetDouble("align_drive_i"),
			prefs->GetDouble("align_drive_d"),
			drive.get(),
			visionManager.get());

	m_abortBtn = abortBtn;
}

AlignWithPeg::~AlignWithPeg()
{
	delete m_pid;
}

void AlignWithPeg::Initialize()
{
	m_pid->SetTolerance(ALIGN_PEG_TOLERANCE);
	visionManager.get()->SwitchCamera(CS_CAM_PEG_PORT);
	drive.get()->SetTalonMode(CANTalon::TalonControlMode::kPositionMode);
}

void AlignWithPeg::Execute()
{
	m_pid->SetSetpoint(0);
}

bool AlignWithPeg::IsFinished()
{
	return m_pid->OnTarget() && frc::SmartDashboard::GetNumber("Distance", -2);
}

void AlignWithPeg::End()
{
}

void AlignWithPeg::Interrupted()
{
}
