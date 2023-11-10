#include <SOIL/SOIL.h>
#include "Application/Engine.h"

int main() {

    std::shared_ptr<Engine> MyEngine = std::make_shared<Engine>();
    MyEngine->Initialize();
    MyEngine->TestLaunch();

    MyEngine->PrintVersionInfo();
    MyEngine->Run();

    MyEngine->KillWindow();
    glfwTerminate();
    return EXIT_SUCCESS;
}