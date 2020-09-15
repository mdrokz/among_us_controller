#include <stdio.h>

#include <linux/uinput.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <string.h>

#include "../headers/controls.h"

#define LENGTH(x) (sizeof(*x) / sizeof((x)[0]))

static int keyboard_fd = 0;

void KeyboardInit()
{
    struct uinput_setup usetup;

    keyboard_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    /* enable mouse button left and relative events */
    ioctl(keyboard_fd, UI_SET_EVBIT, EV_KEY);  // enabling key events
    ioctl(keyboard_fd, UI_SET_KEYBIT, Action); // action key in among us
    ioctl(keyboard_fd, UI_SET_KEYBIT, Report); // report key in among us
    ioctl(keyboard_fd, UI_SET_KEYBIT, Kill);   // kill key in among us
    ioctl(keyboard_fd, UI_SET_KEYBIT, Map);    // map key in among us
    ioctl(keyboard_fd, UI_SET_KEYBIT, Back); // esc key in among us

    // movement keys || WASD keys
    ioctl(keyboard_fd, UI_SET_KEYBIT, MoveUp);
    ioctl(keyboard_fd, UI_SET_KEYBIT, MoveDown);
    ioctl(keyboard_fd, UI_SET_KEYBIT, MoveLeft);
    ioctl(keyboard_fd, UI_SET_KEYBIT, MoveRight);

    memset(&usetup, 0, sizeof(usetup)); // set all bits of usetup to 0
    usetup.id.bustype = BUS_USB;        // set bustype of this device
    usetup.id.vendor = 0x1234;          /* sample vendor */
    usetup.id.product = 0x5678;         /* sample product */
    strcpy(usetup.name, "Keyboard1");

    ioctl(keyboard_fd, UI_DEV_SETUP, &usetup);
    ioctl(keyboard_fd, UI_DEV_CREATE);

    sleep(1);
}

void WriteKeyboardEvents(struct input_event ev[])
{
    struct input_event evr = {{0, 0}, EV_SYN, SYN_REPORT, 0};

    int event_length = LENGTH(ev);

    if (event_length > 1)
    {
        for (int i = 0; i < event_length; i++)
        {
            write(keyboard_fd, &ev[i], sizeof(ev[i]));
            write(keyboard_fd, &evr, sizeof(evr));
        }
    }
    else
    {
        write(keyboard_fd, &ev[0], sizeof(ev[0]));
        write(keyboard_fd, &evr, sizeof(evr));
    }
}

WriteKeyboardEvent(struct input_event ev)
{
    struct input_event evr = {{0, 0}, EV_SYN, SYN_REPORT, 0};

    write(keyboard_fd, &ev, sizeof(ev));
    write(keyboard_fd, &evr, sizeof(evr));
}