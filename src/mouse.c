#include <stdio.h>

#include <linux/uinput.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <string.h>

#define LENGTH(x) (sizeof(*x) / sizeof((x)[0]))

static int mouse_fd = 0;

void MouseInit()
{
    struct uinput_setup usetup;

    mouse_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    /* enable mouse button left and relative events */
    ioctl(mouse_fd, UI_SET_EVBIT, EV_KEY);    // enabling key events
    ioctl(mouse_fd, UI_SET_KEYBIT, BTN_LEFT); //

    ioctl(mouse_fd, UI_SET_EVBIT, EV_REL);
    ioctl(mouse_fd, UI_SET_RELBIT, REL_X);
    ioctl(mouse_fd, UI_SET_RELBIT, REL_Y);

    memset(&usetup, 0, sizeof(usetup)); // set all bits of usetup to 0
    usetup.id.bustype = BUS_USB;        // set bustype of this device
    usetup.id.vendor = 0x1234;          /* sample vendor */
    usetup.id.product = 0x5678;         /* sample product */
    strcpy(usetup.name, "Mouse1");

    ioctl(mouse_fd, UI_DEV_SETUP, &usetup);
    ioctl(mouse_fd, UI_DEV_CREATE);

    sleep(1);
}

void WriteMouseEvents(struct input_event ev[])
{

    struct input_event evr = {{0, 0}, EV_SYN, SYN_REPORT, 0};

    int event_length = LENGTH(ev);

    if (event_length > 1)
    {
        for (int i = 0; i < event_length; i++)
        {
            write(mouse_fd, &ev[i], sizeof(ev[i]));
        }
        write(mouse_fd, &evr, sizeof(evr));
    }
    else
    {
        write(mouse_fd, &ev[0], sizeof(ev[0]));
        write(mouse_fd, &evr, sizeof(evr));
    }
}

// ioctl(fd, UI_DEV_DESTROY);
//    close(fd);