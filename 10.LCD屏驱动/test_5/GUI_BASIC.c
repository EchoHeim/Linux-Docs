#include "lcd.h"
#include "GUI_BASIC.h"

#define GUI_LCM_XMAX 800
#define GUI_LCM_YMAX 480

#define u32 unsigned int 
#define u16 unsigned short 
#define u8 unsigned char

int  GUI_Point(u16 x, u16 y, u32 color)
{  
   /* �������� */
   if(x>GUI_LCM_XMAX) return(0);
   if(y>GUI_LCM_YMAX) return(0);
   
   Show_point(x,y,color);
   return(1);
}

/****************************************************************************
* ���ƣ�GUI_HLine()
* ���ܣ���ˮƽ�ߡ�
* ��ڲ����� x0		ˮƽ����������е�λ��
*            y0		ˮƽ����������е�λ��
*            x1     ˮƽ���յ������е�λ��
*            color	��ʾ��ɫ(���ںڰ�ɫLCM��Ϊ0ʱ��Ϊ1ʱ��ʾ)
* ���ڲ�������
* ˵����
****************************************************************************/
void  GUI_HLine(u16 x0, u16 y0, u16 x1, u32 color) 
{  
   u32  temp;
   if(x0>x1) 						// ��x0��x1��С�������У��Ա㻭ͼ
   {  
	  temp = x1;
      x1 = x0;
      x0 = temp;
   }   
   do
   { 
      GUI_Point(x0,y0,color);
      x0++;
   }while(x1>=x0);
}


/****************************************************************************
* ���ƣ�GUI_RLine()
* ���ܣ�����ֱ�ߡ�
* ��ڲ����� x0		��ֱ����������е�λ��
*           y0		��ֱ����������е�λ��
*           y1      ��ֱ���յ������е�λ��
*           color	��ʾ��ɫ(���ںڰ�ɫLCM��Ϊ0ʱ��Ϊ1ʱ��ʾ)
* ���ڲ�������
* ˵����
****************************************************************************/
void  GUI_RLine(u16 x0, u16 y0, u16 y1, u32 color) 
{  
   u32  temp;
   if(y0>y1) 						// ��y0��y1��С�������У��Ա㻭ͼ
   {  
	  temp = y1;
      y1 = y0;
      y0 = temp;
   }
   do
   {  
	  GUI_Point(x0, y0, color);		// �����ʾ�������ֱ��
      y0++;
   }while(y1>=y0);	
}


/****************************************************************************
* ���ƣ�GUI_Rectangle()
* ���ܣ������Ρ�
* ��ڲ����� x0		�������Ͻǵ�x����ֵ
*           y0		�������Ͻǵ�y����ֵ
*           x1      �������½ǵ�x����ֵ
*           y1      �������½ǵ�y����ֵ
*           color	��ʾ��ɫ
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_Rectangle(u16 x0, u16 y0, u16 x1, u16 y1, u32 color)
{  GUI_HLine(x0, y0, x1, color);
   GUI_HLine(x0, y1, x1, color);
   GUI_RLine(x0, y0, y1, color);
   GUI_RLine(x1, y0, y1, color);
}


/****************************************************************************
* ���ƣ�GUI_RectangleFill()
* ���ܣ������Ρ���һ�����ľ���
* ��ڲ����� x0		�������Ͻǵ�x����ֵ
*           y0		�������Ͻǵ�y����ֵ
*           x1      �������½ǵ�x����ֵ
*           y1      �������½ǵ�y����ֵ
*           linec	�����ıߵ���ɫ
*						fullc �����ɫ
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_RectangleFill(u16 x0, u16 y0, u16 x1, u16 y1, u32 linec,u32 fullc)
{  u32  i;

   /* ���ҳ��������Ͻ������½ǵ������㣬������(x0,y0)��(x1,y1) */
   if(x0>x1) 						// ��x0>x1����x0��x1����
   {  i = x0;
      x0 = x1;
      x1 = i;
   }
   if(y0>y1)						// ��y0>y1����y0��y1����
   {  i = y0;
      y0 = y1;
      y1 = i;
   }
   
   /* �ж��Ƿ�ֻ��ֱ�� */
   if(y0==y1) 
   {  GUI_HLine(x0, y0, x1, linec);
      return;
   }
   if(x0==x1) 
   {  GUI_RLine(x0, y0, y1, linec);
      return;
   }
	 //��������
	 GUI_HLine(x0,y0,x1,linec);
	 GUI_HLine(x0,y1,x1,linec);
	 GUI_RLine(x0,y0,y1,linec);
	 GUI_RLine(x1,y0,y1,linec);
	 //�����ɫ
	 x0++;				//��ȥ������
	 y0++;
	 x1--;
	 y1--;
   while(y0<=y1)						
   {  GUI_HLine(x0, y0, x1, fullc);	// ��ǰ��ˮƽ��
      y0++;							// ��һ��
   }
}


