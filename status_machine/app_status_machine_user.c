#include "app_status_machine_user.h"
#include "battery.h"
#include "app_debug.h"
#include "app_power_user.h"
#include "app_key_user.h"
#include "rgbled.h"

//全局变量
StatusMachine_HandleTypeDef   device_status;



//回调函数声明
#define ENTRY(a,b)  static void b(void);
	STATE_TABLE
#undef ENTRY

typedef void (*DeviceStateCallback)(void);
//回调函数状态表
DeviceStateCallback DeviceStateCallbackTable[MAX_NUM_STATE]={
	
	#define ENTRY(a,b) b,
	   STATE_TABLE
	#undef  ENTRY
	
};


//根据状态驱动不同函数
static StatusMachine_StatusTypeDef  StatusMachine_Handle(StatusMachine_HandleTypeDef * hStatusMachine);




//状态机初始化
void StatusMachine_Init(void)
{
	
}
//状态机线程
void StatusMachine_thread(void)
{
	StatusMachine_Handle(&device_status);
}

//获取设备当前状态
DEVICE_StateTypeDef StatusMachine_GetDeviceState(void)
{
    return device_status.device_state;
	
}
//设置设备为新的状态
void StatusMachine_SetDeviceState(DEVICE_StateTypeDef state)
{
    device_status.device_state= state; 
}




//设备关机
static void StatusMachine_DevicePowerOff(void)
{
	//KEY_DeInit();//释放为按键分配的内存
	LED_GREEN_CLOSE();
	OFF_SYS_POWER();//关闭系统电源
}
//设备待机
static void StatusMachine_DEVICE_STANDBY(void)
{
	
}
//设备低电状态
static void StatusMachine_DEVICE_LOW_POWER_ACTIVE(void)
{
	
}
//设备处于同步模式
static void StatusMachine_DEVICE_SYNC_MODE(void)
{
	
}
//设备处于升级模式
static void StatusMachine_DEVICE_DFU_MODE(void)
{
	
}

//设备尝试关机
static void StatusMachine_DEVICE_TRYING_POWER_OFF(void)
{
	
}


static void StatusMachine_DEVICE_ACTIVE(void)
{
	
}

static void StatusMachine_DEVICE_OFFLINE(void)
{
	
}






//根据状态驱动不同函数
static StatusMachine_StatusTypeDef  StatusMachine_Handle(StatusMachine_HandleTypeDef * hStatusMachine)
{
	if(hStatusMachine == NULL)
	{
		return StatusMachine_FAIL;
	}
	if(IS_DEVICE_StateTypeDef(hStatusMachine->device_state))//判断是否是状态机状态
	{
		if(DeviceStateCallbackTable[hStatusMachine->device_state] != NULL)//函数指针不为空
		{
			DeviceStateCallbackTable[hStatusMachine->device_state]();//状态机回调函数
			return StatusMachine_OK;
		}
		else
		{
			return StatusMachine_FAIL;
		}
	}
	else
	{
		return StatusMachine_FAIL;
	}
}















