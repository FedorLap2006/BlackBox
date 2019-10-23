#include <BlackBox/IGame.hpp>
#include <BlackBox/ISystem.hpp>
//#include <BlackBox/Utils.hpp>
#include <BlackBox/ILog.hpp>

#include <iostream>
#include <filesystem>

/*##############################################*/


/*----------------------------------------------*/


/*##############################################*/

using namespace std;

int main(int argc, char *argv[]) {
  string path;
  bool debug = false;
  if (argc > 1) {
    if (string(argv[1]) == "-debug")
      debug = true;
  }

	//std::filesystem::current_path("../../");
	cout << "current path: " << std::filesystem::current_path() << endl;

  //chdir((path = getBasePath(string(argv[0]))).c_str());
  //path = getBasePath(string(argv[0]));
	SSystemInitParams params;
	params.sLogFileName = "log.txt";
  ISystem*pSystem = CreateSystemInterface(params);
  if (!pSystem->Init())
  {
    pSystem->Release();
    return EXIT_FAILURE;
  }
	pSystem->GetILog()->Log("[OK] ISystem created\n");
	pSystem->GetILog()->Log("[INFO] Current working directory: %s\n", path.c_str());
  pSystem->Start();
	pSystem->Release();

  return 0;
}