/****************************************************************************
* ���ƣ�GUI_Square()
* ���ܣ��������Ρ�
* ��ڲ����� x0		���������Ͻǵ�x����ֵ
*           y0		���������Ͻǵ�y����ֵ
*           with    �����εı߳�
*           color	��ʾ��ɫ
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_Square(u16 x0, u16 y0, u8  with, u32  color)
{   if(with==0) return;
	if( (x0+with) > GUI_LCM_XMAX ) return;
	if( (y0+with) > GUI_LCM_YMAX ) return;
	GUI_Rectangle(x0, y0, x0+with, y0+with, color);

}



/****************************************************************************
* ���ƣ�GUI_Line()
* ���ܣ�����������֮���ֱ�ߡ�
* ��ڲ����� x0		ֱ������x����ֵ
*           y0		ֱ������y����ֵ
*           x1      ֱ���յ��x����ֵ
*           y1      ֱ���յ��y����ֵ
*           color	��ʾ��ɫ(���ںڰ�ɫLCM��Ϊ0ʱ��Ϊ1ʱ��ʾ)
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_Line(u16 x0, u16 y0, u16 x1, u16 y1, u32 color)
{  int   dx;						// ֱ��x���ֵ����
   int   dy;          			// ֱ��y���ֵ����
   signed char    dx_sym;					// x����������Ϊ-1ʱ��ֵ����Ϊ1ʱ��ֵ����
   signed char    dy_sym;					// y����������Ϊ-1ʱ��ֵ����Ϊ1ʱ��ֵ����
   int   dx_x2;					// dx*2ֵ���������ڼӿ������ٶ�
   int   dy_x2;					// dy*2ֵ���������ڼӿ������ٶ�
   int   di;						// ���߱���
   
   
   dx = x1-x0;						// ��ȡ����֮��Ĳ�ֵ
   dy = y1-y0;
   
   /* �ж��������򣬻��Ƿ�Ϊˮƽ�ߡ���ֱ�ߡ��� */
   if(dx>0)							// �ж�x�᷽��
   {  dx_sym = 1;					// dx>0������dx_sym=1
   }
   else
   {  if(dx<0)
      {  dx_sym = -1;				// dx<0������dx_sym=-1
      }
      else
      {  // dx==0������ֱ�ߣ���һ��
         GUI_RLine(x0, y0, y1, color);
      	 return;
      }
   }
   
   if(dy>0)							// �ж�y�᷽��
   {  dy_sym = 1;					// dy>0������dy_sym=1
   }
   else
   {  if(dy<0)
      {  dy_sym = -1;				// dy<0������dy_sym=-1
      }
      else
      {  // dy==0����ˮƽ�ߣ���һ��
         GUI_HLine(x0, y0, x1, color);
      	 return;
      }
   }
    
   /* ��dx��dyȡ����ֵ */
   dx = dx_sym * dx;
   dy = dy_sym * dy;
 
   /* ����2����dx��dyֵ */
   dx_x2 = dx*2;
   dy_x2 = dy*2;
   
   /* ʹ��Bresenham�����л�ֱ�� */
   if(dx>=dy)						// ����dx>=dy����ʹ��x��Ϊ��׼
   {  di = dy_x2 - dx;
      while(x0!=x1)
      {  GUI_Point(x0, y0, color);
         x0 += dx_sym;
         if(di<0)
         {  di += dy_x2;			// �������һ���ľ���ֵ
         }
         else
         {  di += dy_x2 - dx_x2;
            y0 += dy_sym;
         }
      }
      GUI_Point(x0, y0, color);		// ��ʾ���һ��
   }
   else								// ����dx<dy����ʹ��y��Ϊ��׼
   {  di = dx_x2 - dy;
      while(y0!=y1)
      {  GUI_Point(x0, y0, color);
         y0 += dy_sym;
         if(di<0)
         {  di += dx_x2;
         }
         else
         {  di += dx_x2 - dy_x2;
            x0 += dx_sym;
         }
      }
      GUI_Point(x0, y0, color);		// ��ʾ���һ��
   } 
  
}

