#include "stm32f10x.h"
#include "usart.h"
#include "delay.h" 
//#include "intrins.h" 
#include "sys.h" 
#include "string.h"	
//************************************ 

#define  Nack_counter  10 
//************** 端口定义************** 
//LCD 控制线接口 
u8 flag1; 
//sbit  RS=P0^7; 
//sbit  RW=P0^6; 
//sbit  LCDE=P0^5; 
//mlx90614 端口定义 
//sbit  SCL=P1^6;// 时钟线 
//sbit  SDA=P1^7;// 数据线 
//************ 数据定义**************** 
//bdata uchar flag;//可位寻址数据 
//sbit bit_out=flag^7; 
//sbit bit_in=flag^0; 
//uchar DataH,DataL,Pecreg; 
//************ 函数声明***************************************** 
void   start_bit();                 //MLX90614 发起始位子程序 
void   stop_bit();                 //MLX90614发结束位子程序 
u8  rx_byte(void);              //MLX90614 接收字节子程序 
void   send_bit(void);             //MLX90614发送位子程序 
void   tx_byte(uchar dat_byte);     //MLX90614 接收字节子程序 
void   receive_bit(void);           //MLX90614接收位子程序 
//void   delay(uint N);              //延时程序 
uint   memread(void);             // 读温度数据 
void   init1602(void);        //LCD 初始化子程序 
void   chk_busy_flg(void);         //LCD 判断忙子程序 
void   dis_cmd_wrt(u8 cmd);     //LCD 写命令子程序 
void   dis_dat_wrt(u8 dat);       //LCD 写数据子程序 
//void   display(uint Tem);           // 显示子程序 
//*************主函数******************************************* 
//void main() 
{ 
 uint Tem; 
 //函数部分 
 SCL=1;SDA=1;_nop_(); 
 _nop_();_nop_();_nop_(); 
 SCL=0; 
 delay(1000); 
 SCL=1; 
 init1602(); 
 while(1) 
 { 
   Tem=memread(); 
   //display(Tem); 
   //delay(20); 
 } 
} 
//*********输入转换并显示********* 
//void display(uint Tem) 
//{ 
// uint T,a,b; 
// T=Tem*2; 
//  dis_cmd_wrt(0x01);//清屏 
// if(T>=27315) 
// { 
//   T=T-27315; 
//   a=T/100; 
//   b=T-a*100; 
////--------------------------- 
//   if(a>=100) 
//   { 
//    dis_dat_wrt(0x30+a/100); 
//    a=a%100; 
//    dis_dat_wrt(0x30+a/10); 
//    a=a%10; 
//    dis_dat_wrt(0x30+a); 
//   } 
//   else if(a>=10) 
//   { 
//    dis_dat_wrt(0x30+a/10); 
//    a=a%10; 
//    dis_dat_wrt(0x30+a); 
//   } 
//   else 
//   { 
//    dis_dat_wrt(0x30+a); 
//   } 
//   dis_dat_wrt(0x2e);// 显示点 
//   //--------------------------- 
//  if(b>=10) 
//  { 
//    dis_dat_wrt(0x30+b/10); 
////    b=b%10; 
////    dis_dat_wrt(0x30+b); 
//  } 
//  else 
//  { 
//    dis_dat_wrt(0x30); 
////    dis_dat_wrt(0x30+b); 
//  } 
// } 
////==========
// else 
// { 
//  T=27315-T; 
//  a=T/100; 
//    b=T-a*100; 
//  dis_dat_wrt(0x2d); 
////-------------------------- 
//  if(a>=10) 
//  { 
//    dis_dat_wrt(0x30+a/10); 
//    a=a%10; 
//    dis_dat_wrt(0x30+a); 
//  } 
//  else 
//  { 
//    dis_dat_wrt(0x30+a); 
//  } 
//  dis_dat_wrt(0x2e);//显示点 
////-------------------------- 
//  if(b>=10) 
//  { 
//    dis_dat_wrt(0x30+b/10); 
//    b=b%10; 
//    dis_dat_wrt(0x30+b); 
//  } 
//  else 
//  { 
//    dis_dat_wrt(0x30); 
//    dis_dat_wrt(0x30+b); 
//  } 
// } 
//}

