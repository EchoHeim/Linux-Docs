#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/rtc.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include "lcd_init.h"

extern unsigned char pic[];
extern char table_week[]; //月修正数据表
extern int set_time[];		//设置时间数组;

void lcd_clear(unsigned long color);
long char_to_long( char * string, int length );

int Lcd_init (void);
void Lcd_close(void );

void Read_from_HZK16(const unsigned char *s, char* const chs);

void show_point(unsigned int x, unsigned int y, unsigned int c);
void show_char(int x, int y,unsigned int forecolor,unsigned int backcolor,unsigned char ch,char size,char mode);
void show_num(int x,int y,unsigned int point_color,unsigned int back_color,unsigned int num,char len,char size,char mode);
void show_chinese(unsigned int x, unsigned int y, unsigned int fc, unsigned int bc,  const unsigned char * chs,char size,char mode);
void show_string(int x, int y,unsigned int forecolor,unsigned int backcolor,const unsigned char *str,char size,char mode);
int show_bmp( int point_x, int point_y, char *bmpfile );
void Paint_Bmp(int x0,int y0,int width,int high,const unsigned char bmp[]);
void Change_pic(int x0,int y0,int x1,int y1,unsigned char x_len,unsigned char y_len,const unsigned char bmp[]);

char RTC_Get_Week(int year,char month,char day);
void date_time(void);