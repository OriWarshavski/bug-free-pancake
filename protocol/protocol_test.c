#include "protocol.h"
#include <string.h>
#include <stdio.h>
/*...................................................................*/
void Test1PackRegReq(void);
void Test1UnpackRegReq(void);
void Test1PackRegReply(void);
void Test1UnpackRegReply(void);
void Test1PackLogReq(void);
void Test1UnpackLogReq(void);
void Test1PackLogReply(void);
void Test1PackCreateGroupReq(void);
void Test1UnpackCreateGroupReq(void);
void Test1PackCreateGroupReply(void);
void Test1UnpackCreateGroupReply(void);
void Test1PackPrintGroupReply(void);
void Test1UnpackPrintGroupReply(void);
void Test1PackLogOutReq(void);
void Test1UnpackLogOutReq(void);
void Test1PackLogOutReply(void);
void Test1UnpackLogOutReply(void);
/*...................................................................*/
int main()
{
    Test1PackRegReq();
    Test1UnpackRegReq();
    Test1PackRegReply();
    Test1UnpackRegReply();
    Test1PackLogReq();
    Test1UnpackLogReq();
    Test1PackLogReply();
	Test1PackCreateGroupReq();
	Test1UnpackCreateGroupReq();
	Test1PackCreateGroupReply();
	Test1UnpackCreateGroupReply();
	Test1PackPrintGroupReply();
	Test1UnpackPrintGroupReply();
	Test1PackLogOutReq();
	Test1UnpackLogOutReq();
	Test1PackLogOutReply();
	Test1UnpackLogOutReply();
    return 0;
}
/*...................................................................*/
void Test1PackRegReq(void)
{
    ClientDetails user;
    int result;
    char buffer[50];
    strcpy(user.m_userName, "matanel");
    strcpy(user. m_password, "1234");
    result = PackRegReq(&user, buffer);
    if(result == 15 && strcmp(&buffer[11], "1234") == 0 && strncmp(&buffer[3], "matanel", 7) == 0 && buffer[0] == REG_REQ && buffer[1] == 13 && buffer[2] == 7 && buffer[2] == 7 && buffer[10] == 4)
	{
		printf("%-50s %s\n" ,"Test1 PACK REGESTRATION REQ" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 PACK REGESTRATION REQ" ,"FAIL");
	}
}
/*...................................................................*/
void Test1UnpackRegReq(void)
{
    ClientDetails user;
    ClientDetails user2;
    int msgLen;
    char buffer[50];
    strcpy(user.m_userName, "matanel");
    strcpy(user. m_password, "1234");
    msgLen = PackRegReq(&user, buffer);
    user2 = UnpackRegReq(buffer, msgLen);
    if(strcmp(user2.m_userName, "matanel") == 0 && strcmp(user2.m_password, "1234") == 0)
	{
		printf("%-50s %s\n" ,"Test1 UNPACK REGESTRATION REQ" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 UNPACK REGESTRATION REQ" ,"FAIL");
	}
}
/*...................................................................*/
void Test1PackRegReply(void)
{
    char buffer[50];
    if(PackRegReply(REPLY_SUCCESS, buffer) == 3 && buffer[0] == REG_REPLY  && buffer[1] == 2 && buffer[2] == REPLY_SUCCESS)
	{
		printf("%-50s %s\n" ,"Test1 PACK REGESTRATION REPLY" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 PACK REGESTRATION REPLY" ,"FAIL");
	}
}
/*...................................................................*/
void Test1UnpackRegReply(void)
{
    char buffer[50];
    PackRegReply(REPLY_SUCCESS, buffer);
    if(UnpackRegReply(buffer, 3) == REPLY_SUCCESS)
	{
		printf("%-50s %s\n" ,"Test1 UNPACK REGESTRATION REPLY" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 UNPACK REGESTRATION REPLY" ,"FAIL");
	}
}
/*...................................................................*/
void Test1PackLogReq(void)
{
    ClientDetails user;
    int result;
    char buffer[50];
    strcpy(user.m_userName, "matanel");
    strcpy(user. m_password, "1234");
    result = PackLogReq(&user, buffer);
    if(result == 15 && strcmp(&buffer[11], "1234") == 0 && strncmp(&buffer[3], "matanel", 7) == 0 && buffer[0] == LOG_REQ && buffer[1] == 13 && buffer[2] == 7 && buffer[2] == 7 && buffer[10] == 4)
	{
		printf("%-50s %s\n" ,"Test1 PACK LOGIN REQ" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 PACK LOGIN REQ" ,"FAIL");
	}
}
/*...................................................................*/
void Test1UnpackLogReq(void)
{
    ClientDetails user;
    ClientDetails user2;
    int msgLen;
    char buffer[50];
    strcpy(user.m_userName, "matanel");
    strcpy(user. m_password, "1234");
    msgLen = PackLogReq(&user, buffer);
    user2 = UnpackLogReq(buffer, msgLen);
    if(strcmp(user2.m_userName, "matanel") == 0 && strcmp(user2.m_password, "1234") == 0)
	{
		printf("%-50s %s\n" ,"Test1 UNPACK LOGIN REQ" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 UNPACK LOGIN REQ" ,"FAIL");
	}
}
/*...................................................................*/
void Test1PackLogReply(void)
{
    char buffer[50];
    if(PackLogReply(REPLY_SUCCESS, buffer) == 3 && buffer[0] == LOG_REPLY && buffer[1] == 2 && buffer[2] == REPLY_SUCCESS)
	{
		printf("%-50s %s\n" ,"Test1 PACK LOGIN REPLY" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 PACK LOGIN REPLY" ,"FAIL");
	}
}
/*...................................................................*/
void Test1PackCreateGroupReq(void)
{
    GroupDetails group;
    int result;
    char buffer[50];
    strcpy(group.m_userName, "matanel");
    strcpy(group. m_groupName, "room 1");
    result = PackCreateGroupReq(&group, buffer);
    if(result == 17 && strcmp(&buffer[11], "room 1") == 0 && strncmp(&buffer[3], "matanel", 7) == 0 && buffer[0] == GROUP_CREATE_REQ && buffer[1] == 15 && buffer[2] == 7&& buffer[10] == 6)
	{
		printf("%-50s %s\n" ,"Test1 PACK CREATE GROUP REQ" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 PACK CREATE GROUP REQ" ,"FAIL");
	}
}
/*...................................................................*/
void Test1UnpackCreateGroupReq(void)
{
    GroupDetails group;
    GroupDetails group2;
    int msgLen;
    char buffer[50];
    strcpy(group.m_userName, "matanel");
    strcpy(group. m_groupName, "room 1");
    msgLen = PackCreateGroupReq(&group, buffer);
    group2 = UnpackCreateGroupReq(buffer, msgLen);
    if(strcmp(group2.m_userName, "matanel") == 0 && strcmp(group2.m_groupName, "room 1") == 0)
	{
		printf("%-50s %s\n" ,"Test1 UNPACK CREATE GROUP REQ" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 UNPACK CREATE GROUP REQ" ,"FAIL");
	}
}
/*...................................................................*/
void Test1PackCreateGroupReply(void)
{
    char buffer[50];
	GroupDetails group;
    strcpy(group.m_userName, "matanel");
    strcpy(group. m_ip, "255.43.12.6");
	strcpy(group. m_port, "23456");
	group. m_status = 1;
    if(PackCreateGroupReply(&group, buffer) == 21 && buffer[0] == GROUP_CREATE_REPLY && buffer[1] == 19 && buffer[2] == 11 && buffer[14] == 5)
	{
		printf("%-50s %s\n" ,"Test1 PACK CREATE GROUP REPLY" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 PACK CREATE GROUP REPLY" ,"FAIL");
	}
}
/*...................................................................*/
void Test1UnpackCreateGroupReply(void)
{
    char buffer[50];
	GroupDetails group, group2;
	int msgLen;
    strcpy(group.m_userName, "matanel");
    strcpy(group. m_ip, "255.43.12.6");
	strcpy(group. m_port, "23456");
	group. m_status = 1;
	msgLen = PackCreateGroupReply(&group, buffer);
	group2 = UnpackCreateGroupReply(buffer, msgLen);
    if(strcmp(group2.m_ip, "255.43.12.6") == 0 && group2.m_status == 1 && strcmp(group2.m_port, "23456") == 0)
	{
		printf("%-50s %s\n" ,"test1 UNPACK CREATE GROUP REPLY" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"test1 UNPACK CREATE GROUP REPLY" ,"FAIL");
	}
}
/*...................................................................*/
void Test1PackPrintGroupReply(void)
{
    char buffer[50];
	GroupDetails group;
    strcpy(group.m_groupList, "A\nB\nC\n");
    group. m_status = 1;
    if(PackPrintGroupsReply(&group, buffer) == 10 && buffer[0] == PRINT_GROUPS_REPLY && buffer[1] == 8 && buffer[2] == 6 && buffer[9] == 1)
	{
		printf("%-50s %s\n" ,"test1 PACK PRINT GROUPS REPLY" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"test1 PACK PRINT GROUPS REPLY" ,"FAIL");
	}
}
/*...................................................................*/
void Test1UnpackPrintGroupReply(void)
{
    char buffer[50];
	int msgLen;
	GroupDetails group, group2;
    strcpy(group.m_groupList, "A\nB\nC");
    group. m_status = 1;
	msgLen = PackPrintGroupsReply(&group, buffer);
	group2 = UnpackPrintGroupsReply(buffer, msgLen);
    if(strcmp(group2.m_groupList, "A\nB\nC") == 0 && group2.m_status == 1)
	{
		printf("%-50s %s\n" ,"test1 UNPACK PRINT GROUPS REPLY" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"test1 UNPACK PRINT GROUPS REPLY" ,"FAIL");
	}
}
/*...................................................................*/
/*...................................................................*/
void Test1PackLogOutReq(void)
{
    GroupDetails group;
    int result;
    char buffer[50];
    strcpy(group.m_userName, "matanel");
    result = PackLogOutReq(&group, buffer);
    if(result == 10 && strncmp(&buffer[3], "matanel", 7) == 0 && buffer[0] == LOG_OUT_REQ && buffer[1] == 8 && buffer[2] == 7)
	{
		printf("%-50s %s\n" ,"test1 PACK LOGOUT REQ" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"test1 PACK LOGOUT REQ" ,"FAIL");
	}
}
/*...................................................................*/
void Test1UnpackLogOutReq(void)
{
    GroupDetails group;
    GroupDetails group2;
    int msgLen;
    char buffer[50];
    strcpy(group.m_userName, "matanel");
    strcpy(group. m_groupName, "room 1");
    msgLen = PackLogOutReq(&group, buffer);
    group2 = UnpackLogOutReq(buffer, msgLen);
    if(strcmp(group2.m_userName, "matanel") == 0)
	{
		printf("%-50s %s\n" ,"Test1 UNPACK LOGOUT REQ CORRECT" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1UnpackCreateGroupReq CORRECT" ,"FAIL");
	}
}
/*...................................................................*/
void Test1PackLogOutReply(void)
{
    char buffer[50];
    if(PackLogOutReply(REPLY_SUCCESS, buffer) == 3 && buffer[0] == LOG_OUT_REPLY  && buffer[1] == 2 && buffer[2] == REPLY_SUCCESS)
	{
		printf("%-50s %s\n" ,"Test1 PACK LOGOUT REPLY" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 PACK LOGOUT REPLY" ,"FAIL");
	}
}
/*...................................................................*/
void Test1UnpackLogOutReply(void)
{
    char buffer[50];
    PackLogOutReply(REPLY_SUCCESS, buffer);
    if(UnpackLogOutReply(buffer, 3) == REPLY_SUCCESS)
	{
		printf("%-50s %s\n" ,"Test1 UNPACK LOGOUT REPLY" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 UNPACK LOGOUT REPLY" ,"FAIL");
	}
}