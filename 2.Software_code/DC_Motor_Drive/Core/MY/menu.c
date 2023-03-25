#include "menu.h"

extern unsigned char BMP0[];
extern uint8_t Speed;

//����һ�����������ҳ�������ת
key_table table[]=
{
	//��0��
	{0,0,0,1,1,(*fun_0)},
	
    //��1��
	{1,4,2,0,5,(*fun_a1)},
	{2,1,3,0,8,(*fun_b1)},
	{3,2,4,0,10,(*fun_c1)},		
	{4,3,1,0,11,(*fun_d1)},
	
    //�˵�1��2��
	{5,6,6,1,0,(*fun_a21)},	
    {6,5,5,1,0,(*fun_a22)},	

    //�˵�2�ڶ���
    {7,7,9,2,0,(*fun_b21)},
    {8,7,9,2,0,(*fun_b22)},
    {9,7,9,2,0,(*fun_b23)},

    //�˵�3�ڶ���
    {10,10,10,3,0,(*fun_c21)},	

    //�˵�4�ڶ���
    {11,11,11,4,0,(*fun_d21)},		
			
								
};

/**/
void fun_0()
{
    OLED_DrawBMP(0,0,128,8,BMP0);
    //OLED_ShowStr(16,0,(unsigned char*)"zhouqi      ",8);

}


/*********��1��***********/
void fun_a1()   
{	
    OLED_ShowStr(0,0,">",1);
    OLED_ShowStr(16,0,"[1] Direction",1);
    OLED_ShowStr(16,2,"[2] Speed",1);
    OLED_ShowStr(16,4,"[3] Device Info",1);
    OLED_ShowStr(16,6,"[4] SYS Set",1);																				
}

void fun_b1()   
{	
    OLED_ShowStr(0,2,">",1);
    OLED_ShowStr(16,0,"[1] Direction",1);
    OLED_ShowStr(16,2,"[2] Speed",1);
    OLED_ShowStr(16,4,"[3] Device Info",1);
    OLED_ShowStr(16,6,"[4] SYS Set",1);																						
}

void fun_c1()     
{	
    OLED_ShowStr(0,4,">",1);
    OLED_ShowStr(16,0,"[1] Direction",1);
    OLED_ShowStr(16,2,"[2] Speed",1);
    OLED_ShowStr(16,4,"[3] Device Info",1);
    OLED_ShowStr(16,6,"[4] SYS Set",1);																					
}

void fun_d1()     
{	
    OLED_ShowStr(0,6,">",1);
    OLED_ShowStr(16,0,"[1] Direction",1);
    OLED_ShowStr(16,2,"[2] Speed",1);
    OLED_ShowStr(16,4,"[3] Device Info",1);
    OLED_ShowStr(16,6,"[4] SYS Set",1);																							
}

/*********��2��***********/
void fun_a21()     
{	
    OLED_ShowStr(0,2,">",1);
    OLED_ShowStr(16,0,"   Direction",1);
    OLED_ShowStr(16,2,"[1] Forward",1);
    OLED_ShowStr(16,4,"[2] Opposite ",1);
    //OLED_ShowStr(16,6,"[4] Back",1);

}

void fun_a22()     
{	
    OLED_ShowStr(0,4,">",1);
    OLED_ShowStr(16,0,"   Direction",1);
    OLED_ShowStr(16,2,"[1] Forward",1);
    OLED_ShowStr(16,4,"[2] Opposite ",1);
    //OLED_ShowStr(16,6,"[4] Back",1);

}


void fun_b21()     
{	
    if(Speed<=0)
       Speed = 100; 
    else
        Speed--;
    OLED_ShowStr(16,0,"   Speed",2);
    OLED_ShowNum(60,4,Speed,3,16);
}
void fun_b22()     
{	
    //OLED_ShowStr(0,4,">",1);
    OLED_ShowStr(16,0,"   Speed",2);
    //OLED_ShowStr(16,2,"[2] Forward",1);
    //OLED_ShowStr(16,4,"     50 ",1);
    OLED_ShowNum(60,4,Speed,3,16);
   // OLED_ShowStr(16,6,"[4] Back",1);

}

void fun_b23()     
{	
    if(Speed>=100)
       Speed = 0; 
    else
        Speed++;
    OLED_ShowStr(16,0,"   Speed",2);
    OLED_ShowNum(60,4,Speed,3,16);
}

void fun_c21()     
{	
    //OLED_ShowStr(0,4,">",1);
    OLED_ShowStr(16,0,"   Device Info",1);
    OLED_ShowStr(16,2,"Author:ZhouQi",1);
    OLED_ShowStr(16,4,"DATA:2023/3/24",1);
    OLED_ShowStr(16,6,"version:A01.07",1);

}

void fun_d21()     
{	
    //OLED_ShowStr(0,4,">",1);
    OLED_ShowStr(16,0,"   SYS Set",1);
    //OLED_ShowStr(16,2,"",1);
    OLED_ShowStr(16,4,"Storage:YES",1);
    //OLED_ShowStr(16,6,"version:A01.07",1);

}



