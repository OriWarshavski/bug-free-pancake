#include <stdio.h>      /* for SaveData() */
#include <stdlib.h>
#include <string.h>     /* for strcpy() */
#include "usermng.h"
#include "hashMap.h"    /* for hasmap structure */
#include "user.h"       /* for user struct and user funs() */
#include "limit.h"      /* for capacity in CreateUserMng() */
#include "listG.h"      /*parameter for logout - ListPushTail*/

#define OK 0
#define ERROR -1
#define FILE_NOT_EXIST -2
#define ALLOCATION_ERROR -3
#define DEFAULT_ID 1 /* to enter in the LoadData*/
#define FILE_NAME "userfile.txt"

struct UserMng
{
    HashMap* m_userMap;
};

/* assistance functions */
static size_t HashByAscii(void* _userName);
static int CompareInt(void* _firstData, void* _secondData);
static void UserRemove(void* _user);
size_t GetUserMapSize(UserMng* _userMng);
static int IsDuplicate(UserMng* _userMng, char* _name);
static int CreateAndInsert(UserMng* _userMng, int _userId, char* _name,
char* _password, char** _valueUser);
static int SaveData(char* _name, char* _password);
static int LoadData(UserMng* _userMng);
static void* Find(UserMng* _userMng, char* _name);
static int SaveGroupNamesAction(const void* _groupName, void* _value, void* _context);
/* assistance functions */

UserMng* CreateUserMng()
{
    UserMng* userMng;
    HashMap* userMap;
    int resLoadData;
    userMng = (UserMng*)malloc(sizeof(UserMng));
    if (NULL == userMng)
    {
        return NULL;
    }
    userMap = HashMap_Create(CAPACITY_CLIENT, HashByAscii, CompareInt);
    if (NULL == userMap)
    {
        free(userMng);
        return NULL;
    }
    userMng -> m_userMap = userMap;
    resLoadData = LoadData(userMng);
    if (ALLOCATION_ERROR == resLoadData)
    {
        return NULL;
    }
    return userMng;
}

void DestroyUserMng(UserMng** _userMng)
{
    if (NULL == _userMng || NULL == *_userMng)
    {
        return;
    }
    HashMap_Destroy(&((*_userMng) -> m_userMap), NULL, UserRemove);
    free(*_userMng);
    *_userMng = NULL;
}

UMResult AddUser(UserMng* _userMng, int _userId, char* _name, char* _password)
{
    User* newUser;
    int resCreateAndInsert, resSaveData;
    void* keyTemp, *valueTemp;
    char* valueUser;
    if (NULL == _userMng || NULL == _name || NULL == _password)
    {
        return UM_UNINITIALIZED_ERROR;
    }
    if (IsDuplicate(_userMng, _name))
    {
        return UM_DUPLICATE;
    }
    resCreateAndInsert = CreateAndInsert(_userMng, _userId, _name,
        _password, &valueUser);
    if (OK != resCreateAndInsert)
    {
        return UM_ALLOCATION_ERROR;
    }
    resSaveData = SaveData(_name, _password);
    if (OK != resSaveData)
    {
        HashMap_Remove(_userMng -> m_userMap, _name, &keyTemp, &valueTemp);
        newUser = (User*)valueTemp;
        DestroyUser(&newUser);
        free(valueUser);
        return UM_SAVE_FILE_ERROR;
    }
    return UM_SUCCESS;
}

UMResult LogIn(UserMng* _userMng, char* _name, char* _password)
{
    void* resUser;
    char* pass;
    if (NULL == _userMng || NULL == _name || NULL == _password)
    {
        return UM_UNINITIALIZED_ERROR;
    }
    resUser = Find(_userMng, _name);
    if (NULL == resUser)
    {
        return UM_USER_NOT_EXIST;
    }
    if(IsUserLoggedIn(resUser))  /*----ori's update----*/
    {
        return UM_ACTIVE_ERROR;
    }
    if(UserLogIn(resUser, _password) != USER_SUCCESS)
    {
        return UM_INVALID_PASS;
    }
    return UM_SUCCESS;
}

