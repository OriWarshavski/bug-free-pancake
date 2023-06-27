#include "queueG.h"
#include "hashMap.h"
#include "groupMng.h"
#include <string.h>
#include <stdlib.h>
#define PULL_ID_SIZE 100
#define IP_LEN 13
/*...................................................................*/
static int MyItoA (int _num, char *_str);
static int Reverse (char *_str, int _length);
static char* PullIP(char* _ipToInsert);
static char* GetIp(int _i);
static int BuildIpq(Queue* _queue);
static void DestroyIp(void* _ip);
/*...................................................................*/
struct groupMng
{
    HashMap* m_groupMap;
    Queue* m_ipq;
};
/*...................................................................*/
groupMng* CreateGroupMng(char* _name)
{
    groupMng* newMng;
    if(_name == NULL)
    {
        return NULL;
    }
    if((newMng = (groupMng*)malloc(sizeof(groupMng))) == NULL)
    {
        return NULL;
    }

    if((newMng -> m_ipq = QueueCreate(PULL_ID_SIZE)) == NULL)
    {
        free(newMng);
        return NULL;
    }
    if(BuildIpq(newMng -> m_ipq) == -1)
    {
        QueueDestroy(&(newMng -> m_ipq), NULL);
        free(newMng);
        return NULL;
    }
    /*create hashMap*/
    return newMng;
}
/*...................................................................*/
void GroupMngDestroy(groupMng** _mng)
{
    if(_mng == NULL || *_mng == NULL)
    {
        return;
    }
    QueueDestroy(&((*_mng) -> m_ipq), DestroyIp);
    free(*_mng);
    *_mng = NULL;
}
/*...................................................................*/
/*......................ASSISTANCE FUNCTIONS.........................*/
/*...................................................................*/
static int BuildIpq(Queue* _queue)
{
    void* ip;
    char newIp[IP_LEN];
    int i;
    for(i = 0; i < PULL_ID_SIZE; ++i)
    {
        strcpy(newIp, GetIp(i));
        if(QueueInsert(_queue, newIp) != QUEUE_SUCCESS)
        {
            return -1;
        }
    }
    return 1;
}
/*...................................................................*/
static char* GetIp(int _i)
{
    char* newIp;
    char strNum[3];
    if((newIp = (char*)malloc(12*sizeof(char))) == NULL)
    {
        return NULL;
    }
    MyItoA(_i, strNum);
    strcpy(newIp, "244.");
    strcpy(&newIp[4], strNum);
    strcat(newIp, ".0.0");
    return newIp;
}
/*...................................................................*/
static void DestroyIp(void* _ip)
{
    free(_ip);
}
/*...........................................................*/
/*...........................................................*/
static int MyItoA (int _num, char *_str)
{
	int i, minus = 0;
	if (_num == 0)
	{
		*_str = '0';
		*(_str + 1) = '\0';
		return 1;
	}
	if (_num < 0)
	{
		minus = 1;
		_num = (-1)*_num;
	}
	for (i=0 ; _num > 0; i++)
	{
		*(_str+i) = (_num % 10) + '0';
		_num /= 10;
	} 
	if (minus == 1)
	{
		*(_str + i) = '-';
		*(_str + i + 1) = '\0';
	}
	else
	{
		*(_str + i) = '\0';
	}
    	Reverse(_str, strlen(_str));
    return 1;
}
/*...........................................................*/
static int Reverse (char *_str, int _length)
{
	char i, length, temp;
	for (i=0; i < (_length/2); i++)
	{
	    temp = *(_str+i);
	    *(_str+i) = *(_str+_length-i-1);
	    *(_str+_length-i-1) = temp;
	}
    return 1;
}
/*...........................................................*/