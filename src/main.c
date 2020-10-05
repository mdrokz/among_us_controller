#include <stdio.h>

#ifdef __CYGWIN__

#include "../headers/windows/keyboard.h"
#include "../headers/windows/controls.h"
#include <windows.h>
#include <Xinput.h>
// #include <winerror.h>

#endif

#ifdef _WIN32

#include "../headers/windows/keyboard.h"
#include "../headers/windows/controls.h"
#include <windows.h>
#include <Xinput.h>

#endif

#ifdef linux

#include "../headers/linux/keyboard.h"
#include "../headers/linux/controls.h"

#endif

#ifdef __CYGWIN__
int main(void)
{
    DWORD dwResult;
    for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        // Simply get the state of the controller from XInput.
        dwResult = XInputGetState(i, &state);

        if (dwResult == ERROR_SUCCESS)
        {
            // Controller is connected
            printf("1");
        }
        else if(dwResult == ERROR_DEVICE_NOT_CONNECTED)
        {
            // Controller is not connected
            printf("2");
        }
    }
}
#endif

#ifdef _WIN32
int main(void)
{
    printf("hello world");
}
#endif

#ifdef linux

#define GAMEPAD "/dev/input/js0"

int gamepad_fd;

int main(void)
{
    MouseInit();
    KeyboardInit();

    /* Move the mouse diagonally, 5 units per axis */
    // struct input_event evx = EVENT(EV_REL, REL_X, 5);
    // struct input_event evy = EVENT(EV_REL, REL_Y, 5);

    // struct input_event evs[] = {EVENT(EV_REL, REL_X, 5), EVENT(EV_REL, REL_Y, 5)};

    struct js_event j_evs;

    gamepad_fd = open(GAMEPAD, O_RDONLY | O_NONBLOCK);

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

                    ProcessDPADEvents(j_evs, gamepad_fd);

                    ProcessGamepadAxisEvents(j_evs);
                }
                else if (j_evs.type == JS_EVENT_BUTTON)
                {
                    ProcessGamepadButtonEvents(j_evs);
                }
                /* do something interesting with processed events */
            }
        }
    }
    else
    {
        printf("No Joystick detected at %s", GAMEPAD);
        return 0;
    }

    return 0;
}
#endif

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