/****************************************************************************
* ���ƣ�GUI_LineWith()
* ���ܣ�����������֮���ֱ�ߣ����ҿ������ߵĿ�ȡ�
* ��ڲ����� x0		ֱ������x����ֵ
*           y0		ֱ������y����ֵ
*           x1      ֱ���յ��x����ֵ
*           y1      ֱ���յ��y����ֵ
*           with    �߿�(0-50)
*           color	��ʾ��ɫ
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_LineWith(u16 x0, u16 y0, u16 x1, u16 y1, u8 with, u32 color)
{  int   dx;						// ֱ��x���ֵ����
   int   dy;          			// ֱ��y���ֵ����
   signed char		 dx_sym;					// x����������Ϊ-1ʱ��ֵ����Ϊ1ʱ��ֵ����
   signed char    dy_sym;					// y����������Ϊ-1ʱ��ֵ����Ϊ1ʱ��ֵ����
   int   dx_x2;					// dx*2ֵ���������ڼӿ������ٶ�
   int   dy_x2;					// dy*2ֵ���������ڼӿ������ٶ�
   int   di;						// ���߱���
   
   int   wx, wy;					// �߿����
   int   draw_a, draw_b;
   
   /* �������� */
   if(with==0) return;
   if(with>50) with = 50;
   
   dx = x1-x0;						// ��ȡ����֮��Ĳ�ֵ
   dy = y1-y0;
   
   wx = with/2;
   wy = with-wx-1;
   
   /* �ж��������򣬻��Ƿ�Ϊˮƽ�ߡ���ֱ�ߡ��� */
   if(dx>0)							// �ж�x�᷽��
   {  dx_sym = 1;					// dx>0������dx_sym=1
   }
   else
   {  if(dx<0)
      {  dx_sym = -1;				// dx<0������dx_sym=-1
      }
      else
      {  /* dx==0������ֱ�ߣ���һ�� */
         wx = x0-wx;
         if(wx<0) wx = 0;
         wy = x0+wy;
         
         while(1)
         {  x0 = wx;
            GUI_RLine(x0, y0, y1, color);
            if(wx>=wy) break;
            wx++;
         }
         
      	 return;
      }
   }
   
   if(dy>0)							// �ж�y�᷽��
   {  dy_sym = 1;					// dy>0������dy_sym=1
   }
   else
   {  if(dy<0)
      {  dy_sym = -1;				// dy<0������dy_sym=-1
      }
      else
      {  /* dy==0����ˮƽ�ߣ���һ�� */
         wx = y0-wx;
         if(wx<0) wx = 0;
         wy = y0+wy;
         
         while(1)
         {  y0 = wx;
            GUI_HLine(x0, y0, x1, color);
            if(wx>=wy) break;
            wx++;
         }
      	 return;
      }
   }
    
   /* ��dx��dyȡ����ֵ */
   dx = dx_sym * dx;
   dy = dy_sym * dy;
 
   /* ����2����dx��dyֵ */
   dx_x2 = dx*2;
   dy_x2 = dy*2;
   
   /* ʹ��Bresenham�����л�ֱ�� */
   if(dx>=dy)						// ����dx>=dy����ʹ��x��Ϊ��׼
   {  di = dy_x2 - dx;
      while(x0!=x1)
      {  /* x����������������y���򣬼�����ֱ�� */
         draw_a = y0-wx;
         if(draw_a<0) draw_a = 0;
         draw_b = y0+wy;
         GUI_RLine(x0, draw_a, draw_b, color);
         
         x0 += dx_sym;				
         if(di<0)
         {  di += dy_x2;			// �������һ���ľ���ֵ
         }
         else
         {  di += dy_x2 - dx_x2;
            y0 += dy_sym;
         }
      }
      draw_a = y0-wx;
      if(draw_a<0) draw_a = 0;
      draw_b = y0+wy;
      GUI_RLine(x0, draw_a, draw_b, color);
   }
   else								// ����dx<dy����ʹ��y��Ϊ��׼
   {  di = dx_x2 - dy;
      while(y0!=y1)
      {  /* y����������������x���򣬼���ˮƽ�� */
         draw_a = x0-wx;
         if(draw_a<0) draw_a = 0;
         draw_b = x0+wy;
         GUI_HLine(draw_a, y0, draw_b, color);
         
         y0 += dy_sym;
         if(di<0)
         {  di += dx_x2;
         }
         else
         {  di += dx_x2 - dy_x2;
            x0 += dx_sym;
         }
      }
      draw_a = x0-wx;
      if(draw_a<0) draw_a = 0;
      draw_b = x0+wy;
      GUI_HLine(draw_a, y0, draw_b, color);
   } 
  
}


/****************************************************************************
* ���ƣ�GUI_LineS()
* ���ܣ������֮����������ߡ��ӵ�һ�������ڶ��㣬������������...
* ��ڲ����� points  ������������ݵ�ָ�룬��������Ϊ(x0,y0)��(x1,y1)��(x2,y2)...
*           no      ����Ŀ������Ҫ����1
*           color	��ʾ��ɫ
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_LineS(u32 const *points, u8 no, u32 color)
{  u16  x0, y0;
   u16  x1, y1;
   u8  i;

   /* ��ڲ������� */
   if(0==no) return;
   if(1==no)						// ����
   {  x0 = *points++;
      y0 = *points;
      GUI_Point(x0, y0, color);
   }
   
   /* ���������� */
   x0 = *points++;					// ȡ����һ������ֵ����Ϊԭ�������ֵ
   y0 = *points++;
   for(i=1; i<no; i++)
   {  x1 = *points++;				// ȡ����һ������ֵ
      y1 = *points++;
      GUI_Line(x0, y0, x1, y1, color);
      x0 = x1;						// ����ԭ�������
      y0 = y1;
   }
}

/****************************************************************************
* ���ƣ�GUI_Circle()
* ���ܣ�ָ��Բ��λ�ü��뾶����Բ��
* ��ڲ����� x0		Բ�ĵ�x����ֵ
*           y0		Բ�ĵ�y����ֵ
*           r       Բ�İ뾶
*           color	��ʾ��ɫ
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_Circle(u16 x0, u16 y0, u16 r, u32 color)
{  int  draw_x0, draw_y0;			// ��ͼ���������
   int  draw_x1, draw_y1;	
   int  draw_x2, draw_y2;	
   int  draw_x3, draw_y3;	
   int  draw_x4, draw_y4;	
   int  draw_x5, draw_y5;	
   int  draw_x6, draw_y6;	
   int  draw_x7, draw_y7;	
   int  xx, yy;					// ��Բ���Ʊ���
 
   int  di;						// ���߱���
   
   /* �������� */
   if(0==r) return;
   
   /* �����8�������(0��45��90��135��180��225��270��)��������ʾ */
   draw_x0 = draw_x1 = x0;
   draw_y0 = draw_y1 = y0 + r;
   if(draw_y0<GUI_LCM_YMAX) GUI_Point(draw_x0, draw_y0, color);	// 90��
	
   draw_x2 = draw_x3 = x0;
   draw_y2 = draw_y3 = y0 - r;
   if(draw_y2>=0) GUI_Point(draw_x2, draw_y2, color);			// 270��
   
	
   draw_x4 = draw_x6 = x0 + r;
   draw_y4 = draw_y6 = y0;
   if(draw_x4<GUI_LCM_XMAX) GUI_Point(draw_x4, draw_y4, color);	// 0��
   
   draw_x5 = draw_x7 = x0 - r;
   draw_y5 = draw_y7 = y0;
   if(draw_x5>=0) GUI_Point(draw_x5, draw_y5, color);			// 180��   
   if(1==r) return;					// ���뾶Ϊ1������Բ����
   
   
   /* ʹ��Bresenham�����л�Բ */
   di = 3 - 2*r;					// ��ʼ�����߱���
   
   xx = 0;
   yy = r;	
   while(xx<yy)
   {  if(di<0)
	  {  di += 4*xx + 6;	      
	  }
	  else
	  {  di += 4*(xx - yy) + 10;
	  
	     yy--;	  
		 draw_y0--;
		 draw_y1--;
		 draw_y2++;
		 draw_y3++;
		 draw_x4--;
		 draw_x5++;
		 draw_x6--;
		 draw_x7++;	 	
	  }
	  
	  xx++;   
	  draw_x0++;
	  draw_x1--;
	  draw_x2++;
	  draw_x3--;
	  draw_y4++;
	  draw_y5++;
	  draw_y6--;
	  draw_y7--;
		
	
	  /* Ҫ�жϵ�ǰ���Ƿ�����Ч��Χ�� */
	  if( (draw_x0<=GUI_LCM_XMAX)&&(draw_y0>=0) )	
	  {  GUI_Point(draw_x0, draw_y0, color);
	  }	    
	  if( (draw_x1>=0)&&(draw_y1>=0) )	
	  {  GUI_Point(draw_x1, draw_y1, color);
	  }
	  if( (draw_x2<=GUI_LCM_XMAX)&&(draw_y2<=GUI_LCM_YMAX) )	
	  {  GUI_Point(draw_x2, draw_y2, color);   
	  }
	  if( (draw_x3>=0)&&(draw_y3<=GUI_LCM_YMAX) )	
	  {  GUI_Point(draw_x3, draw_y3, color);
	  }
	  if( (draw_x4<=GUI_LCM_XMAX)&&(draw_y4>=0) )	
	  {  GUI_Point(draw_x4, draw_y4, color);
	  }
	  if( (draw_x5>=0)&&(draw_y5>=0) )	
	  {  GUI_Point(draw_x5, draw_y5, color);
	  }
	  if( (draw_x6<=GUI_LCM_XMAX)&&(draw_y6<=GUI_LCM_YMAX) )	
	  {  GUI_Point(draw_x6, draw_y6, color);
	  }
	  if( (draw_x7>=0)&&(draw_y7<=GUI_LCM_YMAX) )	
	  {  GUI_Point(draw_x7, draw_y7, color);
	  }
   }
}


