#include <BlackBox/IGame.hpp>
#include <BlackBox/IEngine.hpp>
#include <BlackBox/Utils.hpp>

#include <iostream>

/*##############################################*/


/*----------------------------------------------*/


/*##############################################*/

using namespace std;

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
int WINAPI WinMain(
      HINSTANCE hInstance,
      HINSTANCE hPrevInstance,
      PSTR szCmdLine,
      int iCmdShow) 
{
  int argc;
  char **argv;
  argv = CommandLineToArgvA(szCmdLine, &argc);
#else
int main(int argc, char *argv[]) {
#endif
  string path;
  bool debug = false;
  if (argc > 1) {
    if (string(argv[1]) == "-debug")
      debug = true;
  }

  //chdir((path = getBasePath(string(argv[0]))).c_str());
  cout << path << endl;

  IEngine *pEngine = CreateIEngine(nullptr);
  cout << "IEngine created" << endl;
  if (pEngine->Init()){
    pEngine->Start();
  }

  return 0;
}
