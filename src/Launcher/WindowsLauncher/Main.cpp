#include <BlackBox/Core/Platform/Platform.hpp>
#include <BlackBox/System/ISystem.hpp>
#include <BlackBox/System/ILog.hpp>
#include <BlackBox/Utils/smartptr.hpp>

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  int status = EXIT_FAILURE;
  string path;
  std::string cmdline;
  for (int i = 0; i < argc; i++)
  {
    cmdline = cmdline + " " + argv[i];
  }

  SSystemInitParams params;

  std::cout << "Current path is " << fs::current_path() << '\n';

  time_t t = time(nullptr);
  std::stringstream ss;
  ss << "logs/" << std::put_time(std::localtime(&t), "%H-%M-%S") << ".txt";
  params.sLogFileName = _strdup(ss.str().c_str());

  snprintf(params.szSystemCmdLine, 512, "%s", cmdline.c_str());
  ISystem* pSystem = CreateSystemInterface(params);
  if (pSystem)
  {
    pSystem->GetILog()->Log("[OK] ISystem created\n");
    pSystem->GetILog()->Log("[INFO] Current working directory: %s\n", path.c_str());
    pSystem->Start();
    status = EXIT_SUCCESS;
  }
  pSystem->Release();

  return status;
}