/****************************************************************************
* ���ƣ�GUI_CircleFill()
* ���ܣ�ָ��Բ��λ�ü��뾶����Բ�����
* ��ڲ����� x0		Բ�ĵ�x����ֵ
*           y0		Բ�ĵ�y����ֵ
*           r       Բ�İ뾶
*						linec	Բ�ε���ɫ
*          	fullc	������ɫ
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_CircleFill(u16 x0, u16 y0, u16 r,u32 linec,u32 fullc)
{  int  draw_x0, draw_y0;			// ��ͼ���������
   int  draw_x1, draw_y1;	
   int  draw_x2, draw_y2;	
   int  draw_x3, draw_y3;	
   int  draw_x4, draw_y4;	
   int  draw_x5, draw_y5;	
   int  draw_x6, draw_y6;	
   int  draw_x7, draw_y7;	
   int  fill_x0, fill_y0;			// �������ı�����ʹ�ô�ֱ�����
   int  fill_x1;
   int  xx, yy;					// ��Բ���Ʊ���
 
   int  di;						// ���߱���
   
   /* �������� */
   if(0==r) return;
   
   /* �����4�������(0��90��180��270��)��������ʾ */
   draw_x0 = draw_x1 = x0;
   draw_y0 = draw_y1 = y0 + r;
   if(draw_y0<GUI_LCM_YMAX)
   {  GUI_Point(draw_x0, draw_y0, fullc);	// 90��
   }
    	
   draw_x2 = draw_x3 = x0;
   draw_y2 = draw_y3 = y0 - r;
   if(draw_y2>=0)
   {  GUI_Point(draw_x2, draw_y2, fullc);	// 270��
   }
  	
   draw_x4 = draw_x6 = x0 + r;
   draw_y4 = draw_y6 = y0;
   if(draw_x4<GUI_LCM_XMAX) 
   {  GUI_Point(draw_x4, draw_y4, fullc);	// 0��
      fill_x1 = draw_x4;
   }
   else
   {  fill_x1 = GUI_LCM_XMAX;
   }
   fill_y0 = y0;							// �������������ʼ��fill_x0
   fill_x0 = x0 - r;						// �����������������fill_y1
   if(fill_x0<0) fill_x0 = 0;
   GUI_HLine(fill_x0, fill_y0, fill_x1, fullc);
   
   draw_x5 = draw_x7 = x0 - r;
   draw_y5 = draw_y7 = y0;
   if(draw_x5>=0) 
   {  GUI_Point(draw_x5, draw_y5, fullc);	// 180��
   }
   if(1==r) return;
   
   
   /* ʹ��Bresenham�����л�Բ */
   di = 3 - 2*r;							// ��ʼ�����߱���
   
   xx = 0;
   yy = r;
   while(xx<yy)
   {  if(di<0)
	  {  di += 4*xx + 6;
	  }
	  else
	  {  di += 4*(xx - yy) + 10;
	  
	     yy--;	  
		 draw_y0--;
		 draw_y1--;
		 draw_y2++;
		 draw_y3++;
		 draw_x4--;
		 draw_x5++;
		 draw_x6--;
		 draw_x7++;		 
	  }
	  
	  xx++;   
	  draw_x0++;
	  draw_x1--;
	  draw_x2++;
	  draw_x3--;
	  draw_y4++;
	  draw_y5++;
	  draw_y6--;
	  draw_y7--;
		
	
	  /* Ҫ�жϵ�ǰ���Ƿ�����Ч��Χ�� */
	  if( (draw_x0<=GUI_LCM_XMAX)&&(draw_y0>=0) )	
	  {  GUI_Point(draw_x0, draw_y0, fullc);
	  }	    
	  if( (draw_x1>=0)&&(draw_y1>=0) )	
	  {  GUI_Point(draw_x1, draw_y1, fullc);
	  }
	  
	  /* �ڶ���ˮֱ�����(�°�Բ�ĵ�) */
	  if(draw_x1>=0)
	  {  /* �������������ʼ��fill_x0 */
	     fill_x0 = draw_x1;
	     /* �������������ʼ��fill_y0 */
	     fill_y0 = draw_y1;
         if(fill_y0>GUI_LCM_YMAX) fill_y0 = GUI_LCM_YMAX;
         if(fill_y0<0) fill_y0 = 0; 
         /* �����������������fill_x1 */									
         fill_x1 = x0*2 - draw_x1;				
         if(fill_x1>GUI_LCM_XMAX) fill_x1 = GUI_LCM_XMAX;
         GUI_HLine(fill_x0, fill_y0, fill_x1, fullc);
      }
	  
	  
	  if( (draw_x2<=GUI_LCM_XMAX)&&(draw_y2<=GUI_LCM_YMAX) )	
	  {  GUI_Point(draw_x2, draw_y2, fullc);   
	  }
	    	  
	  if( (draw_x3>=0)&&(draw_y3<=GUI_LCM_YMAX) )	
	  {  GUI_Point(draw_x3, draw_y3, fullc);
	  }
	  
	  /* ���ĵ㴹ֱ�����(�ϰ�Բ�ĵ�) */
	  if(draw_x3>=0)
	  {  /* �������������ʼ��fill_x0 */
	     fill_x0 = draw_x3;
	     /* �������������ʼ��fill_y0 */
	     fill_y0 = draw_y3;
         if(fill_y0>GUI_LCM_YMAX) fill_y0 = GUI_LCM_YMAX;
         if(fill_y0<0) fill_y0 = 0;
         /* �����������������fill_x1 */									
         fill_x1 = x0*2 - draw_x3;				
         if(fill_x1>GUI_LCM_XMAX) fill_x1 = GUI_LCM_XMAX;
         GUI_HLine(fill_x0, fill_y0, fill_x1, fullc);
      }
	  
	  	  
	  if( (draw_x4<=GUI_LCM_XMAX)&&(draw_y4>=0) )	
	  {  GUI_Point(draw_x4, draw_y4, fullc);
	  }
	  if( (draw_x5>=0)&&(draw_y5>=0) )	
	  {  GUI_Point(draw_x5, draw_y5, fullc);
	  }
	  
	  /* �����㴹ֱ�����(�ϰ�Բ�ĵ�) */
	  if(draw_x5>=0)
	  {  /* �������������ʼ��fill_x0 */
	     fill_x0 = draw_x5;
	     /* �������������ʼ��fill_y0 */
	     fill_y0 = draw_y5;
         if(fill_y0>GUI_LCM_YMAX) fill_y0 = GUI_LCM_YMAX;
         if(fill_y0<0) fill_y0 = 0;
         /* �����������������fill_x1 */									
         fill_x1 = x0*2 - draw_x5;				
         if(fill_x1>GUI_LCM_XMAX) fill_x1 = GUI_LCM_XMAX;
         GUI_HLine(fill_x0, fill_y0, fill_x1, fullc);
      }
	  
	  
	  if( (draw_x6<=GUI_LCM_XMAX)&&(draw_y6<=GUI_LCM_YMAX) )	
	  {  GUI_Point(draw_x6, draw_y6, fullc);
	  }
	  
	  if( (draw_x7>=0)&&(draw_y7<=GUI_LCM_YMAX) )	
	  {  GUI_Point(draw_x7, draw_y7, fullc);
	  }
	  
	  /* �ڰ˵㴹ֱ�����(�ϰ�Բ�ĵ�) */
	  if(draw_x7>=0)
	  {  /* �������������ʼ��fill_x0 */
	     fill_x0 = draw_x7;
	     /* �������������ʼ��fill_y0 */
	     fill_y0 = draw_y7;
         if(fill_y0>GUI_LCM_YMAX) fill_y0 = GUI_LCM_YMAX;
         if(fill_y0<0) fill_y0 = 0;
         /* �����������������fill_x1 */									
         fill_x1 = x0*2 - draw_x7;				
         if(fill_x1>GUI_LCM_XMAX) fill_x1 = GUI_LCM_XMAX;
         GUI_HLine(fill_x0, fill_y0, fill_x1, fullc);
      }
	  
   }
	 if(linec != fullc)
	 {
			GUI_Circle(x0,y0,r,linec);
	 }
}




