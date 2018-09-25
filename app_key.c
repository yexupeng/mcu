#include "app_key.h"
#include "stdio.h"
#include "stdlib.h"

//�󶨰�����Ӧ�ص�����
void KEY_EventCallBack_Attach(KEY_HandleTypeDef * hkey,KEY_EventTypeDef event,keyCallBack callback)
{
	hkey->CallBack[event] =  callback;
}
//��ȡ�������¼�
KEY_EventTypeDef KEY_GetEventType(KEY_HandleTypeDef * hkey)
{
	return (hkey -> Event);
}
//��ȡ������״̬
KEY_StateTypeDef KEY_GetStateType(KEY_HandleTypeDef * hkey)
{
	return (hkey -> State);
}
//����������
static KEY_StatusTypeDef  KEY_Handler(KEY_HandleTypeDef * const hkey)
{
	  KEY_StateTypeDef state ;
	 if(hkey == NULL)
	 {
		 //���log�ж�ָ���Ƿ�Ϊ�գ��������ⶨλ��
		 
		 return KEY_FAIL;
	 }
	 state = hkey->ReadKey();
//	 if(state != hkey->State)
//	 {
//		//���ȥ���˲�,����ʱ��ɨ��ʱ�����
//		if(++(hkey->DebounceCnt) >= DebounceCnt_MAXVALUE)
//		{
			hkey->State =state;
//			hkey->DebounceCnt=0;
//		}
//	 }
//	 else
//	 {
//		 hkey->DebounceCnt=0;
//	 }
	 //״̬����״̬�л���������������������������������������������
	 switch(hkey ->Status)
	 {
		 case 0:
			 if(hkey->State == KEY_STATE_PRESSED)
			 {
				hkey->Ticks =0;
				hkey->Status =1;
			 }
			 else
			 {
				 if(hkey->repeat == 1)
				 {	
					 //���ε������鳬�����ü������Ϊ���ε���
					 if(++(hkey->ClikCnt) > SINGLEORDOUBLE_CNTCOUNT)
					 {    
						 hkey->ClikCnt=0;
						 hkey->repeat=0;
						 hkey->Event= KEY_EVENT_SINGLE_CLIK;
						 KEY_CallBack(hkey,KEY_EVENT_SINGLE_CLIK);//�����¼��ص���������
					 }
				 }
			 }
			break;
		 case  1:
			 if(hkey->State == KEY_STATE_PRESSED)
			 {
				++hkey->Ticks;
				  //���ڰ�������ʱ������
				if(hkey->Ticks > LONG_PRESSED_MAXVALUE)//��������Ϊ�˿������ܣ���Ҫ��ⰴ��ʱ���жϳ��������������ֺ��жϰ���ʱ��
				{
					hkey->Ticks = 0;
					hkey->Status = 2;
					hkey->Event=KEY_EVENT_LONG_PRESS;
					KEY_CallBack(hkey,KEY_EVENT_LONG_PRESS);//�����¼��ص������ص�
				}
			 }
			 else
			 {
					hkey->Status=0;
				 //���ڰ�������ʱ�����ƣ�С�ڰ�������ʱ������
				 if((hkey->Ticks) >= SHORT_PRESSED_MAXVALUE && hkey->Ticks < LONG_PRESSED_MAXVALUE)
				 {
					 hkey->ClikCnt=0;
					 if(++(hkey->repeat) >= 2)
					 {
							hkey->repeat =0;
							hkey->Event= KEY_EVENT_DOUBLE_CLIK; 
							KEY_CallBack(hkey,KEY_EVENT_SINGLE_CLIK);//˫���¼��ص������ص�			 
					 }						 
				 }
//				 else if(hkey->Ticks > LONG_PRESSED_MAXVALUE)
//				 {
//					hkey->Event=KEY_EVENT_LONG_PRESS;
//					KEY_CallBack(hkey,KEY_EVENT_LONG_PRESS);//�����¼��ص������ص�
//				 }
					hkey->Ticks=0;
			 }
			 break;	
		 case 2:
			 if(hkey->State != KEY_STATE_PRESSED)//�����ͷ�,��������Ϊ�˿������ܣ���Ҫ��ⰴ��ʱ���жϳ��������������ֺ��жϰ���ʱ��
			 {
				 hkey->Status =0;
			 }
			 break;
	}
	 return KEY_OK;
}

//����ɨ�裬�����Ѱ,����ֻ���ṩ��ʼ���ӿڼ���
KEY_StatusTypeDef KEY_Scanf(KEY_HandleTypeDef * head)
{
	KEY_HandleTypeDef*  ptr;
	if(head == NULL)
	{
		return KEY_FAIL;
	}
	for(ptr=head;ptr != NULL;ptr=ptr->next)
		KEY_Handler(ptr);
	return KEY_OK;
}
//�����������Ƿ���ڴ���ӵ�����
KEY_HandleTypeDef * KEY_LookUp(KEY_HandleTypeDef**root,KEY_NUMBER keynumber)
{
	KEY_HandleTypeDef *p;
	for(p=*root;p != NULL;p=p->next)
	{
		if(p->KeyNuber == keynumber)
		{
			return p;
		}
	}
	return NULL;
}

//�ͷ�������ڴ�
KEY_StatusTypeDef KEY_Free(KEY_HandleTypeDef *head)
{
	KEY_HandleTypeDef *ptr,*qptr;	
	if(head == NULL)
	{
		return KEY_OK;
	}
	for(ptr=head; ptr!= NULL;ptr=qptr)
	{
		qptr=ptr->next;
		free(ptr);
	}
	return KEY_OK;
}


KEY_StatusTypeDef  KEY_InstallList(KEY_HandleTypeDef **root,KEY_NUMBER keynumber,
  Read readkey,KEY_EventTypeDef event,keyCallBack callback)
{
	KEY_HandleTypeDef *p;

	if((p =KEY_LookUp(root,keynumber)) == NULL)
	{
		p=(KEY_HandleTypeDef*)malloc(sizeof(*p));
		if(p == NULL)
		{
			return KEY_FAIL;
		}
		p->KeyNuber=keynumber;
		p->ReadKey=readkey;
		p->next=NULL;
		KEY_EventCallBack_Attach(p,event,callback);
		if(*root == NULL)
		{
			*root=p;
		}
		else
		{
			KEY_HandleTypeDef *np=*root;
			while(np->next != NULL)
			{
				np=np->next;
			}
			np->next=p;
		}
	}
	else
	{
		KEY_EventCallBack_Attach(p,event,callback);
		return KEY_OK;
	}
}
















