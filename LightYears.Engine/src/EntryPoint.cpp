#include "EntryPoint.h"
#include "framework/Application.h"

int main()
{
	auto application = GetApplication();
	application->Run();
	delete application;
}