/****************************************************************************
* ���ƣ�GUI_Ellipse()
* ���ܣ�������Բ��������Բ���ĸ���Ĳ������������ҵ��x������ֵΪx0��x1�����ϡ����µ�
*      ��y������Ϊy0��y1��
* ��ڲ����� x0		������x����ֵ
*           x1		���ҵ��x����ֵ
*           y0		���ϵ��y����ֵ
*           y1      ���µ��y����ֵ
*           color	��ʾ��ɫ
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_Ellipse(u16 x0, u16 x1, u16 y0, u16 y1, u32 color)
{  int  draw_x0, draw_y0;			// ��ͼ���������
   int  draw_x1, draw_y1;
   int  draw_x2, draw_y2;
   int  draw_x3, draw_y3;
   int  xx, yy;					// ��ͼ���Ʊ���
    
   int  center_x, center_y;		// ��Բ���ĵ��������
   int  radius_x, radius_y;		// ��Բ�İ뾶��x��뾶��y��뾶
   int  radius_xx, radius_yy;		// �뾶��ƽ��ֵ
   int  radius_xx2, radius_yy2;	// �뾶��ƽ��ֵ������
   int  di;						// ������߱���
	
   /* �������� */
   if( (x0==x1) || (y0==y1) ) return;
   	
   /* �������Բ���ĵ����� */
   center_x = (x0 + x1) >> 1;			
   center_y = (y0 + y1) >> 1;
   
   /* �������Բ�İ뾶��x��뾶��y��뾶 */
   if(x0 > x1)
   {  radius_x = (x0 - x1) >> 1;
   }
   else
   {  radius_x = (x1 - x0) >> 1;
   }
   if(y0 > y1)
   {  radius_y = (y0 - y1) >> 1;
   }
   else
   {  radius_y = (y1 - y0) >> 1;
   }
		
   /* ����뾶ƽ��ֵ */
   radius_xx = radius_x * radius_x;
   radius_yy = radius_y * radius_y;
	
   /* ����뾶ƽ��ֵ��2ֵ */
   radius_xx2 = radius_xx<<1;
   radius_yy2 = radius_yy<<1;
	
   /* ��ʼ����ͼ���� */
   xx = 0;
   yy = radius_y;
  
   di = radius_yy2 + radius_xx - radius_xx2*radius_y ;	// ��ʼ�����߱��� 
	
   /* �������Բy���ϵ������˵����꣬��Ϊ��ͼ��� */
   draw_x0 = draw_x1 = draw_x2 = draw_x3 = center_x;
   draw_y0 = draw_y1 = center_y + radius_y;
   draw_y2 = draw_y3 = center_y - radius_y;
  
	 
   GUI_Point(draw_x0, draw_y0, color);					// ��y���ϵ������˵� 
   GUI_Point(draw_x2, draw_y2, color);
	
   while( (radius_yy*xx) < (radius_xx*yy) ) 
   {  if(di<0)
	  {  di+= radius_yy2*(2*xx+3);
	  }
	  else
	  {  di += radius_yy2*(2*xx+3) + 4*radius_xx - 4*radius_xx*yy;
	 	  
	     yy--;
		 draw_y0--;
		 draw_y1--;
		 draw_y2++;
		 draw_y3++;				 
	  }
	  
	  xx ++;						// x���1
	 		
	  draw_x0++;
	  draw_x1--;
	  draw_x2++;
	  draw_x3--;
		
	  GUI_Point(draw_x0, draw_y0, color);
	  GUI_Point(draw_x1, draw_y1, color);
	  GUI_Point(draw_x2, draw_y2, color);
	  GUI_Point(draw_x3, draw_y3, color);
   }
  
   di = radius_xx2*(yy-1)*(yy-1) + radius_yy2*xx*xx + radius_yy + radius_yy2*xx - radius_xx2*radius_yy;
   while(yy>=0) 
   {  if(di<0)
	  {  di+= radius_xx2*3 + 4*radius_yy*xx + 4*radius_yy - 2*radius_xx2*yy;
	 	  
	     xx ++;						// x���1	 		
	     draw_x0++;
	     draw_x1--;
	     draw_x2++;
	     draw_x3--;  
	  }
	  else
	  {  di += radius_xx2*3 - 2*radius_xx2*yy;	 	 		     			 
	  }
	  
	  yy--;
 	  draw_y0--;
	  draw_y1--;
	  draw_y2++;
	  draw_y3++;	
		
	  GUI_Point(draw_x0, draw_y0, color);
	  GUI_Point(draw_x1, draw_y1, color);
	  GUI_Point(draw_x2, draw_y2, color);
	  GUI_Point(draw_x3, draw_y3, color);
   }     
}


