
#ifndef APP_KEY_USER_H
#define APP_KEY_USER_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
	 
#include "app_key.h"



extern KEY_HandleTypeDef *head;



void KEY_Init(void);
void KEY_InitTimer(void);
void KEY_Detect_thread(void);	
void KEY_DeInit(void);	 
#ifdef __cplusplus
}
#endif

#endif
