#ifndef APP_STATUS_MAXCHINE_USER_H
#define APP_STATUS_MAXCHINE_USER_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "stm32f0xx_hal.h"	 

//函数执行状态
typedef enum {
  StatusMachine_OK   = 0,
  StatusMachine_FAIL,
}StatusMachine_StatusTypeDef;
	 


//状态表驱动，包括设备状态和根据状态对应的处理函数
#define STATE_TABLE \
		ENTRY(DEVICE_POWER_OFF,StatusMachine_DevicePowerOff)   \
		ENTRY(DEVICE_TRYING_POWER_OFF,StatusMachine_DEVICE_TRYING_POWER_OFF)\
		ENTRY(DEVICE_STANDBY,StatusMachine_DEVICE_STANDBY)   \
		ENTRY(DEVICE_LOW_POWER_ACTIVE,StatusMachine_DEVICE_LOW_POWER_ACTIVE)   \
		ENTRY(DEVICE_SYNC_MODE,StatusMachine_DEVICE_SYNC_MODE)   \
		ENTRY(DEVICE_DFU_MODE,StatusMachine_DEVICE_DFU_MODE)   \
		ENTRY(DEVICE_ACTIVE,StatusMachine_DEVICE_ACTIVE)   \
		ENTRY(DEVICE_OFFLINE,StatusMachine_DEVICE_OFFLINE)   


//设备状态
typedef enum
{
	#define ENTRY(a,b)  a,
		STATE_TABLE
	#undef ENTRY
	MAX_NUM_STATE
}DEVICE_StateTypeDef;	 

#define  IS_DEVICE_StateTypeDef(stateType) ((stateType == DEVICE_POWER_OFF)|| \
											(stateType == DEVICE_TRYING_POWER_OFF)|| \
											(stateType == DEVICE_STANDBY)|| \
											(stateType == DEVICE_LOW_POWER_ACTIVE)|| \
											(stateType == DEVICE_SYNC_MODE)|| \
											(stateType == DEVICE_DFU_MODE) ||\
											(stateType == DEVICE_ACTIVE)|| \
											(stateType == DEVICE_OFFLINE) \
											)



	 
//内存中单字节对齐
#pragma pack(1)

typedef struct
{
    DEVICE_StateTypeDef device_state;
    
}StatusMachine_HandleTypeDef;	

#pragma pack()	 
	 
 
//全局变量
extern  StatusMachine_HandleTypeDef   device_status;	 
	 
	 
//获取设备当前状态
DEVICE_StateTypeDef StatusMachine_GetDeviceState(void);
//设置设备为新的状态
void StatusMachine_SetDeviceState(DEVICE_StateTypeDef state);
//状态机初始化
void StatusMachine_Init(void);
//状态机线程
void StatusMachine_thread(void);
	 

#ifdef __cplusplus
}
#endif

#endif


