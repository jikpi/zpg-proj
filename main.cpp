#include "Application/Engine.h"

int main() {

    std::shared_ptr<Engine> MyEngine = std::make_shared<Engine>();
    MyEngine->InitializeBase();
    MyEngine->InitializeRendering();

    MyEngine->PrintVersionInfo();
    MyEngine->Run();

    MyEngine->KillWindow();
    glfwTerminate();
    return EXIT_SUCCESS;
}