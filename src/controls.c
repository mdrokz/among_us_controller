#include <linux/input-event-codes.h>

typedef enum KeyboardControls
{

    MoveUp = KEY_W,
    MoveLeft = KEY_A,
    MoveDown = KEY_S,
    MoveRight = KEY_D,
    Kill = KEY_Q,
    Action = KEY_SPACE,
    Report = KEY_R

} KeyboardControls;

typedef enum GamePadControls {

    GMoveUp = KEY_W,
    GMoveLeft = KEY_A,
    GMoveDown = KEY_S,
    GMoveRight = KEY_D,
    GKill = KEY_Q,
    GAction = KEY_SPACE,
    GReport = KEY_R

} GamePadControls;