/****************************************************************************
* ���ƣ�GUI_Arc4()
* ���ܣ���������㼰�յ�ֻ��Ϊ0��-90�ȡ�90��-180�ȡ�180��-270�ȡ�270��-0�ȵȡ����ֱ�
*      Ϊ��1-4���޵�90�Ȼ���
* ��ڲ����� x0		Բ�ĵ�x����ֵ
*           y0		Բ�ĵ�y����ֵ
*           r       Բ���İ뾶
*           angle	����������(1-4)
*           color	��ʾ��ɫ
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_Arc4(u16 x, u16 y, u16 r, u8 angle, u32 color)
{  
	 int  draw_x, draw_y;

   int  op_x, op_y;
   int  op_2rr;
   
   if(r==0) return;
   
   op_2rr = 2*r*r;										// ����rƽ������2
   
   switch(angle)
   {  case  1:
            draw_x = x+r;
            draw_y = y;
            
            op_x = r;
            op_y = 0;
 
            while(1)
            {  GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
                 
               /* ������һ�� */
               op_y++;
               draw_y++;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ʹ�����ȽϷ�ʵ�ֻ�Բ��
               {  op_x--;
                  draw_x--;
               }
               if(op_y>=op_x) break;
            }
            while(1)
            {  GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
                 
               /* ������һ�� */
               op_x--;
               draw_x--;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) 	// ʹ�����ȽϷ�ʵ�ֻ�Բ��
               {  op_y++;
                  draw_y++;
               }
               if(op_x<=0)
               {  GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
                  break;
               }
            }
   
            break;      
   				
      case  2:
            draw_x = x-r;
            draw_y = y;
            
            op_x = r;
            op_y = 0;
 
            while(1)
            {  GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
                 
               /* ������һ�� */
               op_y++;
               draw_y++;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ʹ�����ȽϷ�ʵ�ֻ�Բ��
               {  op_x--;
                  draw_x++;
               }
               if(op_y>=op_x) break;
            }
            while(1)
            {  GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
                 
               /* ������һ�� */
               op_x--;
               draw_x++;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) 	// ʹ�����ȽϷ�ʵ�ֻ�Բ��
               {  op_y++;
                  draw_y++;
               }
               if(op_x<=0)
               {  GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
                  break;
               }
            }
  
            break;
            
      case  3:
            draw_x = x-r;
            draw_y = y;
            
            op_x = r;
            op_y = 0;
 
            while(1)
            {  GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
                 
               /* ������һ�� */
               op_y++;
               draw_y--;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ʹ�����ȽϷ�ʵ�ֻ�Բ��
               {  op_x--;
                  draw_x++;
               }
               if(op_y>=op_x) break;
            }
            while(1)
            {  GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
                 
               /* ������һ�� */
               op_x--;
               draw_x++;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) 	// ʹ�����ȽϷ�ʵ�ֻ�Բ��
               {  op_y++;
                  draw_y--;
               }
               if(op_x<=0)
               {  GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
                  break;
               }
            }
      
            break;
            
      case  4:
            draw_x = x+r;
            draw_y = y;
            
            op_x = r;
            op_y = 0;
 
            while(1)
            {  GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
                 
               /* ������һ�� */
               op_y++;
               draw_y--;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ʹ�����ȽϷ�ʵ�ֻ�Բ��
               {  op_x--;
                  draw_x--;
               }
               if(op_y>=op_x) break;
            }
            while(1)
            {  GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
                 
               /* ������һ�� */
               op_x--;
               draw_x--;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) 	// ʹ�����ȽϷ�ʵ�ֻ�Բ��
               {  op_y++;
                  draw_y--;
               }
               if(op_x<=0)
               {  GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
                  break;
               }
            }
            break;
            
      default:
            break;
      
   }

}

