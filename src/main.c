#include "../headers/mouse.h";

// input_event macro
#define EVENT(type, code, v) \
    ((struct input_event){(struct timeval){0, 0}, type, code, v})

int main(void)
{
    int i = 50;
    MouseInit();

    /* Move the mouse diagonally, 5 units per axis */
    // struct input_event evx = EVENT(EV_REL, REL_X, 5);
    // struct input_event evy = EVENT(EV_REL, REL_Y, 5);

    struct input_event evs[] = {EVENT(EV_REL, REL_X, 5), EVENT(EV_REL, REL_Y, 5)};

    while (i--)
    {
        //   emit(fd, EV_REL, REL_X, 5);
        //   emit(fd, EV_REL, REL_Y, 5);
        //   emit(fd, EV_SYN, SYN_REPORT, 0);
        //   usleep(15000);
        WriteMouseEvents(evs);
        usleep(15000);
    }
    return 0;
}
