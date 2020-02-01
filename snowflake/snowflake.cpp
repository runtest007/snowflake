#include "snowflake.h"

/*
Ĭ������� ��������߳�idһ��ռ��10λ��ʣ��12λ�������кţ���ô1������߳̿��Խ���4096�������㹻���ˣ����(ʹ��7λ)ÿ���������128�����к�
����Ϳ���Ϊ���߳�ÿ���ṩ12.8w���½��������к�
|0|00000000000000000000000000000000000000000|0000000000|000000000000|
*/
CSnowFlakeGenerator::CSnowFlakeGenerator(u_int16_t MachineBitNum,u_int16_t ThreadBitNum,u_int16_t ThreadId,u_int16_t MachineCode)
{
	u16MachineBitNum = MachineBitNum;
	u16ThreadBitNum = ThreadBitNum;

	u64ThreadId = ThreadId;
	u64MachineCode = MachineCode;

	u16RemainBit = REMAIN_BIT;

	if((u16MachineBitNum+u16ThreadBitNum)>(u16RemainBit-MIN_SEQ_BIT)){
		LOGGER_INFO(formatStr("machine code and thread id is bigger"));
		u16MachineBitNum = DEFAULT_MACHINE_BIT;
		u16ThreadBitNum = DEFAULT_THREAD_BIT;
	}

	
	i64StartTimeStamp = DEFAULT_TIME_SET;
	
	i64LastTimeStamp = 0;

	/*���к���ʹ�õ�λ��*/
	u_int16_t seqbit = u16RemainBit - u16MachineBitNum - u16ThreadBitNum;
	u64MaxSeq = (1<<seqbit) -1;

	/*������ƫ��λ*/
	u16MachineOffset = seqbit;

	/*�߳�IDƫ��*/
	u16ThreadOffset = seqbit + 	u16MachineBitNum;

	/*ʱ���ƫ��*/
	u16TimeStampOffset = seqbit + u16ThreadBitNum + u16MachineBitNum;

	u64Sequence = 0;


	
}

int64_t CSnowFlakeGenerator::GetNextId()
{
	int64_t i64CurrentMillSec = 0;
	int64_t retval=0;
	
	i64CurrentMillSec=GetMillSecTime();
	if(i64CurrentMillSec < i64LastTimeStamp){
		LOGGER_ERROR(formatStr("error time stamp create!!"));
		return -1;
	}
	
	/*�����ǰ����ʱ������ϴκ���ʱ�� ���������к�*/
	if(i64CurrentMillSec == i64LastTimeStamp){
		i64LastTimeStamp = i64CurrentMillSec;
		u64Sequence ++;
		if(u64Sequence >= u64MaxSeq){
			GetNextMillSecTime();
		}
		
	}else{
		//�������ϴκ���ʱ����seq ��0
		i64LastTimeStamp = i64CurrentMillSec;
		u64Sequence = 0;
	}
	//printf("=====%u====%u====%u===%u===",u16TimeStampOffset,u16ThreadOffset,u16MachineOffset,u64Sequence);

	//printf("x1:%d====x2:%u====x3:%u===\n",i64CurrentMillSec-i64StartTimeStamp,u64ThreadId,u64MachineCode);
	retval = ((i64CurrentMillSec-i64StartTimeStamp)<<u16TimeStampOffset) | \
		u64ThreadId<< u16ThreadOffset | u64MachineCode<<u16MachineOffset | u64Sequence;

	//printf("================return val:%ld====\n",retval);
	return retval;

}


