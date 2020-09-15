#include <linux/input-event-codes.h>

typedef enum KeyboardControls
{

    MoveUp = KEY_W,
    MoveLeft = KEY_A,
    MoveDown = KEY_S,
    MoveRight = KEY_D,
    Back = KEY_ESC,
    Kill = KEY_Q,
    Map = KEY_TAB,
    Action = KEY_SPACE,
    Report = KEY_R

} KeyboardControls;

typedef enum GamePadControls {

    // GMoveUp,
    // GMoveLeft,
    // GMoveDown,
    // GMoveRight,
    GKill = 2, // 2 IS B
    GAction = 1, // 1 IS A
    GBack = 5, // 5 IS RT
    GMap = 0, // 0 IS X
    GClick = 4, // 4 IS LT
    GReport = 3 // 3 IS Y

} GamePadControls;