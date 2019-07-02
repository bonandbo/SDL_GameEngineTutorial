#include "MyLog.h"
#include <iostream>

extern size_t g_lastLogID;

MyLog::MyLog()
{
	m_ID = g_lastLogID++;
}

MyLog::~MyLog()
{
}

void MyLog::LogToDo(const char* message)
{
	printf("=====================\n");
	printf("@TODO\n");
	printf("=====================\n");
}

void MyLog::LogError(const char* message)
{

}

void MyLog::LogWarning(const char* message)
{

}