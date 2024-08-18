#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>

#include "framebuffer.h"

// Define display resolution (adjust if necessary)
#define WIDTH 128
#define HEIGHT 64

static int constructor();
static void clear_screen(ssize_t color);

struct fb_class framebuffer = {
    .fd = -1,
    .pmap = NULL,
    .vinfo = NULL,
    .screensize = 0,
    .constructor = constructor,
    .clear_screen = clear_screen
};

static void handle_interrupt(int sigint) {
    // Cleanup
    clear_screen(0xFF);
    munmap(framebuffer.pmap, framebuffer.screensize);
    close(framebuffer.fd);
    printf("SIGINT received. Killed process: %d\n", getpid());
    exit(EXIT_SUCCESS);
}

static int constructor() {
    signal(SIGINT, &handle_interrupt);

    const char *device = "/dev/fb0";  
    framebuffer.fd = open(device, O_RDWR);

    if (framebuffer.fd == -1) {
        perror("Error opening framebuffer device");
        return 1;
    }

    // Get framebuffer variable information
    if (ioctl(framebuffer.fd, FBIOGET_VSCREENINFO, &framebuffer.vinfo)) {
        perror("Error reading variable information");
        close(framebuffer.fd);
        return 1;
    }

    // Check framebuffer dimensions
    if (framebuffer.vinfo.xres_virtual != WIDTH || framebuffer.vinfo.yres_virtual != HEIGHT) {
        fprintf(stderr, "Framebuffer dimensions do not match display specifications\n");
        close(framebuffer.fd);
        return 1;
    }

    // Calculate the size of the framebuffer
    framebuffer.screensize = (WIDTH * HEIGHT + 7) / 8;  // Number of bytes

    // Map the framebuffer to memory
    framebuffer.pmap = mmap(NULL, framebuffer.screensize, PROT_READ | PROT_WRITE, MAP_SHARED, framebuffer.fd, 0);
    if (framebuffer.pmap == MAP_FAILED) {
        perror("Error mapping framebuffer device to memory");
        close(framebuffer.fd);
        return 1;
    }
}

static void clear_screen(ssize_t color) {
    memset(framebuffer.pmap, color, framebuffer.screensize);  // Fill with white
    // flushes  changes  made  to  the  in-core copy of a file that was mapped into memory using mmap
    if (msync(framebuffer.pmap, framebuffer.screensize, MS_SYNC) == -1) {
        perror("msync failed");
    }
}