#include "actions.h"
#include <stdio.h>

char get_action(char msg)
{
    switch (msg)
    {
    case 'z':
        return ACTION_MOVE_U;
    case 'q':
        return ACTION_MOVE_L;
    case 's':
        return ACTION_MOVE_D;
    case 'd':
        return ACTION_MOVE_R;
    case 'a':
        return ACTION_BOMB;
    case 'e':
        return ACTION_SPLASH;
    case 'i':
        return ACTION_TELEPORT_U;
    case 'k':
        return ACTION_TELEPORT_D;
    case 'j':
        return ACTION_TELEPORT_L;
    case 'l':
        return ACTION_TELEPORT_R;
    case 'g':
        return ACTION_DASH_U;
    case 'v':
        return ACTION_DASH_L;
    case 'b':
        return ACTION_DASH_D;
    case 'n':
        return ACTION_DASH_R;
    case 'o':
        return ACTION_STILL;
    default:
        return ACTION_NONE;
    }
}