/****************************************************************************
* ���ƣ�GUI_Arc()
* ���ܣ�ָ����㡢�յ㼰�뾶����(���ܻ�Բ)��ʹ�õ���˳ʱ�뷽��ͼ��
* ��ڲ����� x			Բ�ĵ�x������ֵ
*           y			Բ�ĵ�y������ֵ
*           stangle 	��ʼ�Ƕ�(0-359��)
*           endangle	��ֹ�Ƕ�(0-359��)
*           r  			Բ�İ뾶�յ�
*           color		��ʾ��ɫ
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_Arc(u16 x, u16 y, u16 r, u16 stangle, u16 endangle, u32 color)
{  int draw_x, draw_y;					// ��ͼ�������
   int  op_x, op_y;						// ��������
   int  op_2rr;							// 2*r*rֵ����
   
   int  pno_angle;						// �Ƚǵ�ĸ���
   u8  draw_on;							// ���㿪�أ�Ϊ1ʱ���㣬Ϊ0ʱ����
   
   
   /* �������� */
   if(r==0) return;							// �뾶Ϊ0��ֱ���˳�
   if(stangle==endangle) return;			// ��ʼ�Ƕ�����ֹ�Ƕ���ͬ���˳�
   if( (stangle>=360) || (endangle>=360) ) return;

   op_2rr = 2*r*r;							// ����rƽ������2
   pno_angle = 0;
   /* �ȼ�����ڴ˰뾶�µ�45�ȵ�Բ���ĵ��� */       
   op_x = r;
   op_y = 0;
   while(1)
   {  pno_angle++; 							// �������         
      /* ������һ�� */
      op_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_x--;
      }
      if(op_y>=op_x) break;
   }
   
   draw_on = 0;								// �ʼ�ػ��㿪��
   /* ������ʼ�㼰�յ� */
   if(endangle>stangle) draw_on = 1;		// ���յ������㣬���һ��ʼ������(359)
   stangle = (360-stangle)*pno_angle/45;
   endangle = (360-endangle)*pno_angle/45;
   if(stangle==0) stangle=1;
   if(endangle==0) endangle=1;
   
   /* ��ʼ˳ʱ�뻭������359�ȿ�ʼ(��4����) */
   pno_angle = 0;
   
   draw_x = x+r;
   draw_y = y;         
   op_x = r;
   op_y = 0;
   while(1)
   {  /* ������һ�� */
      op_y++;
      draw_y--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_x--;
         draw_x--;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
      } 
      if(op_y>=op_x)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         break;
      }
   }
   
   while(1)
   {  /* ������һ�� */
      op_x--;
      draw_x--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_y++;
         draw_y--;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
      } 
      
      if(op_x<=0)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
         break;
      }
   }
    
    
   /* ��ʼ˳ʱ�뻭������269�ȿ�ʼ(��3����) */
   draw_y = y-r;
   draw_x = x;         
   op_y = r;
   op_x = 0;
   while(1)
   {  /* ������һ�� */
      op_x++;
      draw_x--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 ) // ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_y--;
         draw_y++;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
      } 
      
      if(op_x>=op_y)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
         break;
      }
   }
   
   while(1)
   {  /* ������һ�� */
      op_y--;
      draw_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 ) // ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_x++;
         draw_x--;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
      } 
      if(op_y<=0)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         break;
      }
   }
   
   
   /* ��ʼ˳ʱ�뻭������179�ȿ�ʼ(��2����) */
   draw_x = x-r;
   draw_y = y;         
   op_x = r;
   op_y = 0;
   while(1)
   {  /* ������һ�� */
      op_y++;
      draw_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_x--;
         draw_x++;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
      } 
      if(op_y>=op_x)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         break;
      }
   }
   
   while(1)
   {  /* ������һ�� */
      op_x--;
      draw_x++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_y++;
         draw_y++;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
      } 
      
      if(op_x<=0)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
         break;
      }
   }
  
  
   /* ��ʼ˳ʱ�뻭������89�ȿ�ʼ(��1����) */
   draw_y = y+r;
   draw_x = x;         
   op_y = r;
   op_x = 0;
   while(1)
   {  /* ������һ�� */
      op_x++;
      draw_x++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 ) // ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_y--;
         draw_y--;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
      } 
      
      if(op_x>=op_y)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
         break;
      }
   }
   
   while(1)
   {  /* ������һ�� */
      op_y--;
      draw_y--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 ) // ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_x++;
         draw_x++;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
      } 
      if(op_y<=0)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         break;
      }
   }
   
}

