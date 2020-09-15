#include "../headers/keyboard.h"
#include "../headers/controls.h"
// input_event composite literal macro
#define EVENT(type, code, v) \
    ((struct input_event){(struct timeval){0, 0}, type, code, v})

#define GAMEPAD "/dev/input/js0"

int main(void)
{
    MouseInit();
    KeyboardInit();

    /* Move the mouse diagonally, 5 units per axis */
    // struct input_event evx = EVENT(EV_REL, REL_X, 5);
    // struct input_event evy = EVENT(EV_REL, REL_Y, 5);

    // struct input_event evs[] = {EVENT(EV_REL, REL_X, 5), EVENT(EV_REL, REL_Y, 5)};

    struct js_event j_evs;

    int gamepad_fd = open(GAMEPAD, O_RDONLY | O_NONBLOCK);

    int exists = access(GAMEPAD, F_OK);

    // check if the file exists before reading it as a fd
    if (exists != -1)
    {
        // run event loop
        while (1)
        {
            while (read(gamepad_fd, &j_evs, sizeof(j_evs)) > 0)
            {
                // process_event(e);
                if (j_evs.type == JS_EVENT_INIT)
                {
                    printf("init event");
                }
                else if (j_evs.type == JS_EVENT_AXIS)
                {
                    printf("axis event");
                }
                else if (j_evs.type == JS_EVENT_BUTTON)
                {
                    printf("button event");
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
                            WriteKeyboardEvent(EVENT(EV_KEY, BTN_LEFT, 1));
                        }
                        else
                        {
                            WriteKeyboardEvent(EVENT(EV_KEY, BTN_LEFT, 0));
                        }
                    }
                    break;

                    case GReport:
                    {
                        if (j_evs.value)
                        {
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
            }
            /* do something interesting with processed events */
        }
    }
    else
    {
        printf("No Joystick detected at %s", GAMEPAD);
        return 0;
    }

    return 0;
}

/* 
 while (i--)
    {
        //   emit(fd, EV_REL, REL_X, 5);
        //   emit(fd, EV_REL, REL_Y, 5);
        //   emit(fd, EV_SYN, SYN_REPORT, 0);
        //   usleep(15000);
        WriteMouseEvents(evs);
        usleep(15000);
    }

*/