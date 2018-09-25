#include "app_key_user.h"
#include "app_timer.h"
#include "string.h"
#include "key.h"
#include "stdlib.h"

//按键轮询定时器
SOFT_TIMER_ST     *input_timer;

KEY_HandleTypeDef *head=NULL;


//空函数防止访问野指针造成hardfault
static void KEY_NULL(void)
{
	return ;
}

//看后期有没有更好的分配方式。。。。。。
void KEY_Init()
{
	//先释放一下内存，其实，鸡肋。应该在每次关机(如果掉电的话，不释放也可以。)的时候，释放内存、、
	 KEY_Free(head);
	 KEY_InstallList(&head,KEY_1,Read_KeyPowerDevice,KEY_EVENT_LONG_PRESS,KEY_POWER_LONG_PRESS);
	 KEY_InstallList(&head,KEY_2,Read_Key_A,KEY_EVENT_SINGLE_CLIK,KEY_A_SingleClik);
	 KEY_InstallList(&head,KEY_3,Read_Key_B,KEY_EVENT_SINGLE_CLIK,KEY_B_SingleClik);
	 KEY_InstallList(&head,KEY_4,Read_Key_C,KEY_EVENT_SINGLE_CLIK,KEY_C_SingleClik);
	 KEY_InstallList(&head,KEY_5,Read_Key_D,KEY_EVENT_SINGLE_CLIK,KEY_D_SingleClik);
	 KEY_InstallList(&head,KEY_6,Read_Key_Cancel,KEY_EVENT_SINGLE_CLIK,KEY_CANCEL_SingleClik);	
	 KEY_InstallList(&head,KEY_7,Read_Key_Submit,KEY_EVENT_SINGLE_CLIK,KEY_Submit_SingleClik);	
}
//释放为按键分配的内存
void KEY_DeInit(void)
{
	KEY_Free(head);
}
//定时器初始化
void KEY_InitTimer(void)
{
    input_timer=register_soft_timer(input_timer);
    start(input_timer,5); //5毫秒	
}
//按键轮询线程
void KEY_Detect_thread(void)
{
    if(IS_Elapsed(input_timer))
    {
		KEY_Scanf(head) ;           
        start(input_timer,5); //5毫秒 
    }	
}

