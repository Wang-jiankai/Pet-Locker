#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	 
#include "lcd.h"  
#include "key.h"     
#include "usmart.h" 
#include "malloc.h"
#include "sdio_sdcard.h"  
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"   
#include "text.h"
#include "touch.h"
#include "beep.h" 
#include "rtc.h" 
#include "24cxx.h"

/************************************************
 ��ҵ��ƣ����ڵ�Ƭ���ĳ���Ĵ�����
 ��Ŀ����ʱ�䣺2022��4��
 ����֧�֣�www.openedv.com
 ���ߣ�������
 ָ����ʦ��ʩһ�ɸ�����
 �汾�ţ�2.0_Preview
************************************************/

 int main(void)
 {

	u8 key,t=0;
//	int u=0;
	int n=0;//ѭ����ȡ
//	u8 p=0;
	u8 a=1;
	u8 b=1;
	u8 c=1;
	u8 e=1;
	u32 HPhone_Number=0;
	u32 Phone_Number=0;
	u8 dis_hour,dis_min,dis_sec,cost;
	u32 Password=0;
	u8 box[16];
	u8 BoxN=16;
	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	usmart_dev.init(72);		//��ʼ��USMART		
 	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	BEEP_Init();         	//��ʼ���������˿�
	KEY_Init();					//��ʼ������
	LCD_Init();			   		//��ʼ��LCD   
	AT24CXX_Init();			//IIC��ʼ�� 
	usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART
	RTC_Init();	  			//RTC��ʼ��
	W25QXX_Init();				//��ʼ��W25Q128
	tp_dev.init();
 	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
 	f_mount(fs[0],"0:",1); 		//����SD�� 
 	f_mount(fs[1],"1:",1); 		//����FLASH.
	while(font_init()) 			//����ֿ�
	{
//UPD:
		LCD_Clear(WHITE);		   	//����
 		POINT_COLOR=RED;			//��������Ϊ��ɫ
		LCD_ShowString(30,50,200,16,16,"ELITE STM32F103 ^_^");
		while(SD_Init())			//���SD��
		{
			LCD_ShowString(30,70,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(30,70,200+30,70+16,WHITE);
			delay_ms(200);
		}
		LCD_ShowString(30,70,200,16,16,"SD Card OK");
		LCD_ShowString(30,90,200,16,16,"Font Updating...");
		key=update_font(20,110,16,"0:");//�����ֿ�
		while(key)//����ʧ��		
		{
			LCD_ShowString(30,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);
		} 		  
		LCD_ShowString(30,110,200,16,16,"Font Update Success!   ");
		delay_ms(1500);	
		LCD_Clear(WHITE);//����
	}
	
	while(1)//״̬��ѭ��
{
	
	
	{//������ʾ����
	//box[15]=1;
	//goto start;//������ʱ
	
choose:
	if(BEEP==1)
	{
		delay_ms(200);
		BEEP=0;
	}
//start:
	LCD_Clear(WHITE);	
	//��ʾ��ҳ����
	POINT_COLOR=RED;
	Show_Str_Mid(0,23,"���ڵ�Ƭ���ĳ���Ĵ�����",16,240);
	LCD_ShowString(41,83,200,16,16,"    -  -  ");
	LCD_ShowString(133,83,200,16,16,"  :  :  ");	    
	LCD_ShowNum(41,83,calendar.w_year,4,16);									  
	LCD_ShowNum(81,83,calendar.w_month,2,16);
	LCD_ShowNum(105,83,calendar.w_date,2,16);
	LCD_ShowNum(133,83,calendar.hour,2,16);									  
	LCD_ShowNum(157,83,calendar.min,2,16);									  
	LCD_ShowNum(181,83,calendar.sec,2,16);
	
//���������Ʋ���
//	for(u=1;u<1000;)
//	{
//		BEEP=1;
//		delay_us(u);
//		BEEP=0;
//		delay_us(1000-u);
//		u++;
//		if(u==1000)
//		{
//			for(u=1000;u>1;u--)
//			{
//				BEEP=1;
//				delay_us(u);
//				BEEP=0;
//				delay_us(1000-u);
//			}
//		}
//	}
//24C02����
//	for(n=0;n<16;)
//		{
//		delay_ms(500);
//		AT24CXX_WriteOneByte(n*10+4,rand() % 90 + 10);
//		AT24CXX_WriteOneByte(n*10+5,rand() % 90 + 10);
//		LCD_ShowNum(80,10,AT24CXX_ReadOneByte(n*10+4),2,12);
//		LCD_ShowNum(100,10,AT24CXX_ReadOneByte(n*10+5),2,12);
//		LCD_ShowNum(100,30,rand() % 9000 + 1000,5,12);
//		LCD_ShowNum(100,50,rand() % 9000 + 1000,5,12);
//		LCD_ShowNum(100,70,rand() % 9000 + 1000,5,12);
//		LCD_ShowNum(100,90,rand() % 9000 + 1000,5,12);
//		LCD_ShowNum(100,110,rand() % 9000 + 1000,5,12);
//		LCD_ShowNum(100,130,rand() % 9000 + 1000,5,12);
//		LCD_ShowNum(100,150,rand() % 9000 + 1000,5,12);
//		n++;
//		if(n==16)n=0;
//	}
	
	
	}	
		
		LCD_Fill(0,107,240,109,GRAY);
		LCD_Fill(0,150,240,152,GRAY);
		LCD_Fill(0,200,240,202,GRAY);
		LCD_Fill(0,250,240,252,GRAY);
		LCD_Fill(0,317,240,320,GRAY);

		LCD_Fill(0,107,2,320,GRAY);
		LCD_Fill(59,107,61,320,GRAY);
		LCD_Fill(119,107,121,320,GRAY);
		LCD_Fill(179,107,181,320,GRAY);
		LCD_Fill(237,107,240,320,GRAY);	
		
//		for(BoxN=0;BoxN<16;BoxN++)box[BoxN]=1;//���Ժ���ɫ��״̬ɫ���

		POINT_COLOR=BLACK;
//		for(n=0;n<16;n++)//���ԣ������ϢEEPROMȫ���Ŀ�
//		{
//			AT24CXX_WriteOneByte(10*n+0,0);
//			AT24CXX_WriteOneByte(10*n+1,0);
//			AT24CXX_WriteOneByte(n*10+2,0);
//			AT24CXX_WriteOneByte(n*10+3,0);
//			AT24CXX_WriteOneByte(n*10+4,0);
//			AT24CXX_WriteOneByte(n*10+5,0);
//		}
		for(n=0;n<16;n++)box[n]=AT24CXX_ReadOneByte(10*n);//��EEPROM�е�ȡ�������
		if(box[0]==0)
		{
			BACK_COLOR=GREEN;
			LCD_Fill(3,110,58,149,GREEN);
		}
		else
		{
			BACK_COLOR=RED;
			LCD_Fill(3,110,58,149,RED);
		}
		LCD_ShowString(41,110,20,20,16,"01");//ÿ������ϼӱ��
											//��л�Ƴ���ʦ����������
		if(box[1]==0)
		{
			BACK_COLOR=GREEN;
			LCD_Fill(62,110,118,149,GREEN);
		}
		else
		{
			BACK_COLOR=RED;
			LCD_Fill(62,110,118,149,RED);
		}
		LCD_ShowString(101,110,20,20,16,"02");
		if(box[2]==0)
		{
						BACK_COLOR=GREEN;
			LCD_Fill(122,110,178,149,GREEN);
		}
		else
		{
			BACK_COLOR=RED;
			LCD_Fill(122,110,178,149,RED);	
		}
		LCD_ShowString(162,110,20,20,16,"03");
		if(box[3]==0)
		{			
			BACK_COLOR=GREEN;
			LCD_Fill(182,110,236,149,GREEN);
		}
		else 
		{
			BACK_COLOR=RED;
			LCD_Fill(182,110,236,149,RED);
		}
		LCD_ShowString(219,110,20,20,16,"04");
		
		//�ڶ���
		if(box[4]==0)
		{
			BACK_COLOR=GREEN;
			LCD_Fill(3,153,58,199,GREEN);	
		}
		else
		{	
			BACK_COLOR=RED;		
			LCD_Fill(3,153,58,199,RED);	
		}
		LCD_ShowString(41,153,20,20,16,"05");
		if(box[5]==0)
		{
			BACK_COLOR=GREEN;
			LCD_Fill(62,153,118,199,GREEN);	
		}
		else 
		{	
			BACK_COLOR=RED;
			LCD_Fill(62,153,118,199,RED);
		}
		LCD_ShowString(101,153,20,20,16,"06");
		if(box[6]==0)
		{
			BACK_COLOR=GREEN;
			LCD_Fill(122,153,178,199,GREEN);	
		}
		else 
		{	
			BACK_COLOR=RED;
			LCD_Fill(122,153,178,199,RED);
		}
		LCD_ShowString(162,153,20,20,16,"07");
		if(box[7]==0)
		{		
			BACK_COLOR=GREEN;
			LCD_Fill(182,153,236,199,GREEN);	
		}
		else 
		{
			BACK_COLOR=RED;
			LCD_Fill(182,153,236,199,RED);	
		}
		LCD_ShowString(219,153,20,20,16,"08");
		
		
		
		//������
		if(box[8]==0)
		{
			BACK_COLOR=GREEN;
			LCD_Fill(3,203,58,249,GREEN);	
		}
		else 
		{
			BACK_COLOR=RED;
			LCD_Fill(3,203,58,249,RED);
		}
		LCD_ShowString(41,203,20,20,16,"09");
		if(box[9]==0)
		{
			BACK_COLOR=GREEN;
			LCD_Fill(62,203,118,249,GREEN);
		}
		else 
		{
			BACK_COLOR=RED;
			LCD_Fill(62,203,118,249,RED);
		}
		LCD_ShowString(101,203,20,20,16,"10");
		if(box[10]==0)
		{
			BACK_COLOR=GREEN;
			LCD_Fill(122,203,178,249,GREEN);	
		}
		else 
		{
			BACK_COLOR=RED;
			LCD_Fill(122,203,178,249,RED);
		}
		LCD_ShowString(162,203,20,20,16,"11");
		if(box[11]==0)
		{
			BACK_COLOR=GREEN;
			LCD_Fill(182,203,236,249,GREEN);
		}
		else 
		{
			BACK_COLOR=RED;
			LCD_Fill(182,203,236,249,RED);
		}
		LCD_ShowString(219,203,20,20,16,"12");
		
		
		//������
		if(box[12]==0)
		{
			BACK_COLOR=GREEN;
			LCD_Fill(3,253,58,316,GREEN);	
		}
		else 
		{
			BACK_COLOR=RED;
			LCD_Fill(3,253,58,316,RED);
		}
		LCD_ShowString(41,253,20,20,16,"13");
		if(box[13]==0)
		{
			BACK_COLOR=GREEN;
			LCD_Fill(62,253,118,316,GREEN);	
		}
		else 
		{
			BACK_COLOR=RED;
			LCD_Fill(62,253,118,316,RED);
		}
		LCD_ShowString(101,253,20,20,16,"14");
		if(box[14]==0)
		{
			BACK_COLOR=GREEN;
			LCD_Fill(122,253,178,316,GREEN);	
		}
		else 
		{
			BACK_COLOR=RED;
			LCD_Fill(122,253,178,316,RED);
		}
		LCD_ShowString(162,253,20,20,16,"15");
		if(box[15]==0)
		{
			BACK_COLOR=GREEN;
			LCD_Fill(182,253,236,316,GREEN);	
		}
		else 
		{
			BACK_COLOR=RED;
			LCD_Fill(182,253,236,316,RED);
		}	
		LCD_ShowString(219,253,20,20,16,"16");	
		
		POINT_COLOR=BLUE;
		BACK_COLOR=WHITE;
		if(box[0]==0 || box[1]==0 || box[2]==0 || box[3]==0 || box[4]==0 || box[5]==0 || box[6]==0 || box[7]==0 || box[8]==0 || box[9]==0 || box[10]==0 || box[11]==0 || box[12]==0 || box[13]==0 || box[14]==0 || box[15]==0)
			Show_Str_Mid(0,47,"��ѡ��Ĵ��",24,240);
		else Show_Str_Mid(0,47,"��Ǹ���Ĵ������",24,240);

		
		
		
	while(c)
	{//��λѡ��ȴ�״̬����ҳ��


		//������ʾ
		POINT_COLOR=RED;							    
		if(t!=calendar.sec)	   //����ʱ��	
		{
			t=calendar.sec;
			LCD_ShowNum(41,83,calendar.w_year,4,16);									  
			LCD_ShowNum(81,83,calendar.w_month,2,16);
			LCD_ShowNum(105,83,calendar.w_date,2,16);

			LCD_ShowNum(133,83,calendar.hour,2,16);									  
			LCD_ShowNum(157,83,calendar.min,2,16);									  
			LCD_ShowNum(181,83,calendar.sec,2,16);
			LED0=!LED0;
			POINT_COLOR=BRRED;
			if(LED0==1)
			{
				if(box[0]==1 || box[1]==1 || box[2]==1 || box[3]==1 || box[4]==1 || box[5]==1 || box[6]==1 || box[7]==1 || box[8]==1 || box[9]==1 || box[10]==1 || box[11]==1 || box[12]==1 || box[13]==1 || box[14]==1 || box[15]==1)
				Show_Str_Mid(8,4,"���｡��״�������...",12,240);
				//������Ӳ����δ��λ
			}else LCD_Fill(8,4,200,16,WHITE);
			
		
			key=KEY_Scan(0);
			if(key==KEY0_PRES)	//KEY0����,��ִ��У׼����
			{
				LCD_Clear(WHITE);//����
				TP_Adjust();  	//��ĻУ׼  
			}
		}
		
		//��ѡɨ��
		tp_dev.scan(0);
		if(tp_dev.sta & TP_PRES_DOWN)			
		{//���������
		 	if(tp_dev.x[0]<lcddev.width && tp_dev.y[0]<lcddev.height)
			{
				if(tp_dev.x[0]>0&&tp_dev.x[0]<60 && tp_dev.y[0]>110&&tp_dev.y[0]<150)
				{//0
					BoxN=0;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(3,110,58,149,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}
				}
				else if(tp_dev.x[0]>60&&tp_dev.x[0]<120 && tp_dev.y[0]>110&&tp_dev.y[0]<150)
				{//1
					BoxN=1;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(62,110,118,149,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}				
				}
				else if(tp_dev.x[0]>120&&tp_dev.x[0]<180 && tp_dev.y[0]>110&&tp_dev.y[0]<150)
				{//2
					BoxN=2;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(122,110,178,149,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}				
				}
				else if(tp_dev.x[0]>180&&tp_dev.x[0]<240 && tp_dev.y[0]>110&&tp_dev.y[0]<150)
				{//3
					BoxN=3;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(182,110,236,149,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}				
				}
				////////�ڶ��а���
				else if(tp_dev.x[0]>0&&tp_dev.x[0]<60 && tp_dev.y[0]>151&&tp_dev.y[0]<200)
				{//4
					BoxN=4;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(3,153,58,199,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}				
				}
				else if(tp_dev.x[0]>60&&tp_dev.x[0]<120 && tp_dev.y[0]>151&&tp_dev.y[0]<200)
				{//5
					BoxN=5;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(62,153,118,199,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}
				}
				else if(tp_dev.x[0]>120&&tp_dev.x[0]<180 && tp_dev.y[0]>151&&tp_dev.y[0]<200)
				{//6
					BoxN=6;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(122,153,178,199,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}
				}
				else if(tp_dev.x[0]>180&&tp_dev.x[0]<240 && tp_dev.y[0]>151&&tp_dev.y[0]<200)
				{//7
					BoxN=7;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(182,153,236,199,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}
				}
				////////�����а���
				else if(tp_dev.x[0]>0&&tp_dev.x[0]<60 && tp_dev.y[0]>201&&tp_dev.y[0]<250)
				{//8
					BoxN=8;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(3,203,58,249,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}
				}
				else if(tp_dev.x[0]>60&&tp_dev.x[0]<120 && tp_dev.y[0]>201&&tp_dev.y[0]<250)
				{//9
					BoxN=9;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(62,203,118,249,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}
				}
				else if(tp_dev.x[0]>120&&tp_dev.x[0]<180 && tp_dev.y[0]>201&&tp_dev.y[0]<250)
				{///10
					BoxN=10;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(122,203,178,249,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}
				}
				else if(tp_dev.x[0]>180&&tp_dev.x[0]<240 && tp_dev.y[0]>201&&tp_dev.y[0]<250)
				{//11
					BoxN=11;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(182,203,236,249,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}
				}
				////////�����а���
				else if(tp_dev.x[0]>0&&tp_dev.x[0]<60 && tp_dev.y[0]>251&&tp_dev.y[0]<320)
				{//12
					BoxN=12;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(3,253,58,316,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}
				}
				else if(tp_dev.x[0]>60&&tp_dev.x[0]<120 && tp_dev.y[0]>251&&tp_dev.y[0]<320)
				{//13
					BoxN=13;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(62,253,118,316,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}
				}
				else if(tp_dev.x[0]>120&&tp_dev.x[0]<180 && tp_dev.y[0]>251&&tp_dev.y[0]<320)
				{///14
					BoxN=14;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(122,253,178,316,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}
				}
				else if(tp_dev.x[0]>180&&tp_dev.x[0]<240 && tp_dev.y[0]>251&&tp_dev.y[0]<320)
				{//15
					BoxN=15;
					if(box[BoxN]==0)
					{
						BEEP=1;
						LCD_Fill(182,253,236,316,BRRED);
					}
					else
					{
						BEEP=1;
						goto pwp;
					}
				}
				
				//������ԡ�
				delay_ms(250);
				if(BEEP==1)	
				{	
					LCD_Clear(WHITE);
					c=0;//�չ�ѡ�У������������״̬
				}		
				
			}
			BEEP=0;
		}else delay_ms(10);	//û�а������µ�ʱ��
//	while(1);
	}
	
	
	
	
	
	{//�����������
	POINT_COLOR=RED;
	Show_Str_Mid(0,23,"���ڵ�Ƭ���ĳ���Ĵ�����",16,240);
	//��ʾʱ��
	POINT_COLOR=RED;//��������Ϊ��ɫ
	LCD_ShowString(41,83,200,16,16,"    -  -  ");
	LCD_ShowString(133,83,200,16,16,"  :  :  ");
	LCD_ShowNum(41,83,calendar.w_year,4,16);									  
	LCD_ShowNum(81,83,calendar.w_month,2,16);
	LCD_ShowNum(105,83,calendar.w_date,2,16);
	LCD_ShowNum(133,83,calendar.hour,2,16);									  
	LCD_ShowNum(157,83,calendar.min,2,16);									  
	LCD_ShowNum(181,83,calendar.sec,2,16);
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,107,"������Ļ����λ����",16,240);
	Show_Str_Mid(0,47,"�������ֻ���",24,240);
	POINT_COLOR=BROWN;
	Show_Str(26,183,40,24,"1",24,0);
	Show_Str(86,183,40,24,"2",24,0);
	Show_Str(145,183,40,24,"3",24,0);
	Show_Str(26,233,40,24,"4",24,0);
	Show_Str(86,233,40,24,"5",24,0);
	Show_Str(145,233,40,24,"6",24,0);
	Show_Str(26,282,40,24,"7",24,0);
	Show_Str(86,282,40,24,"8",24,0);
	Show_Str(145,282,40,24,"9",24,0);
	Show_Str(185,182,50,24,"ȷ��",24,0);
	Show_Str(185,232,50,24,"�س�",24,0);
 	Show_Str(204,282,40,24,"0",24,0);
	LCD_Fill(0,126,240,128,GRAY);
	LCD_Fill(0,170,240,172,GRAY);
	LCD_Fill(0,220,240,222,GRAY);
	LCD_Fill(0,270,240,272,GRAY);
	LCD_Fill(0,317,240,320,GRAY);
	LCD_Fill(0,126,2,320,GRAY);
	LCD_Fill(59,170,61,320,GRAY);
	LCD_Fill(119,170,121,320,GRAY);
	LCD_Fill(179,170,181,320,GRAY);
	LCD_Fill(237,126,240,320,GRAY);
	}
	
	
	
	while(a)
	{//��������״̬����ҳ��
		
		POINT_COLOR=RED;							    
		if(t!=calendar.sec)					   //����ʱ��	
		{
			t=calendar.sec;
			LCD_ShowNum(41,83,calendar.w_year,4,16);									  
			LCD_ShowNum(81,83,calendar.w_month,2,16);
			LCD_ShowNum(105,83,calendar.w_date,2,16);

			LCD_ShowNum(133,83,calendar.hour,2,16);									  
			LCD_ShowNum(157,83,calendar.min,2,16);									  
			LCD_ShowNum(181,83,calendar.sec,2,16);
			LED0=!LED0;
			POINT_COLOR=BRRED;
			if(LED0==1)
			{
				if(box[0]==1 || box[1]==1 || box[2]==1 || box[3]==1 || box[4]==1 || box[5]==1 || box[6]==1 || box[7]==1 || box[8]==1 || box[9]==1 || box[10]==1 || box[11]==1 || box[12]==1 || box[13]==1 || box[14]==1 || box[15]==1)
				Show_Str_Mid(8,4,"���｡��״�������...",12,240);
			}else LCD_Fill(8,4,200,16,WHITE);
		}
		POINT_COLOR=RED;
		tp_dev.scan(0);
		if(tp_dev.sta & TP_PRES_DOWN)			//������������
		{
		 	if(tp_dev.x[0]<lcddev.width && tp_dev.y[0]<lcddev.height)
			{				
				if(Phone_Number>0x63 && Phone_Number<0x3e8 && HPhone_Number==0)
				{//�ж��Ƿ�����ǰ�벿��
					HPhone_Number=Phone_Number;
					Phone_Number=0;
					LCD_Fill(173,130,183,150,WHITE);
					LCD_ShowNum(50,136,HPhone_Number,3,24);//���ӱ�־λ
				}
//				if(HPhone_Number>0 && Phone_Number==0)    //bug
//				{
//					Phone_Number=HPhone_Number;
//					HPhone_Number=0;
//					LCD_ShowNum(50,136,0,3,24);
//					LCD_ShowNum(88,136,Phone_Number,8,24);
//				}
				
				
				
				if(tp_dev.x[0]>0&&tp_dev.x[0]<60 && tp_dev.y[0]>170&&tp_dev.y[0]<220)
				{//1
					//while(c)if(tp_dev.x[0]>lcddev.width || tp_dev.y[0]>lcddev.height)c=0;//ʧ�ܵ����ּ�ⷨ
					Phone_Number=Phone_Number*10+1;
					BEEP=1;
					LCD_ShowNum(88,136,Phone_Number,8,24);
				}
				else if(tp_dev.x[0]>60&&tp_dev.x[0]<120 && tp_dev.y[0]>170&&tp_dev.y[0]<220)
				{//2
					Phone_Number=Phone_Number*10+2;
					BEEP=1;
					LCD_ShowNum(88,136,Phone_Number,8,24);
				}
				else if(tp_dev.x[0]>120&&tp_dev.x[0]<180 && tp_dev.y[0]>170&&tp_dev.y[0]<220)
				{//3
					Phone_Number=Phone_Number*10+3;
					BEEP=1;
					LCD_ShowNum(88,136,Phone_Number,8,24);
				}
//				else if(tp_dev.x[0]>180&&tp_dev.x[0]<240 && tp_dev.y[0]>170&&tp_dev.y[0]<220)
//				{//ȷ����//������һѭ��
//					BEEP=1;
//					LCD_ShowNum(88,136,Phone_Number,8,24);
//				}
				////////�ڶ��а���
				else if(tp_dev.x[0]>0&&tp_dev.x[0]<60 && tp_dev.y[0]>220&&tp_dev.y[0]<270)
				{//4
					Phone_Number=Phone_Number*10+4;
					BEEP=1;
					LCD_ShowNum(88,136,Phone_Number,8,24);
				}
				else if(tp_dev.x[0]>60&&tp_dev.x[0]<120 && tp_dev.y[0]>220&&tp_dev.y[0]<270)
				{//5
					Phone_Number=Phone_Number*10+5;
					BEEP=1;
					LCD_ShowNum(88,136,Phone_Number,8,24);
				}
				else if(tp_dev.x[0]>120&&tp_dev.x[0]<180 && tp_dev.y[0]>220&&tp_dev.y[0]<270)
				{//6
					Phone_Number=Phone_Number*10+6;
					BEEP=1;
					LCD_ShowNum(88,136,Phone_Number,8,24);
				}
				else if(tp_dev.x[0]>180&&tp_dev.x[0]<240 && tp_dev.y[0]>220&&tp_dev.y[0]<270)
				{//ɾ��					
					if(Phone_Number==0 && HPhone_Number==0)
					{
						BEEP=1;a=1;c=1;
						goto choose;//���delay_ms(200);BEEP=0;
					}
pnum://�ص���������״̬
					BEEP=1;
					if(Phone_Number!=0)
					{
						Phone_Number/=10;
					}
					else 
					{
						Phone_Number=HPhone_Number/10;
						HPhone_Number=0;
						LCD_Fill(50,130,84,160,WHITE);
					}
					if(Phone_Number==0)LCD_Fill(173,130,183,160,WHITE);
					else LCD_ShowNum(88,136,Phone_Number,8,24);
				}
				////////�����а���
				else if(tp_dev.x[0]>0&&tp_dev.x[0]<60 && tp_dev.y[0]>270&&tp_dev.y[0]<320)
				{//7
					Phone_Number=Phone_Number*10+7;
					BEEP=1;
					LCD_ShowNum(88,136,Phone_Number,8,24);
				}
				else if(tp_dev.x[0]>60&&tp_dev.x[0]<120 && tp_dev.y[0]>270&&tp_dev.y[0]<320)
				{//8
					Phone_Number=Phone_Number*10+8;
					BEEP=1;
					LCD_ShowNum(88,136,Phone_Number,8,24);
				}
				else if(tp_dev.x[0]>120&&tp_dev.x[0]<180 && tp_dev.y[0]>270&&tp_dev.y[0]<320)
				{///9
					Phone_Number=Phone_Number*10+9;
					BEEP=1;
					LCD_ShowNum(88,136,Phone_Number,8,24);
				}
				else if(tp_dev.x[0]>180&&tp_dev.x[0]<240 && tp_dev.y[0]>270&&tp_dev.y[0]<320)
				{//0
					Phone_Number=Phone_Number*10;
					BEEP=1;
					LCD_ShowNum(88,136,Phone_Number,8,24);
				}
				//BEEP=0;//�������
				if(Phone_Number>0x98967F)//�绰����������ֹ��ǰ����ѭ����׼�����Ͷ���
				{
					a=0;b=1;goto bp;
				}
			}
			delay_ms(200);
			BEEP=0;
		}else delay_ms(10);	//û�а������µ�ʱ��
		
//		c=1;
//		p++;
//		if(p%20==0)LED0=!LED0;
		
	}
	
	
	
	
pwp:
	{//�����������
	delay_ms(100);
	BEEP=0;
	LCD_Clear(WHITE);
	POINT_COLOR=RED;
	Show_Str_Mid(0,23,"���ڵ�Ƭ���ĳ���Ĵ�����",16,240);
	LCD_ShowString(41,83,200,16,16,"    -  -  ");	//��ʾʱ��
	LCD_ShowString(133,83,200,16,16,"  :  :  ");
	LCD_ShowNum(41,83,calendar.w_year,4,16);									  
	LCD_ShowNum(81,83,calendar.w_month,2,16);
	LCD_ShowNum(105,83,calendar.w_date,2,16);
	LCD_ShowNum(133,83,calendar.hour,2,16);									  
	LCD_ShowNum(157,83,calendar.min,2,16);									  
	LCD_ShowNum(181,83,calendar.sec,2,16);
	POINT_COLOR=MAGENTA;	
	Show_Str_Mid(0,47,"����������",24,240);
	Show_Str_Mid(0,107,"������Ļ����λ����",16,240);
	POINT_COLOR=BROWN;
	Show_Str(26,183,40,24,"1",24,0);			//���̲���
	Show_Str(86,183,40,24,"2",24,0);
	Show_Str(145,183,40,24,"3",24,0);
	Show_Str(26,233,40,24,"4",24,0);
	Show_Str(86,233,40,24,"5",24,0);
	Show_Str(145,233,40,24,"6",24,0);
	Show_Str(26,282,40,24,"7",24,0);
	Show_Str(86,282,40,24,"8",24,0);
	Show_Str(145,282,40,24,"9",24,0);
	Show_Str(185,182,50,24,"ȷ��",24,0);
	Show_Str(185,232,50,24,"�س�",24,0);
	Show_Str(204,282,40,24,"0",24,0);
	LCD_Fill(0,126,240,128,GRAY);
	LCD_Fill(0,170,240,172,GRAY);
	LCD_Fill(0,220,240,222,GRAY);
	LCD_Fill(0,270,240,272,GRAY);
	LCD_Fill(0,317,240,320,GRAY);
	LCD_Fill(0,126,2,320,GRAY);
	LCD_Fill(59,170,61,320,GRAY);
	LCD_Fill(119,170,121,320,GRAY);
	LCD_Fill(179,170,181,320,GRAY);
	LCD_Fill(237,126,240,320,GRAY);
	POINT_COLOR=RED;
	LCD_ShowNum(209,0,AT24CXX_ReadOneByte(BoxN*10+4),2,12);//����ʱ��֪����
	LCD_ShowNum(221,0,AT24CXX_ReadOneByte(BoxN*10+5),2,12);

	}
	while(e)
	{//��������״̬����ҳ��
		POINT_COLOR=RED;							    
		if(t!=calendar.sec)					   //����ʱ��	
		{
			t=calendar.sec;
			LCD_ShowNum(41,83,calendar.w_year,4,16);									  
			LCD_ShowNum(81,83,calendar.w_month,2,16);
			LCD_ShowNum(105,83,calendar.w_date,2,16);

			LCD_ShowNum(133,83,calendar.hour,2,16);									  
			LCD_ShowNum(157,83,calendar.min,2,16);									  
			LCD_ShowNum(181,83,calendar.sec,2,16);
			LED0=!LED0;
			POINT_COLOR=BRRED;
			if(LED0==1)
			{
				if(box[0]==1 || box[1]==1 || box[2]==1 || box[3]==1 || box[4]==1 || box[5]==1 || box[6]==1 || box[7]==1 || box[8]==1 || box[9]==1 || box[10]==1 || box[11]==1 || box[12]==1 || box[13]==1 || box[14]==1 || box[15]==1)
				Show_Str_Mid(8,4,"���｡��״�������...",12,240);
			}else LCD_Fill(8,4,200,16,WHITE);
		}
		
		POINT_COLOR=RED;
		tp_dev.scan(0);
		if(tp_dev.sta & TP_PRES_DOWN)			//������������
		{
		 	if(tp_dev.x[0]<lcddev.width && tp_dev.y[0]<lcddev.height)
			{
				if(tp_dev.x[0]>0&&tp_dev.x[0]<60 && tp_dev.y[0]>170&&tp_dev.y[0]<220)
				{//1
					Password=Password*10+1;
					BEEP=1;
					LCD_ShowNum(88,136,Password,8,24);
				}
				else if(tp_dev.x[0]>60&&tp_dev.x[0]<120 && tp_dev.y[0]>170&&tp_dev.y[0]<220)
				{//2
					Password=Password*10+2;
					BEEP=1;
					LCD_ShowNum(88,136,Password,8,24);
				}
				else if(tp_dev.x[0]>120&&tp_dev.x[0]<180 && tp_dev.y[0]>170&&tp_dev.y[0]<220)
				{//3
					Password=Password*10+3;
					BEEP=1;
					LCD_ShowNum(88,136,Password,8,24);
				}
				////////�ڶ��а���
				else if(tp_dev.x[0]>0&&tp_dev.x[0]<60 && tp_dev.y[0]>220&&tp_dev.y[0]<270)
				{//4
					Password=Password*10+4;
					BEEP=1;
					LCD_ShowNum(88,136,Password,8,24);
				}
				else if(tp_dev.x[0]>60&&tp_dev.x[0]<120 && tp_dev.y[0]>220&&tp_dev.y[0]<270)
				{//5
					Password=Password*10+5;
					BEEP=1;
					LCD_ShowNum(88,136,Password,8,24);
				}
				else if(tp_dev.x[0]>120&&tp_dev.x[0]<180 && tp_dev.y[0]>220&&tp_dev.y[0]<270)
				{//6
					Password=Password*10+6;
					BEEP=1;
					LCD_ShowNum(88,136,Password,8,24);
				}
				else if(tp_dev.x[0]>180&&tp_dev.x[0]<240 && tp_dev.y[0]>220&&tp_dev.y[0]<270)
				{//ɾ��		
					BEEP=1;			
					if(Password==0)
					{
						a=1;c=1;
						goto choose;//���delay_ms(200);BEEP=0;
					}
					else
					{
						Password/=10;
					}
					if(Password==0)LCD_Fill(173,130,183,160,WHITE);
					else LCD_ShowNum(88,136,Password,8,24);
				}
				////////�����а���
				else if(tp_dev.x[0]>0&&tp_dev.x[0]<60 && tp_dev.y[0]>270&&tp_dev.y[0]<320)
				{//7
					Password=Password*10+7;
					BEEP=1;
					LCD_ShowNum(88,136,Password,8,24);
				}
				else if(tp_dev.x[0]>60&&tp_dev.x[0]<120 && tp_dev.y[0]>270&&tp_dev.y[0]<320)
				{//8
					Password=Password*10+8;
					BEEP=1;
					LCD_ShowNum(88,136,Password,8,24);
				}
				else if(tp_dev.x[0]>120&&tp_dev.x[0]<180 && tp_dev.y[0]>270&&tp_dev.y[0]<320)
				{///9
					Password=Password*10+9;
					BEEP=1;
					LCD_ShowNum(88,136,Password,8,24);
				}
				else if(tp_dev.x[0]>180&&tp_dev.x[0]<240 && tp_dev.y[0]>270&&tp_dev.y[0]<320)
				{//0
					Password=Password*10;
					BEEP=1;
					LCD_ShowNum(88,136,Password,8,24);
				}
				
				//BEEP=0;//�������
				
				if(Password == AT24CXX_ReadOneByte(BoxN*10+4)*100+AT24CXX_ReadOneByte(BoxN*10+5))//������ȷ����ֹ��ǰ����ѭ����
				{
					Password=0;
					//�������
					BEEP=1;
					//��ʾ���ͽ���					
					LCD_Clear(WHITE);
					t=calendar.sec;			//����ʹ��ʱ�䲢�Ʒ���ʾ
					dis_sec=calendar.sec-AT24CXX_ReadOneByte(BoxN*10+3);
					dis_min=calendar.min-AT24CXX_ReadOneByte(BoxN*10+2);					
					dis_hour=calendar.hour-AT24CXX_ReadOneByte(BoxN*10+1);
					POINT_COLOR=BLUE;					
					Show_Str_Mid(0,87,"���ι�ʹ��",24,240);
					Show_Str_Mid(0,163,"��������",24,240);
					POINT_COLOR=RED;
					LCD_ShowNum(24,120,dis_hour,2,24);
					LCD_ShowNum(96,120,dis_min,2,24);
					LCD_ShowNum(170,120,dis_sec,2,24);
					Show_Str_Mid(46,120,"Сʱ",24,48);
					Show_Str_Mid(121,120,"����",24,48);
					Show_Str_Mid(193,120,"��",24,24);
					cost=(dis_sec+60*dis_min+3600*dis_hour)/5;
					LCD_ShowNum(80,196,cost,3,24);
					Show_Str_Mid(127,196,"Ԫ",24,24);
					//����
					AT24CXX_WriteOneByte(BoxN*10,0);//�ͷŸù�
					AT24CXX_WriteOneByte(BoxN*10+1,00);//�ͷ�ʱ���ǩ
					AT24CXX_WriteOneByte(BoxN*10+2,00);
					AT24CXX_WriteOneByte(BoxN*10+3,00);
					AT24CXX_WriteOneByte(BoxN*10+4,00);//�ͷ��������
					AT24CXX_WriteOneByte(BoxN*10+5,00);
//					AT24CXX_WriteOneByte(160+BoxN,00);//�ͷźŶ�
//					AT24CXX_WriteOneByte(BoxN*10+6,00);//�ͷŵ绰��				
//					AT24CXX_WriteOneByte(BoxN*10+7,00);//�ͷ�ָ�� 
					box[BoxN]=0;
					BoxN=16;
					delay_ms(600);
					BEEP=0;
					delay_ms(700);
					a=1;b=1;c=1;
//					while(1);
					goto choose;					
					
				}
			}
			delay_ms(200);
			BEEP=0;
		}else delay_ms(10);	//û�а������µ�ʱ��
		
	}
	
	
	
	
	
	while(b)
	{//���ŷ���״̬����ҳ��
bp:
		POINT_COLOR=RED;	 //����ʱ�䣬�ȴ���������			    
		if(t!=calendar.sec)
		{
			t=calendar.sec;
			LCD_ShowNum(41,83,calendar.w_year,4,16);									  
			LCD_ShowNum(81,83,calendar.w_month,2,16);
			LCD_ShowNum(105,83,calendar.w_date,2,16);
			LCD_ShowNum(133,83,calendar.hour,2,16);									  
			LCD_ShowNum(157,83,calendar.min,2,16);									  
			LCD_ShowNum(181,83,calendar.sec,2,16);
			LED0=!LED0;
		}
		tp_dev.scan(0);
		if(tp_dev.sta & TP_PRES_DOWN)			//������������
		{
		 	if(tp_dev.x[0]<lcddev.width && tp_dev.y[0]<lcddev.height)
			{				
				if(tp_dev.x[0]>180&&tp_dev.x[0]<240 && tp_dev.y[0]>170&&tp_dev.y[0]<220)
				{//ȷ����ť
					BEEP=1;
					//BEEP=0;//�������
					//��ʾ���ͽ���					
					LCD_Clear(WHITE);
					POINT_COLOR=RED;
					LCD_ShowString(41,83,200,16,16,"    -  -  ");
					LCD_ShowString(133,83,200,16,16,"  :  :  ");
					t=calendar.sec;
					LCD_ShowNum(41,83,calendar.w_year,4,16);									  
					LCD_ShowNum(81,83,calendar.w_month,2,16);
					LCD_ShowNum(105,83,calendar.w_date,2,16);
					LCD_ShowNum(133,83,calendar.hour,2,16);									  
					LCD_ShowNum(157,83,calendar.min,2,16);									  
					LCD_ShowNum(181,83,calendar.sec,2,16);
					
					//����������룬������
					AT24CXX_WriteOneByte(BoxN*10+4,rand() % 90 + 10);
					AT24CXX_WriteOneByte(BoxN*10+5,rand() % 90 + 10);
					LCD_ShowNum(209,0,AT24CXX_ReadOneByte(BoxN*10+4),2,12);//����ʱ��ʾ����
					LCD_ShowNum(221,0,AT24CXX_ReadOneByte(BoxN*10+5),2,12);	
					
					//����ȡ��������ţ�Ӳ��δ��λ			
					
					POINT_COLOR=BLUE;
					Show_Str_Mid(0,147,"ȡ����������ѷ���",24,240);
					
					AT24CXX_WriteOneByte(BoxN*10+0,1);//��ǰ�����г��� ��־λ����EEPROM
					AT24CXX_WriteOneByte(BoxN*10+3,calendar.sec);//��ס��ǰʱ��
					AT24CXX_WriteOneByte(BoxN*10+2,calendar.min);
					AT24CXX_WriteOneByte(BoxN*10+1,calendar.hour);
					
					HPhone_Number=0;//��ʼ�����������´���
					Phone_Number=0;
					Password=0;
					box[BoxN]=1;
					BoxN=16;
					
					delay_ms(600);
					BEEP=0;
					delay_ms(700);
					a=1;b=1;c=1;
					//while(1);
					break;
					
				}
				else if(tp_dev.x[0]>180&&tp_dev.x[0]<240 && tp_dev.y[0]>220&&tp_dev.y[0]<270)
				{//ɾ����ť,b=0��������ѯ��������λ��
					a=1;c=1;b=1;
					goto pnum;
				}
				delay_ms(200);
				BEEP=0;
			}
		}else delay_ms(10);	//û�а������µ�ʱ��
	
	
	
	
	
	
	
	
	
	}
	
	
	
	
}








//	u32 fontcnt;		  
//	u8 i,j;
//	u8 fontx[2];//gbk��
//	while(1)
//	{
//		fontcnt=0;
//		for(i=0x81;i<0xff;i++)
//		{		
//			fontx[0]=i;
//			LCD_ShowNum(118,150,i,3,16);		//��ʾ������ֽ�    
//			for(j=0x40;j<0xfe;j++)
//			{
//				if(j==0x7f)continue;
//				fontcnt++;
//				LCD_ShowNum(118,170,j,3,16);	//��ʾ������ֽ�	 
//				LCD_ShowNum(118,190,fontcnt,5,16);//���ּ�����ʾ	 
//			 	fontx[1]=j;
//				Show_Font(30+132,220,fontx,24,0);	  
//				Show_Font(30+144,244,fontx,16,0);	  		 		 
//				Show_Font(30+108,260,fontx,12,0);	  		 		 
//				t=200;
//				while(t--)//��ʱ,ͬʱɨ�谴���������ֿ�
//				{
//					delay_ms(1);
//					key=KEY_Scan(0);
//					if(key==KEY0_PRES)goto UPD;
//				}
//				LED0=!LED0;
//			}   
//		}	
//	}

 
}
