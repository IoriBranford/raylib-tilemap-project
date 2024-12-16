#include <engine.h>
#include <game.h>

int main() {
    InitEngine();
    InitGame();

    RunEngine();

    CloseGame();
    StopEngine();
    return 0;
}