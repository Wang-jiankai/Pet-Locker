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
#include "adc.h"

/************************************************
 毕业设计：基于单片机的宠物寄存柜设计
 项目启动时间：2022年4月
 技术支持：www.openedv.com
 作者：王建凯
 指导教师：施一飞副教授
 版本号：2.0_Preview
************************************************/

 int main(void)
 {

	u8 key,t=0;
//	int u=0;
	int n=0;//循环读取
	u8 p=0;
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
	u16 adcx;
	float temp;
	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	usmart_dev.init(72);		//初始化USMART		
 	LED_Init();		  			//初始化与LED连接的硬件接口
	BEEP_Init();         	//初始化蜂鸣器端口
	KEY_Init();					//初始化按键
	LCD_Init();			   		//初始化LCD
	Adc_Init();		  		//ADC初始化
	AT24CXX_Init();			//IIC初始化 
	usmart_dev.init(SystemCoreClock/1000000);	//初始化USMART
	RTC_Init();	  			//RTC初始化
	W25QXX_Init();				//初始化W25Q128
	tp_dev.init();
 	my_mem_init(SRAMIN);		//初始化内部内存池
	exfuns_init();				//为fatfs相关变量申请内存
 	f_mount(fs[0],"0:",1); 		//挂载SD卡
 	f_mount(fs[1],"1:",1); 		//挂载FLASH.
	while(font_init()) 			//检查字库
	{
//UPD:
		LCD_Clear(WHITE);		   	//清屏
 		POINT_COLOR=RED;			//设置字体为红色
		LCD_ShowString(30,50,200,16,16,"ELITE STM32F103 ^_^");
		while(SD_Init())			//检测SD卡
		{
			LCD_ShowString(30,70,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(30,70,200+30,70+16,WHITE);
			delay_ms(200);
		}
		LCD_ShowString(30,70,200,16,16,"SD Card OK");
		LCD_ShowString(30,90,200,16,16,"Font Updating...");
		key=update_font(20,110,16,"0:");//更新字库
		while(key)//更新失败		
		{
			LCD_ShowString(30,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);
		} 		  
		LCD_ShowString(30,110,200,16,16,"Font Update Success!   ");
		delay_ms(1500);	
		LCD_Clear(WHITE);//清屏
	}
	
	while(1)//状态大循环
{
	
	
	{//基础显示界面
	//box[15]=1;
	//goto start;//跳过延时
	
choose:
	if(BEEP==1)
	{
		delay_ms(200);
		BEEP=0;
	}
//start:
	LCD_Clear(WHITE);	
	//显示首页界面
	POINT_COLOR=RED;
	Show_Str_Mid(0,23,"基于单片机的宠物寄存柜设计",16,240);
	LCD_ShowString(41,83,200,16,16,"    -  -  ");
	LCD_ShowString(133,83,200,16,16,"  :  :  ");	    
	LCD_ShowNum(41,83,calendar.w_year,4,16);									  
	LCD_ShowNum(81,83,calendar.w_month,2,16);
	LCD_ShowNum(105,83,calendar.w_date,2,16);
	LCD_ShowNum(133,83,calendar.hour,2,16);									  
	LCD_ShowNum(157,83,calendar.min,2,16);									  
	LCD_ShowNum(181,83,calendar.sec,2,16);
	
//蜂鸣器控制测试
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
//24C02测试
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
		
//		for(BoxN=0;BoxN<16;BoxN++)box[BoxN]=1;//测试红颜色柜状态色填充

		POINT_COLOR=BLACK;
//		for(n=0;n<16;n++)//调试，柜存信息EEPROM全部改空
//		{
//			AT24CXX_WriteOneByte(10*n+0,0);
//			AT24CXX_WriteOneByte(10*n+1,0);
//			AT24CXX_WriteOneByte(n*10+2,0);
//			AT24CXX_WriteOneByte(n*10+3,0);
//			AT24CXX_WriteOneByte(n*10+4,0);
//			AT24CXX_WriteOneByte(n*10+5,0);
//		}
		for(n=0;n<16;n++)box[n]=AT24CXX_ReadOneByte(10*n);//从EEPROM中调取空置情况
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
		LCD_ShowString(41,110,20,20,16,"01");//每格柜右上加编号
											//感谢黄成老师提出宝贵意见
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
		
		//第二行
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
		
		
		
		//第三行
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
		
		
		//第四行
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
			Show_Str_Mid(0,47,"请选择寄存柜",24,240);
		else Show_Str_Mid(0,47,"抱歉，寄存柜已满",24,240);

		
		
		
	while(c)
	{//柜位选择等待状态（首页）


		//界面显示
		POINT_COLOR=RED;							    
		if(t!=calendar.sec)	   //更新时间	
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
				Show_Str_Mid(8,4,"宠物健康状况检测中...",12,240);
				//传感器硬件尚未到位
			}else LCD_Fill(8,4,200,16,WHITE);
			
			if(AT24CXX_ReadOneByte(150)==1)
			{
				adcx=Get_Adc_Average(ADC_Channel_1,10);
				//LCD_ShowxNum(156,130,adcx,4,16,0);//显示ADC的值
				temp=(float)adcx*(3.3/4096);
				adcx=temp;
				LCD_ShowxNum(163,150,adcx,1,16,0);//显示电压值
				temp-=adcx;
				temp*=1000;
				LCD_ShowxNum(172,150,temp,3,16,0X80);
				if(temp<700)p++;
				if(p>=1)
				{
					while(1);
					p=0;
				}//发送紧急短信
			}
			
			
			key=KEY_Scan(0);
			if(key==KEY0_PRES)	//KEY0长按,则执行校准程序
			{
				LCD_Clear(WHITE);//清屏
				TP_Adjust();  	//屏幕校准  
			}
			
			
		}
		
		//柜选扫描
		tp_dev.scan(0);
		if(tp_dev.sta & TP_PRES_DOWN)			
		{//触摸屏检测
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
				////////第二行按键
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
				////////第三行按键
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
				////////第四行按键
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
				
				//消噪调试↓
				delay_ms(250);
				if(BEEP==1)	
				{	
					LCD_Clear(WHITE);
					c=0;//空柜被选中，进入号码输入状态
				}		
				
			}
			BEEP=0;
		}else delay_ms(10);	//没有按键按下的时候
//	while(1);
	}
	
	
	
	
	
	{//号码输入界面
	POINT_COLOR=RED;
	Show_Str_Mid(0,23,"基于单片机的宠物寄存柜设计",16,240);
	//显示时间
	POINT_COLOR=RED;//设置字体为蓝色
	LCD_ShowString(41,83,200,16,16,"    -  -  ");
	LCD_ShowString(133,83,200,16,16,"  :  :  ");
	LCD_ShowNum(41,83,calendar.w_year,4,16);									  
	LCD_ShowNum(81,83,calendar.w_month,2,16);
	LCD_ShowNum(105,83,calendar.w_date,2,16);
	LCD_ShowNum(133,83,calendar.hour,2,16);									  
	LCD_ShowNum(157,83,calendar.min,2,16);									  
	LCD_ShowNum(181,83,calendar.sec,2,16);
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,107,"触击屏幕，逐位输入",16,240);
	Show_Str_Mid(0,47,"请输入手机号",24,240);
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
	Show_Str(185,182,50,24,"确定",24,0);
	Show_Str(185,232,50,24,"回撤",24,0);
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
	{//号码输入状态（次页）
		
		POINT_COLOR=RED;							    
		if(t!=calendar.sec)					   //更新时间	
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
				Show_Str_Mid(8,4,"宠物健康状况检测中...",12,240);
			}else LCD_Fill(8,4,200,16,WHITE);
		}
		POINT_COLOR=RED;
		tp_dev.scan(0);
		if(tp_dev.sta & TP_PRES_DOWN)			//触摸屏被按下
		{
		 	if(tp_dev.x[0]<lcddev.width && tp_dev.y[0]<lcddev.height)
			{				
				if(Phone_Number>0x63 && Phone_Number<0x3e8 && HPhone_Number==0)
				{//判断是否该提出前半部分
					HPhone_Number=Phone_Number;
					Phone_Number=0;
					LCD_Fill(173,130,183,150,WHITE);
					LCD_ShowNum(50,136,HPhone_Number,3,24);//添加标志位
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
					//while(c)if(tp_dev.x[0]>lcddev.width || tp_dev.y[0]>lcddev.height)c=0;//失败的松手检测法
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
//				{//确定键//安到下一循环
//					BEEP=1;
//					LCD_ShowNum(88,136,Phone_Number,8,24);
//				}
				////////第二行按键
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
				{//删除					
					if(Phone_Number==0 && HPhone_Number==0)
					{
						BEEP=1;a=1;c=1;
						goto choose;//随后delay_ms(200);BEEP=0;
					}
pnum://回到输入密码状态
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
				////////第三行按键
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
				//BEEP=0;//消噪调试
				if(Phone_Number>0x98967F)//电话号输满，终止当前输入循环，准备发送短信
				{
					a=0;b=1;goto bp;
				}
			}
			delay_ms(200);
			BEEP=0;
		}else delay_ms(10);	//没有按键按下的时候
		
//		c=1;
//		p++;
//		if(p%20==0)LED0=!LED0;
		
	}
	
	
	
	
pwp:
	{//密码输入界面
	delay_ms(100);
	BEEP=0;
	LCD_Clear(WHITE);
	POINT_COLOR=RED;
	Show_Str_Mid(0,23,"基于单片机的宠物寄存柜设计",16,240);
	LCD_ShowString(41,83,200,16,16,"    -  -  ");	//显示时间
	LCD_ShowString(133,83,200,16,16,"  :  :  ");
	LCD_ShowNum(41,83,calendar.w_year,4,16);									  
	LCD_ShowNum(81,83,calendar.w_month,2,16);
	LCD_ShowNum(105,83,calendar.w_date,2,16);
	LCD_ShowNum(133,83,calendar.hour,2,16);									  
	LCD_ShowNum(157,83,calendar.min,2,16);									  
	LCD_ShowNum(181,83,calendar.sec,2,16);
	POINT_COLOR=MAGENTA;	
	Show_Str_Mid(0,47,"请输入密码",24,240);
	Show_Str_Mid(0,107,"触击屏幕，逐位输入",16,240);
	POINT_COLOR=BROWN;
	Show_Str(26,183,40,24,"1",24,0);			//键盘布局
	Show_Str(86,183,40,24,"2",24,0);
	Show_Str(145,183,40,24,"3",24,0);
	Show_Str(26,233,40,24,"4",24,0);
	Show_Str(86,233,40,24,"5",24,0);
	Show_Str(145,233,40,24,"6",24,0);
	Show_Str(26,282,40,24,"7",24,0);
	Show_Str(86,282,40,24,"8",24,0);
	Show_Str(145,282,40,24,"9",24,0);
	Show_Str(185,182,50,24,"确定",24,0);
	Show_Str(185,232,50,24,"回撤",24,0);
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
	LCD_ShowNum(209,0,AT24CXX_ReadOneByte(BoxN*10+4),2,12);//调试时告知密码
	LCD_ShowNum(221,0,AT24CXX_ReadOneByte(BoxN*10+5),2,12);

	}
	while(e)
	{//密码输入状态（次页）
		POINT_COLOR=RED;							    
		if(t!=calendar.sec)					   //更新时间	
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
				Show_Str_Mid(8,4,"宠物健康状况检测中...",12,240);
			}else LCD_Fill(8,4,200,16,WHITE);
		}
		
		POINT_COLOR=RED;
		tp_dev.scan(0);
		if(tp_dev.sta & TP_PRES_DOWN)			//触摸屏被按下
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
				////////第二行按键
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
				{//删除		
					BEEP=1;			
					if(Password==0)
					{
						a=1;c=1;
						goto choose;//随后delay_ms(200);BEEP=0;
					}
					else
					{
						Password/=10;
					}
					if(Password==0)LCD_Fill(173,130,183,160,WHITE);
					else LCD_ShowNum(88,136,Password,8,24);
				}
				////////第三行按键
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
				
				//BEEP=0;//消噪调试
				
				if(Password == AT24CXX_ReadOneByte(BoxN*10+4)*100+AT24CXX_ReadOneByte(BoxN*10+5))//密码正确，终止当前输入循环，
				{
					Password=0;
					//消噪调试
					BEEP=1;
					//显示发送界面					
					LCD_Clear(WHITE);
					t=calendar.sec;			//计算使用时间并计费显示
					dis_sec=calendar.sec-AT24CXX_ReadOneByte(BoxN*10+3);
					dis_min=calendar.min-AT24CXX_ReadOneByte(BoxN*10+2);					
					dis_hour=calendar.hour-AT24CXX_ReadOneByte(BoxN*10+1);
					POINT_COLOR=BLUE;					
					Show_Str_Mid(0,87,"本次共使用",24,240);
					Show_Str_Mid(0,163,"本次消费",24,240);
					POINT_COLOR=RED;
					LCD_ShowNum(24,120,dis_hour,2,24);
					LCD_ShowNum(96,120,dis_min,2,24);
					LCD_ShowNum(170,120,dis_sec,2,24);
					Show_Str_Mid(46,120,"小时",24,48);
					Show_Str_Mid(121,120,"分钟",24,48);
					Show_Str_Mid(193,120,"秒",24,24);
					cost=(dis_sec+60*dis_min+3600*dis_hour)/5;
					LCD_ShowNum(80,196,cost,3,24);
					Show_Str_Mid(127,196,"元",24,24);
					//打开门
					AT24CXX_WriteOneByte(BoxN*10,0);//释放该柜
					AT24CXX_WriteOneByte(BoxN*10+1,00);//释放时间标签
					AT24CXX_WriteOneByte(BoxN*10+2,00);
					AT24CXX_WriteOneByte(BoxN*10+3,00);
					AT24CXX_WriteOneByte(BoxN*10+4,00);//释放随机密码
					AT24CXX_WriteOneByte(BoxN*10+5,00);
//					AT24CXX_WriteOneByte(160+BoxN,00);//释放号段
//					AT24CXX_WriteOneByte(BoxN*10+6,00);//释放电话号				
//					AT24CXX_WriteOneByte(BoxN*10+7,00);//释放指纹 
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
		}else delay_ms(10);	//没有按键按下的时候
		
	}
	
	
	
	
	
	while(b)
	{//短信发送状态（暂页）
bp:
		POINT_COLOR=RED;	 //更新时间，等待触击操作			    
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
		if(tp_dev.sta & TP_PRES_DOWN)			//触摸屏被按下
		{
		 	if(tp_dev.x[0]<lcddev.width && tp_dev.y[0]<lcddev.height)
			{				
				if(tp_dev.x[0]>180&&tp_dev.x[0]<240 && tp_dev.y[0]>170&&tp_dev.y[0]<220)
				{//确定按钮
					BEEP=1;
					//BEEP=0;//消噪调试
					//显示发送界面					
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
					
					//生成随机密码，并存入
					AT24CXX_WriteOneByte(BoxN*10+4,rand() % 90 + 10);
					AT24CXX_WriteOneByte(BoxN*10+5,rand() % 90 + 10);
					LCD_ShowNum(209,0,AT24CXX_ReadOneByte(BoxN*10+4),2,12);//调试时提示密码
					LCD_ShowNum(221,0,AT24CXX_ReadOneByte(BoxN*10+5),2,12);	
					
					//发送取回密码短信，硬件未到位			
					
					POINT_COLOR=BLUE;
					Show_Str_Mid(0,147,"取回密码短信已发送",24,240);
					
					AT24CXX_WriteOneByte(BoxN*10+0,1);//当前柜已有宠物 标志位存入EEPROM
					AT24CXX_WriteOneByte(BoxN*10+3,calendar.sec);//记住当前时间
					AT24CXX_WriteOneByte(BoxN*10+2,calendar.min);
					AT24CXX_WriteOneByte(BoxN*10+1,calendar.hour);
//					AT24CXX_WriteOneByte(,);
//					AT24CXX_WriteOneByte(,);
//					AT24CXX_WriteOneByte(,);
//					AT24CXX_WriteOneByte(,);
//					AT24CXX_WriteOneByte(,);
					
					HPhone_Number=0;//初始化变量，待下次用
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
				{//删除按钮,b=0；继续查询触击号码位置
					a=1;c=1;b=1;
					goto pnum;
				}
				delay_ms(200);
				BEEP=0;
			}
		}else delay_ms(10);	//没有按键按下的时候
	
	
	
	
	
	
	
	
	
	}
	
	
	
	
}








//	u32 fontcnt;		  
//	u8 i,j;
//	u8 fontx[2];//gbk码
//	while(1)
//	{
//		fontcnt=0;
//		for(i=0x81;i<0xff;i++)
//		{		
//			fontx[0]=i;
//			LCD_ShowNum(118,150,i,3,16);		//显示内码高字节    
//			for(j=0x40;j<0xfe;j++)
//			{
//				if(j==0x7f)continue;
//				fontcnt++;
//				LCD_ShowNum(118,170,j,3,16);	//显示内码低字节	 
//				LCD_ShowNum(118,190,fontcnt,5,16);//汉字计数显示	 
//			 	fontx[1]=j;
//				Show_Font(30+132,220,fontx,24,0);	  
//				Show_Font(30+144,244,fontx,16,0);	  		 		 
//				Show_Font(30+108,260,fontx,12,0);	  		 		 
//				t=200;
//				while(t--)//延时,同时扫描按键；更新字库
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

