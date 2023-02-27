#include "test/Program.h"
#include "core/Core.h"
#include "core/UniquePtr.h"

using namespace Corvus;
int32 main(int32 argc, char* argv[])
{
	UniquePtr<Program> pProgram = new Program();
	pProgram->Init();
	pProgram->Run();
	return 0;
}