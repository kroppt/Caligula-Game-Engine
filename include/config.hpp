#ifndef CONFIG_H
#define CONFIG_H

extern int res_x;
extern int res_y;
extern int vsync;

void createConfig(const char *filename);
void readConfig(const char *filename);

#endif