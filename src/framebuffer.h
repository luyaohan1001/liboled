#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include <linux/fb.h>


struct fb_class {
    int fd;
    int screensize;
    struct fb_var_screeninfo vinfo;
    void *pmap;
    void (*constructor)();
    void (*clear_screen)();
};

extern struct fb_class framebuffer;

#endif