//************************************ 
void   start_bit(void) 
{ 
   SDA=1; 
   _nop_();_nop_();_nop_();_nop_();_nop_(); 
   SCL=1; 
   _nop_();_nop_();_nop_();_nop_();_nop_(); 
   SDA=0; 
   _nop_();_nop_();_nop_();_nop_();_nop_(); 
   SCL=0; 
   _nop_();_nop_();_nop_();_nop_();_nop_(); 
 
} 
//------------------------------ 
void   stop_bit(void) 
{ 

   SCL=0; 
   _nop_();_nop_();_nop_();_nop_();_nop_(); 
   SDA=0; 
   _nop_();_nop_();_nop_();_nop_();_nop_(); 
   SCL=1; 
   _nop_();_nop_();_nop_();_nop_();_nop_(); 
   SDA=1; 
} 
//--------- 发送一个字节--------- 
void  tx_byte(uchar dat_byte) 
{ 
   char i,n,dat; 
   n=Nack_counter; 
TX_again: 
   dat=dat_byte; 
   for(i=0;i<8;i++) 
   { 
     if(dat&0x80) 
      bit_out=1; 
     else 
      bit_out=0; 
     send_bit(); 
     dat=dat<<1; 
   } 
   
      receive_bit(); 
   if(bit_in==1) 
   { 
    stop_bit(); 
    if(n!=0) 
    {n--;goto Repeat;} 
    else 
     goto exit; 
   } 
   else 
    goto exit; 
Repeat: 
    start_bit(); 
    goto TX_again; 
exit: ; 
} 
//-----------发送一个位--------- 
void  send_bit(void) 
{ 
  if(bit_out==0) 
  
       SDA=0; 
  else 
     SDA=1; 
  _nop_(); 
  SCL=1; 
  _nop_();_nop_();_nop_();_nop_(); 
  _nop_();_nop_();_nop_();_nop_(); 
  SCL=0; 
  _nop_();_nop_();_nop_();_nop_(); 
  _nop_();_nop_();_nop_();_nop_(); 
} 
//---------- 接收一个字节-------- 
uchar rx_byte(void) 
{ 
  uchar i,dat; 
  dat=0; 
  for(i=0;i<8;i++) 
  { 
    dat=dat<<1; 
    receive_bit(); 
    if(bit_in==1) 
     dat=dat+1; 
  } 
  send_bit(); 
  return dat; 
} 

//---------- 接收一个位---------- 
void receive_bit(void) 
{ 
  SDA=1;bit_in=1; 
  SCL=1; 
  _nop_();_nop_();_nop_();_nop_(); 
  _nop_();_nop_();_nop_();_nop_(); 
  bit_in=SDA; 
  _nop_(); 
  SCL=0; 
  _nop_();_nop_();_nop_();_nop_(); 
  _nop_();_nop_();_nop_();_nop_(); 
} 
//------------ 延时-------------- 
//void   delay(uint N) 
//{ 
//  uint i; 
//  for(i=0;i<N;i++) 
//  
//     _nop_(); 
//} 
//------------------------------ 
uint memread(void) 
{ 
  start_bit(); 
  tx_byte(0xB4);  //Send SlaveAddress ==============================
  //tx_byte(0x00); 
  tx_byte(0x07);  //Send Command 
  //------------ 
  start_bit(); 
  tx_byte(0x01); 
  bit_out=0; 
  DataL=rx_byte(); 
  bit_out=0; 
  DataH=rx_byte(); 
  bit_out=1; 
  Pecreg=rx_byte(); 
  stop_bit(); 
  return(DataH*256+DataL); 
}
//******************LCD 显示子函数*********************** 
//void init1602(void)        // 初始化LCD 
//{ 
//   dis_cmd_wrt(0x01); 
//   dis_cmd_wrt(0x0c); 
//   dis_cmd_wrt(0x06); 
//   dis_cmd_wrt(0x38); 
//   
//   } 
// 
void chk_busy_flg(void) //LCD 忙标志判断 
{ 
   flag1=0x80; 
  while(flag1&0x80) 
 { 
   P2=0xff; 
   RS=0; 
   RW=1; 
   LCDE=1; 
   flag1=P2; 
   LCDE=0; 
 } 
} 
 
void dis_cmd_wrt(uchar cmd)    // 写命令子函数 
{ 
   chk_busy_flg(); 
   P2=cmd; 
   RS=0; 
   RW=0; 
   LCDE=1; 
   LCDE=0; 
} 
 
void dis_dat_wrt(uchar dat) // 写数据子函数 
{ 
  chk_busy_flg(); 
  if(flag1==16) 
  { 
   P2=0XC0; 
   RS=0; 
   RW=0; 
   LCDE=1; 
   LCDE=0; 
  } 
   P2=dat; 
   RS=1; 
   RW=0; 
   LCDE=1; 
   LCDE=0; 
} 
 
