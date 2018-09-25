#include "app_status_machine_user.h"
#include "battery.h"
#include "app_debug.h"
#include "app_power_user.h"
#include "app_key_user.h"
#include "rgbled.h"

//ȫ�ֱ���
StatusMachine_HandleTypeDef   device_status;



//�ص���������
#define ENTRY(a,b)  static void b(void);
	STATE_TABLE
#undef ENTRY

typedef void (*DeviceStateCallback)(void);
//�ص�����״̬��
DeviceStateCallback DeviceStateCallbackTable[MAX_NUM_STATE]={
	
	#define ENTRY(a,b) b,
	   STATE_TABLE
	#undef  ENTRY
	
};


//����״̬������ͬ����
static StatusMachine_StatusTypeDef  StatusMachine_Handle(StatusMachine_HandleTypeDef * hStatusMachine);




//״̬����ʼ��
void StatusMachine_Init(void)
{
	
}
//״̬���߳�
void StatusMachine_thread(void)
{
	StatusMachine_Handle(&device_status);
}

//��ȡ�豸��ǰ״̬
DEVICE_StateTypeDef StatusMachine_GetDeviceState(void)
{
    return device_status.device_state;
	
}
//�����豸Ϊ�µ�״̬
void StatusMachine_SetDeviceState(DEVICE_StateTypeDef state)
{
    device_status.device_state= state; 
}




//�豸�ػ�
static void StatusMachine_DevicePowerOff(void)
{
	//KEY_DeInit();//�ͷ�Ϊ����������ڴ�
	LED_GREEN_CLOSE();
	OFF_SYS_POWER();//�ر�ϵͳ��Դ
}
//�豸����
static void StatusMachine_DEVICE_STANDBY(void)
{
	
}
//�豸�͵�״̬
static void StatusMachine_DEVICE_LOW_POWER_ACTIVE(void)
{
	
}
//�豸����ͬ��ģʽ
static void StatusMachine_DEVICE_SYNC_MODE(void)
{
	
}
//�豸��������ģʽ
static void StatusMachine_DEVICE_DFU_MODE(void)
{
	
}

//�豸���Թػ�
static void StatusMachine_DEVICE_TRYING_POWER_OFF(void)
{
	
}


static void StatusMachine_DEVICE_ACTIVE(void)
{
	
}

static void StatusMachine_DEVICE_OFFLINE(void)
{
	
}






//����״̬������ͬ����
static StatusMachine_StatusTypeDef  StatusMachine_Handle(StatusMachine_HandleTypeDef * hStatusMachine)
{
	if(hStatusMachine == NULL)
	{
		return StatusMachine_FAIL;
	}
	if(IS_DEVICE_StateTypeDef(hStatusMachine->device_state))//�ж��Ƿ���״̬��״̬
	{
		if(DeviceStateCallbackTable[hStatusMachine->device_state] != NULL)//����ָ�벻Ϊ��
		{
			DeviceStateCallbackTable[hStatusMachine->device_state]();//״̬���ص�����
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