UMResult JoinGroup(UserMng* _userMng, char* _name, char* _groupName)
{
    void* resUser;
    UserResult resIsMember;
    if (NULL == _userMng || NULL == _name || NULL == _groupName)
    {
        return UM_UNINITIALIZED_ERROR;
    }
    resUser = Find(_userMng, _name);
    if (NULL == resUser)
    {
        return UM_USER_NOT_EXIST;
    }
    if(!(IsUserLoggedIn(resUser)))  /*----ori's update----*/
    {
        return UM_NOT_ACTIVE_ERROR;
    }
    resIsMember = UserJoinGroup((User*)resUser, _groupName);
    if(USER_GROUP_DUPLICATE == resIsMember)
    {
        return UM_DUPLICATE;
    }
    return UM_SUCCESS;
}
/*.........................................................................*/
UMResult LeaveGroup(UserMng* _userMng, char* _name, char* _groupName)
{
    void* user;
    if (NULL == _userMng || NULL == _name || NULL == _groupName)
    {
        return UM_UNINITIALIZED_ERROR;
    } 
    if((user = Find(_userMng, _name)) == NULL)
    {
        return UM_USER_NOT_EXIST; 
    }
    if(!(IsUserLoggedIn(user)))
    {
        return UM_NOT_ACTIVE_ERROR;
    }
    if((UserLeaveGroup((User*)user, _groupName)) != USER_SUCCESS) 
    {
        return UM_GROUP_NOT_FOUND;
    }
    return UM_SUCCESS;
}
/*.........................................................................*/
UMResult LogOut(UserMng* _userMng, char* _name, List* _groupList)
{
    void* user;
    HashMap* groupsHash;
    if (NULL == _userMng || NULL == _name || NULL == _groupList)
    {
        return UM_UNINITIALIZED_ERROR;
    } 
    if((user = Find(_userMng, _name)) == NULL)
    {
        return UM_USER_NOT_EXIST; 
    }
    if(!(IsUserLoggedIn(user)))
    {
        return UM_NOT_ACTIVE_ERROR;
    }
    groupsHash = GetGroupMap(user);
    if(HashMap_ForEach(groupsHash, SaveGroupNamesAction, _groupList) != HashMap_Size(groupsHash))
    {
        return UM_LOGOUT_ERROR;
    }
    if(UserLogOut((User*)user) != USER_SUCCESS)
    {
        return UM_LOGOUT_ERROR;
    }
    return UM_SUCCESS;
}
/*********** inner assistance functions ***********/

static void* Find(UserMng* _userMng, char* _name)
{
    void* pValue = NULL;
    HashMap_Find(_userMng -> m_userMap, _name, &pValue);
    return (NULL != pValue) ? pValue : NULL;
}

static int LoadData(UserMng* _userMng)
{
    char name[MAX_SIZE_NAME];
    char password[MAX_SIZE_PASSWORD];
    FILE* pFile = fopen(FILE_NAME, "r");
    if (NULL == pFile)
    {
        return FILE_NOT_EXIST;
    }
    fscanf(pFile, "%s %s", name, password);
    while(!(feof(pFile)))
    {
        CreateAndInsert(_userMng, DEFAULT_ID, name, password, NULL);
        fscanf(pFile, "%s %s", name, password);
    }
    fclose(pFile);
    return OK;
}

static int SaveData(char* _name, char* _password)
{
    FILE* pFile = fopen(FILE_NAME, "a+");
    if (NULL == pFile)
    {
        return ERROR;
    }
    fprintf(pFile, "%s ", _name);
    fprintf(pFile, "%s\n", _password);
    fclose(pFile);
    return OK;
}

static int CreateAndInsert(UserMng* _userMng, int _userId, char* _name,
    char* _password, char** _valueUser)
{
    User* newUser;
    Map_Result resMapInsert;
    char* allocName;
    newUser = UserCreate(_userId, _name, _password);
    if (NULL == newUser)
    {
        return ALLOCATION_ERROR;
    }
    allocName = (char*)malloc(sizeof(char));
    if (NULL == allocName)
    {
        DestroyUser(&newUser);
        return ALLOCATION_ERROR;
    }
    strcpy(allocName, _name);
    resMapInsert = HashMap_Insert(_userMng -> m_userMap, allocName, newUser);
    if (MAP_SUCCESS != resMapInsert)
    {
        free(allocName);
        DestroyUser(&newUser);
        return ALLOCATION_ERROR;
    }
    if (NULL != _valueUser)
    {
        *_valueUser = allocName;
    }
    return OK;
}

static int IsDuplicate(UserMng* _userMng, char* _name)
{
    void* pValue = NULL;
    HashMap_Find(_userMng -> m_userMap, _name, &pValue);
    return (NULL == pValue) ? FALSE : TRUE;
}
/******* inner function for HashDestroy() *******/
static void UserRemove(void* _user)
{
    User* temp = (User*)_user;
    DestroyUser(&temp);
}
/***** inner functions for HashMap_Create() *****/
static size_t HashByAscii(void* _userName)
{
    char* Name = (char*)_userName;
    size_t i = 0, sumAscii = 0;
    while (Name[i] != '\0')
    {
        sumAscii += (i + 1) * Name[i];
        ++i;
    }
    return sumAscii;
}
static int CompareInt(void* _firstData, void* _secondData)
{
    return (*(int*)_firstData == *(int*)_secondData);
}
/********* assistance function for tests *********/
size_t GetUserMapSize(UserMng* _userMng)
{
    return HashMap_Size(_userMng -> m_userMap);
}

/*.........................................................................*/
static int SaveGroupNamesAction(const void* _groupName, void* _value, void* _context)
{
    List* groupList = (List*)_context;
    ListPushTail(groupList, (void*)_groupName);
    return 1;
}

