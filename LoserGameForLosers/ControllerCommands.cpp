#include "ControllerCommands.h"
#include "stdafx.h"

void EndRoundCommand::execute(Entity * entity)
{
	processor_->debug_end_round();
}
