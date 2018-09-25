#include "app_key.h"
#include "stdio.h"
#include "stdlib.h"

//绑定按键对应回调函数
void KEY_EventCallBack_Attach(KEY_HandleTypeDef * hkey,KEY_EventTypeDef event,keyCallBack callback)
{
	hkey->CallBack[event] =  callback;
}
//获取按键的事件
KEY_EventTypeDef KEY_GetEventType(KEY_HandleTypeDef * hkey)
{
	return (hkey -> Event);
}
//获取按键的状态
KEY_StateTypeDef KEY_GetStateType(KEY_HandleTypeDef * hkey)
{
	return (hkey -> State);
}
//按键处理函数
static KEY_StatusTypeDef  KEY_Handler(KEY_HandleTypeDef * const hkey)
{
	  KEY_StateTypeDef state ;
	 if(hkey == NULL)
	 {
		 //添加log判断指针是否为空，方便问题定位。
		 
		 return KEY_FAIL;
	 }
	 state = hkey->ReadKey();
//	 if(state != hkey->State)
//	 {
//		//软件去抖滤波,看定时器扫描时间而定
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
	 //状态机，状态切换。。。。。。。。。。。。。。。。。。。。。。
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
					 //两次单击事情超过设置间隔，认为两次单击
					 if(++(hkey->ClikCnt) > SINGLEORDOUBLE_CNTCOUNT)
					 {    
						 hkey->ClikCnt=0;
						 hkey->repeat=0;
						 hkey->Event= KEY_EVENT_SINGLE_CLIK;
						 KEY_CallBack(hkey,KEY_EVENT_SINGLE_CLIK);//单击事件回调函数调用
					 }
				 }
			 }
			break;
		 case  1:
			 if(hkey->State == KEY_STATE_PRESSED)
			 {
				++hkey->Ticks;
				  //大于按键长按时间限制
				if(hkey->Ticks > LONG_PRESSED_MAXVALUE)//。。。。为了开机功能，需要检测按下时间判断长按，而不是松手后判断按下时间
				{
					hkey->Ticks = 0;
					hkey->Status = 2;
					hkey->Event=KEY_EVENT_LONG_PRESS;
					KEY_CallBack(hkey,KEY_EVENT_LONG_PRESS);//长按事件回调函数回调
				}
			 }
			 else
			 {
					hkey->Status=0;
				 //大于按键单击时间限制，小于按键长按时间限制
				 if((hkey->Ticks) >= SHORT_PRESSED_MAXVALUE && hkey->Ticks < LONG_PRESSED_MAXVALUE)
				 {
					 hkey->ClikCnt=0;
					 if(++(hkey->repeat) >= 2)
					 {
							hkey->repeat =0;
							hkey->Event= KEY_EVENT_DOUBLE_CLIK; 
							KEY_CallBack(hkey,KEY_EVENT_SINGLE_CLIK);//双击事件回调函数回调			 
					 }						 
				 }
//				 else if(hkey->Ticks > LONG_PRESSED_MAXVALUE)
//				 {
//					hkey->Event=KEY_EVENT_LONG_PRESS;
//					KEY_CallBack(hkey,KEY_EVENT_LONG_PRESS);//长按事件回调函数回调
//				 }
					hkey->Ticks=0;
			 }
			 break;	
		 case 2:
			 if(hkey->State != KEY_STATE_PRESSED)//按键释放,。。。。为了开机功能，需要检测按下时间判断长按，而不是松手后判断按下时间
			 {
				 hkey->Status =0;
			 }
			 break;
	}
	 return KEY_OK;
}

//按键扫描，链表遍寻,后期只需提供初始化接口即可
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
//查找链表中是否存在待添加的链表
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

//释放请求的内存
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
















