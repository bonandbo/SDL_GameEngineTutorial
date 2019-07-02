#pragma once

static size_t g_lastLogID = 0;

class MyLog
{
public:
	MyLog();
	~MyLog();

	void LogToDo(const char* message);
	void LogError(const char* message);
	void LogWarning(const char* message);
private:
	size_t m_ID;
};
