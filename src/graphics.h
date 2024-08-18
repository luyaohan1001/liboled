#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__


struct display_class {
  int x;
  int y;
  void (*print)(const char* str);
  void (*clear_screen)();
};

extern char FONT_TABLE[128][8];
extern struct display_class display;

#endif