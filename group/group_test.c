#include "group.h"
#include <stdio.h>
#include <string.h>

/*...................................................................*/
void Test1CreateGroup(void);
void Test1DestroyGroup(void);
/*...................................................................*/
int main()
{

    Test1CreateGroup();
	Test1DestroyGroup();
    return 0;
}
/*...................................................................*/
void Test1CreateGroup(void)
{
    Group* group = NULL;
	int* count;
    group = GroupCreate("room 1", "244.01.0.0");
	count = GetGroupCounter(group);
    if(group != NULL && strcmp(GetGroupName(group), "room 1") ==  0 && strcmp(GetGroupIp(group), "244.01.0.0") == 0 && GetGroupPort(group) == 8070 && *count == 1)
	{
		printf("%-50s %s\n" ,"Test1CreateGroup CORRECT" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1CreateGroup CORRECT" ,"FAIL");
	}
	GroupDestroy(&group);
}
/*...................................................................*/
void Test1DestroyGroup(void)
{
    Group* group = NULL;
    group = GroupCreate("room 1", "244.01.0.0");
    if(strcmp(GroupDestroy(&group), "244.01.0.0") == 0  && group == NULL)
	{
		printf("%-50s %s\n" ,"Test1DestroyGroup CORRECT" ,"PASS");
	}
	else
	{
		printf("%-50s %s\n" ,"Test1DestroyGroup CORRECT" ,"FAIL");
	}
}
/*...................................................................*/