/****************************************************************************
* ���ƣ�GUI_Pieslice()
* ���ܣ�ָ����㡢�յ㼰�뾶����(���ܻ�Բ)��ʹ�õ���˳ʱ�뷽��ͼ��
* ��ڲ����� x			Բ�ĵ�x������ֵ
*           y			Բ�ĵ�y������ֵ
*           stangle 	��ʼ�Ƕ�(0-359��)
*           endangle	��ֹ�Ƕ�(0-359��)
*           r  			Բ�İ뾶�յ�
*           color		��ʾ��ɫ
* ���ڲ�������
* ˵��������ʧ��ԭ����ָ����ַ������Ч��Χ��
****************************************************************************/
void  GUI_Pieslice(u16 x, u16 y, u16 r, u16 stangle, u16 endangle, u32 color)
{  int  draw_x, draw_y;					// ��ͼ�������
   int  op_x, op_y;						// ��������
   int  op_2rr;							// 2*r*rֵ����
   
   int  pno_angle;						// �Ƚǵ�ĸ���
   u8  draw_on;							// ���㿪�أ�Ϊ1ʱ���㣬Ϊ0ʱ����
   
   
   /* �������� */
   if(r==0) return;							// �뾶Ϊ0��ֱ���˳�
   if(stangle==endangle) return;			// ��ʼ�Ƕ�����ֹ�Ƕ���ͬ���˳�
   if( (stangle>=360) || (endangle>=360) ) return;

   op_2rr = 2*r*r;							// ����rƽ������2
   pno_angle = 0;
   /* �ȼ�����ڴ˰뾶�µ�45�ȵ�Բ���ĵ��� */       
   op_x = r;
   op_y = 0;
   while(1)
   {  pno_angle++; 							// �������         
      /* ������һ�� */
      op_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_x--;
      }
      if(op_y>=op_x) break;
   }
   
   draw_on = 0;								// �ʼ�ػ��㿪��
   /* ������ʼ�㼰�յ� */
   if(endangle>stangle) draw_on = 1;		// ���յ������㣬���һ��ʼ������(359)
   stangle = (360-stangle)*pno_angle/45;
   endangle = (360-endangle)*pno_angle/45;
   if(stangle==0) stangle=1;
   if(endangle==0) endangle=1;
   
   /* ��ʼ˳ʱ�뻭������359�ȿ�ʼ(��4����) */
   pno_angle = 0;
   
   draw_x = x+r;
   draw_y = y;         
   op_x = r;
   op_y = 0;
   while(1)
   {  /* ������һ�� */
      op_y++;
      draw_y--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_x--;
         draw_x--;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      if(op_y>=op_x)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         break;
      }
   }
   
   while(1)
   {  /* ������һ�� */
      op_x--;
      draw_x--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_y++;
         draw_y--;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      
      if(op_x<=0)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
         break;
      }
   }
    
    
   /* ��ʼ˳ʱ�뻭������269�ȿ�ʼ(��3����) */
   draw_y = y-r;
   draw_x = x;         
   op_y = r;
   op_x = 0;
   while(1)
   {  /* ������һ�� */
      op_x++;
      draw_x--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 ) // ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_y--;
         draw_y++;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      
      if(op_x>=op_y)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
         break;
      }
   }
   
   while(1)
   {  /* ������һ�� */
      op_y--;
      draw_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 ) // ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_x++;
         draw_x--;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      if(op_y<=0)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         break;
      }
   }
   
   
   /* ��ʼ˳ʱ�뻭������179�ȿ�ʼ(��2����) */
   draw_x = x-r;
   draw_y = y;         
   op_x = r;
   op_y = 0;
   while(1)
   {  /* ������һ�� */
      op_y++;
      draw_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_x--;
         draw_x++;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      if(op_y>=op_x)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         break;
      }
   }
   
   while(1)
   {  /* ������һ�� */
      op_x--;
      draw_x++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_y++;
         draw_y++;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      
      if(op_x<=0)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
         break;
      }
   }
  
  
   /* ��ʼ˳ʱ�뻭������89�ȿ�ʼ(��1����) */
   draw_y = y+r;
   draw_x = x;         
   op_y = r;
   op_x = 0;
   while(1)
   {  /* ������һ�� */
      op_x++;
      draw_x++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 ) // ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_y--;
         draw_y--;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      
      if(op_x>=op_y)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);		// ��ʼ��ͼ
         break;
      }
   }
   
   while(1)
   {  /* ������һ�� */
      op_y--;
      draw_y--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 ) // ʹ�����ȽϷ�ʵ�ֻ�Բ��
      {  op_x++;
         draw_x++;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// ��ʼ��ͼ
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// �����������յ㣬���㿪��ȡ��
      {  draw_on = 1-draw_on;
         if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      if(op_y<=0)
      {  if(draw_on==1) GUI_Point(draw_x, draw_y, color);
         break;
      }
   }
   
}


