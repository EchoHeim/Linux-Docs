#include "includes.h"

char table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //月修正数据表
int set_time[6] = {2016,10,22,17,49,6};		//设置时间数组;

char RTC_Get_Week(int year,char month,char day)	//功能描述:输入公历日期得到星期(只允许1901-2099年)		
{											//返回值：星期号	
	int temp2;
	char yearH,yearL;
	yearH=year/100;	yearL=year%100; 
	if (yearH>19)yearL+=100;	// 如果为21世纪,年份数加100  // 所过闰年数只算1900年之后的  
	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3) temp2--;
	return(temp2%7);
}

