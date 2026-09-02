#include <3ds.h>
#include <citro2d.h>
#include "core/GameManager.hpp"

int main(int argc, char **argv)
{
    GameManager GameManager;
    if (!GameManager.init()) { GameManager.exit(); return 0; }

	while (aptMainLoop())
    {
        if (!GameManager.render()) { break; }
        if (!GameManager.update()) { break; }
    }
    GameManager.exit();

	return 0;
}