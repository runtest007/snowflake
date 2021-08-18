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
		u_int16_t u16MachineBitNum;  	//机器位数max 31
		u_int16_t u16ThreadBitNum;   	//线程位数	 max 31
		
		u_int64_t u64ThreadId;			//线程ID 为了移位定义成u64
		u_int64_t u64MachineCode;		//机器码 为了移位定义成u64
		
		u_int16_t u16ThreadOffset;		//线程偏移量
		u_int16_t u16MachineOffset;		//机器码便宜量
		u_int16_t u16TimeStampOffset;	//时间戳偏移量

		u_int16_t u16RemainBit;			//预留位数,64 位中第一位不使用，41 位为毫秒级时间戳，后22位为预留给机器码和线程id以及产生的序列号使用
		
		u_int64_t u64MaxSeq;			//最大序列值
		int64_t   i64StartTimeStamp;	//过去的某个时间戳[2019/04/15/18:00:00]
		u_int64_t u64Sequence;			//当前序号

		int64_t i64LastTimeStamp;		//上次时间戳

	private:
		int64_t GetMillSecTime()
        {
			struct timeval tmval;
			gettimeofday(&tmval,NULL);
			return (tmval.tv_sec*1000 + tmval.tv_usec/1000);
		}

		int64_t GetNextMillSecTime()
		{
			//等待下一毫秒出现
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
