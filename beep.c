/**********************
Filename: FingerMusic
Author:		Yukon Chen
Revision: finish the delay between digital display & music, a queue
can be uesd to store the musicode would be played next.
***********************/
#include <STC15F2K60S2.h>
#define uint unsigned int
#define uchar unsigned char
#include <stdlib.h>
#include "musics.c"
#include "varias.c"

sbit beep=P3^4;			  	//������
sbit KEY1 = P3^2;
sbit KEY2 = P3^3;
sbit KEY3 = P1^7;
sbit led_sel=P2^3;			//�������LED���л�����
uchar timeh,timel;		  //���嶨ʱ������װֵ

void gameScreen();
void musiDelayCode();

/**********************
�������ƣ�void delay(unsigned int xms)
������������ʱ
��ڲ�����xms��������Ҫ��ʱ�ĺ���ֵ
���ڲ�������
��ע��

***********************/
void delay(unsigned int xms)
{
	uint i,j;						   
	 for(i=xms;i>0;i--)
	 	for(j=124;j>0;j--);
}
/**********************
FUNCTION: 		void clearAll()
DESCRIPTION:	if game finished, clean all barriars and game screen show.
***********************/
void clearAll()
{
	uint n;
	for(n=0;n<8;n++){
		show_b[k] = 0x00;
		show_f[k] = 0x00;
	}
}
/***********************
FUNCTION: 		void seg7encorder()
DESCRIPTION:	to translate a number into 7-segment code.
************************/
uchar seg7encorder(uint num){
	switch(num){
		case 0: return 0x3f;
		case 1: return 0x06;
		case 2: return 0x5b;
		case 3: return 0x4f;
		case 4: return 0x66;
		case 5: return 0x6d;
		case 6: return 0x7d;
		case 7: return 0x07;
		case 8: return 0x7f;
		case 9: return 0x6f;
		default: return 0xff;
	}
}
/***********************
FUNCTION: 		void showPoint()
DESCRIPTION:	to show calculate every bit of a number.
************************/
void showPoint(){
	uchar numg = seg7encorder(point%10);
	uchar nums = seg7encorder(point/10%10);
	uchar numb = seg7encorder(point/100%10);
	show_vic[5] = numb;
	show_vic[6] = nums;
	show_vic[7] = numg;
	show_lose[5] = numb;
	show_lose[6] = nums;
	show_lose[7] = numg;
}

void changeLevel(){
	level++;										//initial level 1
	if(level == 2){							//level 2
		delaytime = 280;
		mudltime = 1000;
	}else if(level == 3){				//level 3
		delaytime = 130;	
		mudltime = 700;
	}else{											//game win
		clearAll();
		showPoint();
		gameState = 1;
		return;
	}
}

uint countN(uint i){
	uint n = 1;
	switch(level){
		case 1:
			while(jingo[i+n]==jingo[i])n++;
			break;
		case 2:
			while(tongyi[i+n]==tongyi[i])n++;
			break;
		case 3:
			while(nevforg[i+n]==nevforg[i])n++;
			break;
	}
	return n;
}
/**********************
�������ƣ�void playmusic()
������������������
��ڲ�������
���ڲ�������
***********************/
void playmusic()
{
	
	uchar p,tem;   //mΪ����   
	uchar i=6;    
	uchar prex = 127;
	uchar premu = 127;
	
	while(1)   
	{   
		if(gameState > 0)						//game over
		{
			break;
		}
		
		switch(level){
				case 1: p=jingo[i]; break;
				case 2: p=tongyi[i];break;
				case 3: p=nevforg[i];break;
		}
		
		//show_f[3] = seg7encorder(p/100);
		//show_f[4] = seg7encorder(p/10%10);
		//show_f[5] = seg7encorder(p%10);
		if(p==0x00)
		{
			i=6;
			show_b[0] = 0x00;
			delay(8000);
			count = 0;							
			changeLevel();
		}        
		else if(p==0xff)   //��������ֹ��,��ʱ100ms,����ȡ��һ����
		{
			i=i+1;
			delay(delaytime);
			TR0=0;
		}      
		else			   //���������ȡ�����ͽ��� 
		{
			switch(level)
			{
				case 1: tem=quyin(jingo[i-6]); break;  //ȡ����ǰ������quzi�����е�λ��ֵ
				case 2: tem=quyin(tongyi[i-6]);break;
				case 3: tem=quyin(nevforg[i-6]);break;
			}		
			timeh=quzi[tem];			//��������Ӧ�ļ�ʱ����װ��ֵ����timeh��timel
			timel=quzi[tem+1];
			
			if(tem != premu){
				do{
					x = rand()%3;	
				}while(x==prex);
				prex = x;
				
				switch(x){
				case 0: next = 0x01; break;		//show_b[0] is an original resource used to copy musicode to next location.
				case 1: next = 0x40; break;
				case 2: next = 0x08; break;
				}
				n = countN(i-6);
				i += n-1;
				premu = tem;
			}else{
				next = 0x00;
			}
			
			i++;
			TH0=timeh;					//��timeh��timel�����ʱ��
			TL0=timel;
			
			TR0=1;                                              
			delay(mudltime*n); 		//�ȴ��������, ͨ��P3^4�������Ƶ  
			TR0=0;    
		} 
		n = 1;
		prex = 999;
   }
}
/**********************
�������ƣ�void init_sys()
����������ϵͳ��ʼ��������������IO��
***********************/
void init_sys()
{
	P0M0=0xff;
	P0M1=0x00;
	P2M0=0x08;
	P2M1=0x00;
	P3M0=0x10;
	P3M1=0x00;
	P4M0=0x00;
	P4M1=0x00;
	P5M0=0x00;
	P5M1=0x00;
}
void init()						  
{
	TMOD=0x11;
	TH0=0xD8;
	TL0=0xEF;
	EA=1;
	ET0=1;
	TR0=0;
	ET1=1;
	TR1=1;
}

