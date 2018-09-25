#include "app_key_user.h"
#include "app_timer.h"
#include "string.h"
#include "key.h"
#include "stdlib.h"

//������ѯ��ʱ��
SOFT_TIMER_ST     *input_timer;

KEY_HandleTypeDef *head=NULL;


//�պ�����ֹ����Ұָ�����hardfault
static void KEY_NULL(void)
{
	return ;
}

//��������û�и��õķ��䷽ʽ������������
void KEY_Init()
{
	//���ͷ�һ���ڴ棬��ʵ�����ߡ�Ӧ����ÿ�ιػ�(�������Ļ������ͷ�Ҳ���ԡ�)��ʱ���ͷ��ڴ桢��
	 KEY_Free(head);
	 KEY_InstallList(&head,KEY_1,Read_KeyPowerDevice,KEY_EVENT_LONG_PRESS,KEY_POWER_LONG_PRESS);
	 KEY_InstallList(&head,KEY_2,Read_Key_A,KEY_EVENT_SINGLE_CLIK,KEY_A_SingleClik);
	 KEY_InstallList(&head,KEY_3,Read_Key_B,KEY_EVENT_SINGLE_CLIK,KEY_B_SingleClik);
	 KEY_InstallList(&head,KEY_4,Read_Key_C,KEY_EVENT_SINGLE_CLIK,KEY_C_SingleClik);
	 KEY_InstallList(&head,KEY_5,Read_Key_D,KEY_EVENT_SINGLE_CLIK,KEY_D_SingleClik);
	 KEY_InstallList(&head,KEY_6,Read_Key_Cancel,KEY_EVENT_SINGLE_CLIK,KEY_CANCEL_SingleClik);	
	 KEY_InstallList(&head,KEY_7,Read_Key_Submit,KEY_EVENT_SINGLE_CLIK,KEY_Submit_SingleClik);	
}
//�ͷ�Ϊ����������ڴ�
void KEY_DeInit(void)
{
	KEY_Free(head);
}
//��ʱ����ʼ��
void KEY_InitTimer(void)
{
    input_timer=register_soft_timer(input_timer);
    start(input_timer,5); //5����	
}
//������ѯ�߳�
void KEY_Detect_thread(void)
{
    if(IS_Elapsed(input_timer))
    {
		KEY_Scanf(head) ;           
        start(input_timer,5); //5���� 
    }	
}

