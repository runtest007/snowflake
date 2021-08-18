#ifndef __SNOWFLAKE__H
#define __SNOWFLAKE__H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/unistd.h>
#include <errno.h>
#include<linux/types.h>
#include <sys/time.h>

#define REMAIN_BIT 22
#define MIN_SEQ_BIT 7
#define DEFAULT_MACHINE_BIT 5
#define DEFAULT_THREAD_BIT 5


#define GENERATOR_ID_ERROR -1
#define GENERATOR_ID_DEFAULT 0

#define DEFAULT_TIME_SET 1555322400

class CSnowFlakeGenerator
{
	private:
		u_int16_t u16MachineBitNum;  	//����λ��max 31
		u_int16_t u16ThreadBitNum;   	//�߳�λ��	 max 31
		
		u_int64_t u64ThreadId;			//�߳�ID Ϊ����λ�����u64
		u_int64_t u64MachineCode;		//������ Ϊ����λ�����u64
		
		u_int16_t u16ThreadOffset;		//�߳�ƫ����
		u_int16_t u16MachineOffset;		//�����������
		u_int16_t u16TimeStampOffset;	//ʱ���ƫ����

		u_int16_t u16RemainBit;			//Ԥ��λ��,64 λ�е�һλ��ʹ�ã�41 λΪ���뼶ʱ�������22λΪԤ������������߳�id�Լ����������к�ʹ��
		
		u_int64_t u64MaxSeq;			//�������ֵ
		int64_t   i64StartTimeStamp;	//��ȥ��ĳ��ʱ���[2019/04/15/18:00:00]
		u_int64_t u64Sequence;			//��ǰ���

		int64_t i64LastTimeStamp;		//�ϴ�ʱ���

	private:
		int64_t GetMillSecTime()
        {
			struct timeval tmval;
			gettimeofday(&tmval,NULL);
			return (tmval.tv_sec*1000 + tmval.tv_usec/1000);
		}

		int64_t GetNextMillSecTime()
		{
			//�ȴ���һ�������
			while(1)
			{
				if(i64LastTimeStamp < GetMillSecTime())
				{
					i64LastTimeStamp = GetMillSecTime();
					break;
				}
			}
		}

	public:
		CSnowFlakeGenerator(u_int16_t MachineBitNum,u_int16_t ThreadBitNum,u_int16_t ThreadId,u_int16_t MachineCode);
		int64_t GetNextId();
		
};

#endif
