
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>

#include "sysdeps.h"

#define   TRACE_TAG  TRACE_USB
#include "adb.h"

static char udc_controller_name[64] = { 0 };
static const char *init_controller_name()
{
    if (!udc_controller_name[0]) {
        DIR *dir;

        if ((dir = opendir("/sys/class/udc")) == NULL) {
            D("cannot found udc dir, udc driver maybe not select\n");
            exit(-1);
        }

        for (;;) {
            struct dirent *entry;

            if ((entry = readdir(dir)) == NULL) {
                closedir(dir);
                D("cannot found udc dir, udc driver maybe not select\n");
                exit(-1);
            }
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            if (entry->d_type != DT_REG && entry->d_type != DT_LNK) {
                continue;
            }
            strncpy(udc_controller_name, entry->d_name, sizeof(udc_controller_name));
            D("udc controller is %s\n", udc_controller_name);

            break;
        }
        closedir(dir);
    }
    return udc_controller_name;
}

void set_udc()
{
    const char *controller_name = init_controller_name();
    int fd = unix_open("/sys/kernel/config/usb_gadget/g1/UDC", O_RDWR);
    close_on_exec(fd);
    unix_write(fd, controller_name, strlen(controller_name));
    unix_close(fd);
}
