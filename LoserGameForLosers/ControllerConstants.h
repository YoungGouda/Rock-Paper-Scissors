#pragma once

struct Input
{
	Input(const int command, const int keys)
		: command(command), keys(keys)
	{}
	int command;
	int keys;
};

