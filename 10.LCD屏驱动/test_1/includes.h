#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include "lcd_init.h"

void lcd_clear(unsigned long color);
long char_to_long( char * string, int length );

int Lcd_init (void);
void Lcd_close(void );

void Read_from_HZK16(const unsigned char *s, char* const chs);

void show_point(unsigned int x, unsigned int y, unsigned int c);
void show_char(int x, int y,unsigned int forecolor,unsigned int backcolor,unsigned char ch);
void show_chinese_16(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc,  const unsigned char * chs);
void show_string(int x, int y,unsigned int forecolor,unsigned int backcolor,const unsigned char *str);
int show_bmp( int point_x, int point_y, char *bmpfile );

