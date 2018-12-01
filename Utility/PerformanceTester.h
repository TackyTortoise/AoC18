#pragma once

class PerformanceTester
{
public:
	PerformanceTester();
	~PerformanceTester();

	static void Start()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	static void Stop()
	{
		stop = std::chrono::high_resolution_clock::now();
	}
	static void Log()
	{
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;
	}
	static void StopAndLog() { Stop(); Log(); }

private:
	static std::chrono::steady_clock::time_point start;
	static std::chrono::steady_clock::time_point stop;
};