#include <stdio.h>

#include <linux/uinput.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <linux/joystick.h>


void MouseInit();


void WriteMouseEvents(struct input_event ev[]);