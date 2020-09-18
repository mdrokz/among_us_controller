#include <linux/input-event-codes.h>
#include <linux/joystick.h>
#include "../headers/keyboard.h"

#define EVENT(type, code, v) \
    ((struct input_event){(struct timeval){0, 0}, type, code, v})

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

typedef enum GamePadControls
{

    GMoveY = 5,
    GMoveX = 4,
    GKill = 2,   // 2 IS B
    GAction = 1, // 1 IS A
    GBack = 5,   // 5 IS RT
    GMap = 0,    // 0 IS X
    GClick = 4,  // 4 IS LT
    GReport = 3  // 3 IS Y

} GamePadControls;

void ProcessGamepadAxisEvents(struct js_event j_evs)
{
    KeyboardControls kctrl[] = {MoveRight, MoveLeft, MoveDown, MoveUp};

    // printf("AXIS: %d", j_evs.number);
    // printf("VALUE: %d", j_evs.value);

    switch (j_evs.number)
    {

    case 0:
    {

        if (j_evs.value > 0)
        {

            WriteKeyboardEvent(EVENT(EV_KEY, MoveRight, 1));
        }
        else if (j_evs.value == 0)
        {
            WriteKeyboardEvent(EVENT(EV_KEY, kctrl[0], 0));
            WriteKeyboardEvent(EVENT(EV_KEY, kctrl[1], 0));
        }
        else
        {
            WriteKeyboardEvent(EVENT(EV_KEY, MoveLeft, 1));
        }
    }
    break;

    case 1:
    {
        if (j_evs.value > 0)
        {
            WriteKeyboardEvent(EVENT(EV_KEY, MoveDown, 1));
        }
        else if (j_evs.value == 0)
        {
            WriteKeyboardEvent(EVENT(EV_KEY, kctrl[2], 0));
            WriteKeyboardEvent(EVENT(EV_KEY, kctrl[3], 0));
        }
        else
        {
            WriteKeyboardEvent(EVENT(EV_KEY, MoveUp, 1));
        }
    }
    break;

    case 2:
    {
        if (j_evs.value > 0)
        {
            WriteMouseEvents((struct input_event[]){EVENT(EV_REL, REL_X, 5)});
        }
        else
        {
            WriteMouseEvents((struct input_event[]){EVENT(EV_REL, REL_X, -5)});
        }
    }
    break;

    case 3:
    {
        if (j_evs.value > 0)
        {
            WriteMouseEvents((struct input_event[]){EVENT(EV_REL, REL_Y, 5)});
        }
        else
        {
            WriteMouseEvents((struct input_event[]){EVENT(EV_REL, REL_Y, -5)});
        }
    }
    break;
    }
}

void ProcessGamepadButtonEvents(struct js_event j_evs)
{
    switch (j_evs.number)
    {

    case GKill:
    {
        if (j_evs.value)
        {
            WriteKeyboardEvent(EVENT(EV_KEY, Kill, 1));
        }
        else
        {
            WriteKeyboardEvent(EVENT(EV_KEY, Kill, 0));
        }
    }
    break;

    case GBack:
    {
        if (j_evs.value)
        {
            WriteKeyboardEvent(EVENT(EV_KEY, Back, 1));
        }
        else
        {
            WriteKeyboardEvent(EVENT(EV_KEY, Back, 0));
        }
    }
    break;

    case GAction:
    {
        if (j_evs.value)
        {
            WriteKeyboardEvent(EVENT(EV_KEY, Action, 1));
        }
        else
        {
            WriteKeyboardEvent(EVENT(EV_KEY, Action, 0));
        }
    }
    break;

    case GMap:
    {
        if (j_evs.value)
        {
            WriteKeyboardEvent(EVENT(EV_KEY, Map, 1));
        }
        else
        {
            WriteKeyboardEvent(EVENT(EV_KEY, Map, 0));
        }
    }
    break;

    case GClick:
    {
        if (j_evs.value)
        {
            struct input_event evs[] = {EVENT(EV_KEY, BTN_LEFT, 1)};

            WriteMouseEvents(evs);
        }
        else
        {
            struct input_event evs[] = {EVENT(EV_KEY, BTN_LEFT, 0)};

            WriteMouseEvents(evs);
        }
    }
    break;

    case GReport:
    {
        if (j_evs.value)
        {
            // (struct js_event[]){(struct js_event) {}};
            WriteKeyboardEvent(EVENT(EV_KEY, Report, 1));
        }
        else
        {
            WriteKeyboardEvent(EVENT(EV_KEY, Report, 0));
        }
    }
    break;
    }
}

void ProcessDPADEvents(struct js_event j_evs, int gamepad_fd)
{
    KeyboardControls kctrl[] = {MoveRight, MoveLeft, MoveDown, MoveUp};

    struct js_event j_evs2;

    if (j_evs.number == GMoveX)
    {

        if (j_evs.value > 0)
        {
            WriteKeyboardEvent(EVENT(EV_KEY, MoveRight, 1));
        }
        else if (j_evs.value < 0)
        {
            WriteKeyboardEvent(EVENT(EV_KEY, MoveLeft, 1));
        }
        else if (j_evs.value == 0)
        {
            WriteKeyboardEvent(EVENT(EV_KEY, kctrl[0], 0));
            WriteKeyboardEvent(EVENT(EV_KEY, kctrl[1], 0));
        }
    }
    else if (j_evs.number == GMoveY)
    {
        if (j_evs.value > 0)
        {
            WriteKeyboardEvent(EVENT(EV_KEY, MoveDown, 1));
        }
        else if (j_evs.value < 0)
        {
            WriteKeyboardEvent(EVENT(EV_KEY, MoveUp, 1));
        }
        else if (j_evs.value == 0)
        {
            WriteKeyboardEvent(EVENT(EV_KEY, kctrl[2], 0));
            WriteKeyboardEvent(EVENT(EV_KEY, kctrl[3], 0));
        }
    }
}