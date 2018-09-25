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



//�����ص��������¼�����
//֧�ֵ�����˫����������
#define KEY_CallBack(handle,event)  do{ \
									if(handle->CallBack[event] != NULL) \
							       {                                \
									   handle->CallBack[event]();\
								   } 										   \
							  }while(0);

								
#define DebounceCnt_MAXVALUE   5          //����˲�����
#define LONG_PRESSED_MAXVALUE   300        //����������ԭ��100̫��
#define SHORT_PRESSED_MAXVALUE   5          //�̰�����
#define SINGLEORDOUBLE_CNTCOUNT  50         //������˫���������
								

//��������״̬
typedef enum {
  KEY_OK   = 0,
  KEY_FAIL,
}KEY_StatusTypeDef;

								
//�����¼����Ͷ���
typedef enum{
	/*��������*/
	KEY_EVENT_SINGLE_CLIK=0,
	/*����˫��*/
	KEY_EVENT_DOUBLE_CLIK,
	/*��������*/
	KEY_EVENT_LONG_PRESS,
	/*�����¼�����*/
	KEY_EVENT_NUMBER,
	/*�ް����¼�*/
	KEY_EVENT_NONE_PRESS
	
}KEY_EventTypeDef;


//����״̬���Ͷ���
typedef enum{
		/*����û�а���*/
	KEY_STATE_NONE_PRESSED =0,
		/*����������*/
	KEY_STATE_PRESSED 	
}KEY_StateTypeDef;


//���尴���ص�����ָ��
typedef void (*keyCallBack)(void);
typedef	 KEY_StateTypeDef   (*Read)(void);

typedef struct KEY_HandleTypeDef{
		uint8_t                      KeyNuber;
    /*���������¼�����*/
	 uint16_t                    Ticks;
	 uint8_t                     ClikCnt;
	/*���������������*/
	 uint8_t 					 DebounceCnt;
	//״̬���л���־
	 uint8_t                     Status;
	/*�����¼�*/
	 KEY_EventTypeDef            Event;
	/*����״̬*/
	KEY_StateTypeDef             State;
	/*������������*/
	uint8_t                      repeat;
	/*��ȡ����״̬����*/
	Read                          ReadKey;
	/*������ͬ�¼���Ӧ��ͬ�ص�����*/
	 keyCallBack                 CallBack[KEY_EVENT_NUMBER];
	 struct KEY_HandleTypeDef              *next;

}KEY_HandleTypeDef;


//�󶨰�����Ӧ�ص�����
void KEY_EventCallBack_Attach(KEY_HandleTypeDef * hkey,KEY_EventTypeDef event,keyCallBack callback);
//��ȡ�������¼�
KEY_EventTypeDef KEY_GetEventType(KEY_HandleTypeDef * hkey);
//��ȡ������״̬
KEY_StateTypeDef KEY_GetStateType(KEY_HandleTypeDef * hkey);
//����ɨ�躯��
KEY_StatusTypeDef KEY_Scanf(KEY_HandleTypeDef * const head);
//�����������Ƿ���ڴ���ӵ�����
KEY_HandleTypeDef * KEY_LookUp(KEY_HandleTypeDef**root,KEY_NUMBER keynumber);
KEY_StatusTypeDef KEY_Free(KEY_HandleTypeDef *head);

KEY_StatusTypeDef  KEY_InstallList(KEY_HandleTypeDef **root,KEY_NUMBER keynumber,
  Read readkey,KEY_EventTypeDef event,keyCallBack callback);
#ifdef __cplusplus
}
#endif

#endif
