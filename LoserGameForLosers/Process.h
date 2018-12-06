#pragma once
#include <functional>
#include <utility>

class Process
{
public:
	virtual ~Process() = default;
	virtual bool do_work() = 0;
	virtual float work_done() = 0;
};

class AndMultiProcessor : public Process
{
public:
	std::vector<Process *> and_processes;

	AndMultiProcessor(std::vector<Process *> processes)
		: and_processes(processes)
	{}

	bool do_work() override
	{
		auto work_complete = true;
		
		for (auto& a : and_processes)
		{
			work_complete &= a->do_work();
		}

		return work_complete;
	}

	float work_done() override
	{
		auto work_percentage = 0.0f;

		for (auto& a : and_processes)
		{
			work_percentage += a->work_done();
		}
		
		if (and_processes.size() > 0)
			work_percentage /= and_processes.size();
		else
			work_percentage = 1.0f;
		
		return work_percentage;
	}
};

class OrMultiProcessor : public Process
{
public:
	std::vector<Process *> or_processes;
	OrMultiProcessor(std::vector<Process *> processes )
		: or_processes(processes)
	{}

	bool do_work() override
	{
		auto work_complete = true;

		if (or_processes.size() > 0)
			work_complete = false;

		for (auto& o : or_processes)
		{
			work_complete |= o->do_work();
		}
		
		return work_complete;
	}

	float work_done() override
	{
		auto work_percentage = 1.0f;

		if (or_processes.size() > 0)
			work_percentage = 0.0f;

		for (auto& o : or_processes)
		{
			work_percentage = std::max(work_percentage, o->work_done());
		}

		return work_percentage;
	}
};