/**********************
void main() main function
***********************/
void main()
{
	init_sys();
	init();
	P0=0x00;
	/*gameState = -1;
	while(gameState == -1)			//waiting
	{
		if(KEY1 == 0){gameState = 0;}
	}*/
	playmusic();
	while(1);
}

/**********************
void tim1() interrupt 1
***********************/
uint bcount = 0;
void tim1() interrupt 1					
{
	TH0=timeh;
	TL0=timel;
	beep=~beep;
}
void tim2() interrupt 3		
{
	TH1=(65536-925)/256;
	TL1=(65536-925)%256;
	gameScreen();
}


/***********************
FUNCTION:void gameScreen()
************************/
void gameScreen(){

		if(gameState == 0)
		{
			if(KEY3 == 0){ show_b[6] &= 0xfe; }		 //�û�����������λ�õ�����
			if(KEY2 == 0){ show_b[6] &= 0xbf; }
			if(KEY1 == 0){ show_b[6] &= 0xf7; } 
			
			if(elidith == 50)
			{
				if(KEY3 == 0){ show_f[6] ^= 0x01; }  //�û���������˸
				if(KEY2 == 0){ show_f[6] ^= 0x40; }
				if(KEY1 == 0){ show_f[6] ^= 0x08; } 
				elidith = 0;
			}
			
			divcontrol = 0;
			show_f[6] |= 0x36;	//�û���ʾ��
		}
		
		P0=0;
		led_sel=0;	
		P0=0;
		if(k<=7){
			P2=weixuan[k];			//ѡ������ܵ�λ��
			P0=show_f[k];				//��ʾ��Ӧ����ֵ
		}
		else{
			P0=0;
			led_sel=1;
			P0 = led;
		}
		k=(k+1)%9;						//ԭ������forѭ���л�P0,ʹ�����Ȳ�������������ÿ���ж�ֻ������ʾ
													//һλ���Ӷ�ʹ����������ᵼ���ж�ռ��̫��ʱ�䣬�������ֲ��ſ���
		count++;
		elidith++;
		
		//LED��ʾ
		
		if(count==delaytime)	
		{
			switch(gameState){
				case 0:	// go game
					if(show_b[7]!=0x00)											
					{
						led = led >> 1;
						if(led == 0x00){
							clearAll();
							showPoint();
							gameState = 2;											
						}
					}else{																	
						if(divpo=10){ point++; divpo=0;}	// get points
						else divpo++;
					}
					
					for(k=7;k>0;k--)	//barriers shift right
					{
						show_b[k] = show_b[k-1];
					}
					
					show_b[0] = next;
					
					for(k=0;k<8;k++)	//show lights shift right
					{
						show_f[k] = show_b[k];
					}
					count=0;
					break;
					
				case 1:	//win game							
					for(k=0;k<8;k++)
					{
						show_f[k] = show_vic[k];
					}
					break;
					
				case 2:	//lose game							
					for(k=0;k<8;k++)
					{
						show_f[k] = show_lose[k];
					}
					break;
			}
		}
}