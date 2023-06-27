#include "user.h"
#include "hashMap.h"
#include <stdio.h>
#include <string.h>         /*strcmp*/
/*...........................................................*/
int GetUserId(User* _user);
char* GetName(User* _user);
char* GetPass(User* _user);
/*...........................................................*/
static void Test1UserCreateCorrect(void);
static void Test1UserDestroy(void);
static void Test2UserCreateIncorrect(void);
static void Test3UserCreateIncorrect(void);
static void Test4UserCreateIncorrect(void);
static void Test2UserDestroy(void);
static void Test3UserDestroyIncorrect(void);
static void Test4UserDestroyIncorrect(void);
static void Test1UserIsActive(void);
static void Test2UserIsActiveIncorrect(void);
static void Test1UserJoinGroup(void);
static void Test2UserJoinGroup(void);
static void Test1UserLeaveGroup(void);
static void Test2UserLeaveGroup(void);
static void Test1UserLogout(void);
static void Test1UserLogin(void);
/*...........................................................*/
int main()
{
    Test1UserCreateCorrect();
    Test2UserCreateIncorrect();
    Test3UserCreateIncorrect();
    Test4UserCreateIncorrect();
    Test1UserDestroy();
    Test2UserDestroy();
    Test3UserDestroyIncorrect();
    Test4UserDestroyIncorrect();
    Test1UserIsActive();
    Test2UserIsActiveIncorrect();
	Test1UserJoinGroup();
	Test2UserJoinGroup();
	Test1UserLeaveGroup();
	Test2UserLeaveGroup();
	Test1UserLogout();
	Test1UserLogin();
    return 0;
}
/*...........................................................*/
static void Test1UserCreateCorrect(void)
{
    User* user = UserCreate(3, "ori", "1234");
    if((user != NULL) && (GetUserId(user) == 3) && !strcmp(GetName(user), "ori") && !strcmp(GetPass(user), "1234") && GetGroupMap(user) == NULL)
	{
		printf("%-50s %s\n" ,"Test1 UserCreate CORRECT" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 UserCreate CORRECT" ,"FAIL");
	}
    DestroyUser(&user);
}
/*...........................................................*/
static void Test2UserCreateIncorrect(void)
{
    User* user = UserCreate(0, "ori", "1234");
    if(user == NULL)
	{
		printf("%-50s %s\n" ,"Test2 UserCreateIncorrect INCORRECT SOCKET" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test2 UserCreateIncorrect INCORRECT SOCKET" ,"FAIL");
	}
    DestroyUser(&user);
}
/*...........................................................*/
static void Test3UserCreateIncorrect(void)
{
    User* user = UserCreate(3, NULL, "1234");
    if(user == NULL)
	{
		printf("%-50s %s\n" ,"Test3 UserCreateIncorrect INCORRECT NAME" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test3 UserCreateIncorrect INCORRECT NAME" ,"FAIL");
	}
    DestroyUser(&user);
}
/*...........................................................*/
static void Test4UserCreateIncorrect(void)
{
    User* user = UserCreate(3, "ori", NULL);
    if(user == NULL)
	{
		printf("%-50s %s\n" ,"Test4 UserCreateIncorrect INCORRECT PASSWORD" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test4 UserCreateIncorrect INCORRECT PASSWORD" ,"FAIL");
	}
    DestroyUser(&user);
}
/*...........................................................*/
static void Test1UserDestroy(void)
{
    User* user = UserCreate(3, "ori", "1234");
    DestroyUser(&user);
    if(user == NULL)
	{
		printf("%-50s %s\n" ,"Test1 UserDestroy" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 UserDestroy" ,"FAIL");
	}
}
/*...........................................................*/
static void Test2UserDestroy(void)
{
    User* user = UserCreate(3, "ori", "1234");
    DestroyUser(&user);
    DestroyUser(&user);
    if(user == NULL)
	{
		printf("%-50s %s\n" ,"Test2 UserDestroy DOUBLE DESTROY" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test2U serDestroy DOUBLE DESTROY" ,"FAIL");
	}
}
/*...........................................................*/
static void Test3UserDestroyIncorrect(void)
{
    DestroyUser(NULL);
	printf("%-50s %s\n" ,"Test3 UserDestroy UNINITIALIZED **" ,"PASS");
}
/*...........................................................*/
static void Test4UserDestroyIncorrect(void)
{
    User* user = NULL;
    DestroyUser(&user);
	printf("%-50s %s\n" ,"Test4 UserDestroy UNINITIALIZED *" ,"PASS");
}
/*...........................................................*/
static void Test1UserIsActive(void)
{
    User* user = UserCreate(3, "ori", "1234");
    if(IsUserLoggedIn(user) == 0)
	{
		printf("%-50s %s\n" ,"Test1 UserIsActive CORRECT" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 UserIsActive CORRECT" ,"FAIL");
	}
    DestroyUser(&user);
}
/*...........................................................*/
static void Test2UserIsActiveIncorrect(void)
{
    if(IsUserLoggedIn(NULL) == -1)
	{
		printf("%-50s %s\n" ,"Test2 UserIsActive INCORRECT" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test2 UserIsActive INCORRECT" ,"FAIL");
	}
}
/*...........................................................*/
static void Test1UserJoinGroup(void)
{
    User* user = UserCreate(3, "ori", "1234");
	int status = UserJoinGroup(user, "group1");
	void* key, *val;
	HashMap* hash = GetGroupMap(user);
	HashMap_Remove(hash, "group1", &key, &val);
    if(status == USER_SUCCESS && strcmp((char*)key, "group1") == 0 && GetGroupMap(user) != NULL)
	{
		printf("%-50s %s\n" ,"Test1 UserJoinGroup CORRECT" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 UserJoinGroup CORRECT" ,"FAIL");
	}
	DestroyUser(&user);
}
/*...........................................................*/
static void Test2UserJoinGroup(void)
{
    User* user = UserCreate(3, "ori", "1234");
	int status;
	UserJoinGroup(user, "group1");
    if(UserJoinGroup(user, "group1") == USER_GROUP_DUPLICATE)
	{
		printf("%-50s %s\n" ,"Test2 UserJoinGroup DUPLICATE" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test2 UserJoinGroup DUPLICATE" ,"FAIL");
	}
	DestroyUser(&user);
}
/*...........................................................*/
static void Test1UserLeaveGroup(void)
{
    User* user = UserCreate(3, "ori", "1234");
	int status, status2, status3;
	void* key, *val;
	HashMap* hash;
	UserJoinGroup(user, "group1");
	UserJoinGroup(user, "group2");
	status = UserLeaveGroup(user, "group1");
	HashMap_Remove(hash, "group1", &key, &val);
	hash = GetGroupMap(user);
	status3 =  HashMap_Find(hash,"group2", &val);
	status2 = HashMap_Find(hash,"group1", &val);
    if(status == USER_SUCCESS && status2 == MAP_KEY_NOT_FOUND_ERROR && status3 == MAP_SUCCESS)
	{
		printf("%-50s %s\n" ,"Test1 UserLeaveGroup CORRECT" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 UserLeaveGroup CORRECT" ,"FAIL");
	}
	DestroyUser(&user);
}
/*...........................................................*/
static void Test2UserLeaveGroup(void)
{
    User* user = UserCreate(3, "ori", "1234");
	int status, status2, status3;
	void* key, *val;
	HashMap* hash;
	status = UserLeaveGroup(user, "group1");
    if(status == USER_GROUP_NOT_FOUND)
	{
		printf("%-50s %s\n" ,"Test2 UserLeaveGroup NOT FOUND" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test2 UserLeaveGroup NOT FOUND" ,"FAIL");
	}
	DestroyUser(&user);
}
/*...........................................................*/
static void Test1UserLogout(void)
{
    User* user = UserCreate(3, "ori", "1234");
	int status;
	HashMap* hash;
	UserLogIn(user, "1234");
	UserJoinGroup(user, "group1");
	hash = GetGroupMap(user);
	status = UserLogOut(user);
    if(status == USER_SUCCESS && HashMap_Size(hash) == 1 && GetGroupMap(user) == NULL && IsUserLoggedIn(user) == 0)
	{
		printf("%-50s %s\n" ,"Test1 USER LOGOUT CORRECT" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 USER LOGOUT CORRECT" ,"FAIL");
	}
	DestroyUser(&user);
}
/*...........................................................*/
static void Test1UserLogin(void)
{
    User* user = UserCreate(3, "ori", "1234");
	int status;
	HashMap* hash;
	status = UserLogIn(user, "1234");
    if(status == USER_SUCCESS && IsUserLoggedIn(user) == 1)
	{
		printf("%-50s %s\n" ,"Test1 USER LOGIN CORRECT" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1 USER LOGIN CORRECT" ,"FAIL");
	}
	DestroyUser(&user);
}