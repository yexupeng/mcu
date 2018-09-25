#ifndef APP_KEY_H
#define APP_KEY_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "stdint.h"


typedef enum{
	KEY_1 = 0,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7
}KEY_NUMBER;



//按键回调函数，事件驱动
//支持单击、双击、长按。
#define KEY_CallBack(handle,event)  do{ \
									if(handle->CallBack[event] != NULL) \
							       {                                \
									   handle->CallBack[event]();\
								   } 										   \
							  }while(0);

								
#define DebounceCnt_MAXVALUE   5          //软件滤波计数
#define LONG_PRESSED_MAXVALUE   300        //长按计数，原先100太短
#define SHORT_PRESSED_MAXVALUE   5          //短按计数
#define SINGLEORDOUBLE_CNTCOUNT  50         //单击和双击间隔计数
								

//触摸函数状态
typedef enum {
  KEY_OK   = 0,
  KEY_FAIL,
}KEY_StatusTypeDef;

								
//按键事件类型定义
typedef enum{
	/*按键单击*/
	KEY_EVENT_SINGLE_CLIK=0,
	/*按键双击*/
	KEY_EVENT_DOUBLE_CLIK,
	/*按键长按*/
	KEY_EVENT_LONG_PRESS,
	/*按键事件个数*/
	KEY_EVENT_NUMBER,
	/*无按键事件*/
	KEY_EVENT_NONE_PRESS
	
}KEY_EventTypeDef;


//按键状态类型定义
typedef enum{
		/*按键没有按下*/
	KEY_STATE_NONE_PRESSED =0,
		/*按键被按下*/
	KEY_STATE_PRESSED 	
}KEY_StateTypeDef;


//定义按键回调函数指针
typedef void (*keyCallBack)(void);
typedef	 KEY_StateTypeDef   (*Read)(void);

typedef struct KEY_HandleTypeDef{
		uint8_t                      KeyNuber;
    /*按键按下事件计数*/
	 uint16_t                    Ticks;
	 uint8_t                     ClikCnt;
	/*按键软件消除抖动*/
	 uint8_t 					 DebounceCnt;
	//状态机切换标志
	 uint8_t                     Status;
	/*按键事件*/
	 KEY_EventTypeDef            Event;
	/*按键状态*/
	KEY_StateTypeDef             State;
	/*连续按键计数*/
	uint8_t                      repeat;
	/*读取按键状态函数*/
	Read                          ReadKey;
	/*按键不同事件对应不同回调函数*/
	 keyCallBack                 CallBack[KEY_EVENT_NUMBER];
	 struct KEY_HandleTypeDef              *next;

}KEY_HandleTypeDef;


//绑定按键对应回调函数
void KEY_EventCallBack_Attach(KEY_HandleTypeDef * hkey,KEY_EventTypeDef event,keyCallBack callback);
//获取按键的事件
KEY_EventTypeDef KEY_GetEventType(KEY_HandleTypeDef * hkey);
//获取按键的状态
KEY_StateTypeDef KEY_GetStateType(KEY_HandleTypeDef * hkey);
//按键扫描函数
KEY_StatusTypeDef KEY_Scanf(KEY_HandleTypeDef * const head);
//查找链表中是否存在待添加的链表
KEY_HandleTypeDef * KEY_LookUp(KEY_HandleTypeDef**root,KEY_NUMBER keynumber);
KEY_StatusTypeDef KEY_Free(KEY_HandleTypeDef *head);

KEY_StatusTypeDef  KEY_InstallList(KEY_HandleTypeDef **root,KEY_NUMBER keynumber,
  Read readkey,KEY_EventTypeDef event,keyCallBack callback);
#ifdef __cplusplus
}
#endif

#endif
