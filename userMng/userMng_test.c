#include "usermng.h"
#include <stdio.h>
#include "listG.h"  
/*...........................................................*/
static void Test1MngLeaveCorrect(void);
static void Test2MngLeaveCorrect(void);
static void Test3MngLeaveCorrect(void);
static void Test1MngLogOutCorrect(void);
static void Test2MngLogOutInorrect(void);
static void Test3MngLogOutInorrect(void);
/*...........................................................*/
int main ()
{
    Test1MngLeaveCorrect();
    Test2MngLeaveCorrect();
    Test3MngLeaveCorrect();
    Test1MngLogOutCorrect();
    Test2MngLogOutInorrect();
    Test3MngLogOutInorrect();
    return 0;
}
/*...........................................................*/
static void Test1MngLeaveCorrect(void)
{
    UserMng* mng = CreateUserMng();
    int status, status2;
    AddUser(mng, 123, "ori", "1234");
    status2 = LogIn(mng, "ori",  "1234");
    JoinGroup(mng, "ori", "group1");
    status = LeaveGroup(mng, "ori", "group1");
    if(status == UM_SUCCESS && status2 == UM_SUCCESS)
	{
		printf("%-50s %s\n" ,"Test1 LEAVE GROUP CORRECT" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 LEAVE GROUP CORRECT" ,"FAIL");
	}
    DestroyUserMng(&mng);
}
/*...........................................................*/
static void Test2MngLeaveCorrect(void)
{
    UserMng* mng = CreateUserMng();
    int status;
    AddUser(mng, 123, "ori", "1234");
    LogIn(mng, "ori",  "1234");
    JoinGroup(mng, "ori", "group1");
    status = LeaveGroup(mng, "ori", "group2");
    if(status == UM_GROUP_NOT_FOUND)
	{
		printf("%-50s %s\n" ,"Test2 LEAVE GROUP GROUP NOT FOUND" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test2 LEAVE GROUP GROUP NOT FOUND" ,"FAIL");
	}
    DestroyUserMng(&mng);
}
/*...........................................................*/
static void Test3MngLeaveCorrect(void)
{
    UserMng* mng = CreateUserMng();
    int status;
    AddUser(mng, 123, "ori", "1234");
    LogIn(mng, "ori",  "1234");
    JoinGroup(mng, "ori", "group1");
    status = LeaveGroup(mng, "matanel", "group1");
    if(status == UM_USER_NOT_EXIST)
	{
		printf("%-50s %s\n" ,"Test3 LEAVE GROUP USER NOT FOUND" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test3 LEAVE GROUP USER NOT FOUND" ,"FAIL");
	}
    DestroyUserMng(&mng);
}
/*...........................................................*/
static void Test1MngLogOutCorrect(void)
{
    UserMng* mng = CreateUserMng();
    int status1, status2;
    void* lastG, *firstG;
    List* groups = ListCreate();
    AddUser(mng, 123, "shaul", "1234");
    LogIn(mng, "shaul",  "1234");
    JoinGroup(mng, "shaul", "group0");
    JoinGroup(mng, "shaul", "group1");
    JoinGroup(mng, "shaul", "group2");
    status1 = LogOut(mng, "shaul", groups);
    status2 = ListSize(groups);
    ListPopTail(groups, &lastG);
    ListPopHead(groups, &firstG);
    if(status1 == UM_SUCCESS && status2 == 3 && strcmp((char*)lastG, "group2") == 0 && strcmp((char*)firstG, "group0") == 0)
	{
		printf("%-50s %s\n" ,"Test1 LOGOUT CORRECT" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 LOGOUT CORRECT" ,"FAIL");
	}
    ListDestroy(&groups, NULL);
    DestroyUserMng(&mng);
}
/*...........................................................*/
static void Test2MngLogOutInorrect(void)
{
    UserMng* mng = CreateUserMng();
    int status1, status2;
    void* lastG, *firstG;
    List* groups = ListCreate();
    AddUser(mng, 123, "shaul", "1234");
    status2 = JoinGroup(mng, "shaul", "group0");
    status1 = LogOut(mng, "shaul", groups);
    if(status1 == UM_NOT_ACTIVE_ERROR && status2 == UM_NOT_ACTIVE_ERROR)
	{
		printf("%-50s %s\n" ,"Test2 LOGOUT NOT ACTIVE" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test2 LOGOUT NOT ACTIVE" ,"FAIL");
	}
    ListDestroy(&groups, NULL);
    DestroyUserMng(&mng);
}
/*...........................................................*/
static void Test3MngLogOutInorrect(void)
{
    UserMng* mng = CreateUserMng();
    int status1;
    void* lastG, *firstG;
    List* groups = ListCreate();
    AddUser(mng, 123, "shaul", "1234");
    LogIn(mng, "shaul",  "1234");
    JoinGroup(mng, "shaul", "group0");
    status1 = LogOut(mng, "persi", groups);
    if(status1 == UM_USER_NOT_EXIST)
	{
		printf("%-50s %s\n" ,"Test3 LOGOUT USER NOT FOUND" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test3 LOGOUT USER NOT FOUND" ,"FAIL");
	}
    ListDestroy(&groups, NULL);
    DestroyUserMng(&mng);
}