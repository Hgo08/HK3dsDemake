#include <3ds.h>
#include <citro2d.h>
#include "core/GameManager.hpp"

int main(int argc, char **argv)
{
    GameManager GameManager;
    if (!GameManager.init()) { GameManager.exit(); return 0; }

	while (aptMainLoop())
    {
        if (!GameManager.render()) { GameManager.exit();  break; }
        if (!GameManager.update()) { GameManager.exit();  break; }
    }
    GameManager.exit();

	return 0;
}