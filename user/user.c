#include "user.h"
#include "limit.h"
#include "hashMap.h"
#include <stdlib.h>     /*malloc*/
#include <string.h>     /*strcpy*/
/*...........................................................*/
static size_t HashByAscii(void* _groupName);
static int CompareInt(void* _firstData, void* _secondData);
static int SaveGroupNamesAction(const void* _key, void* _value, void* _context);
/*...........................................................*/
struct User
{
    int m_userId;
    int m_active;
    char m_name[30];
    char m_password[20];
    HashMap* m_groupsMap;
};
/*...........................................................*/
User* UserCreate(int _userId, char* _name, char* _password)
{
    User* newUser;
    if(_userId <= 0 || _name == NULL || _password == NULL)
    {
        return NULL;
    }
    if((newUser = (User*)malloc(sizeof(User))) == NULL)
    {
        return NULL;
    }
    newUser -> m_groupsMap = NULL;
    newUser -> m_userId = _userId;
    newUser -> m_active = 0;
    strcpy(newUser -> m_name, _name);
    strcpy(newUser -> m_password, _password);
    return newUser;
}
/*...........................................................*/
void DestroyUser(User** _user)
{
    if(_user == NULL || *_user == NULL)
    {
        return;
    }
    if((*_user) -> m_groupsMap != NULL)
    {
        HashMap_Destroy(&((*_user) -> m_groupsMap), NULL, NULL);
    }
    free(*_user);
    *_user = NULL;
}
/*...........................................................*/
UserResult UserLogIn(User* _user, char* _password)
{
    if(_user == NULL|| _password == NULL)
    {
        return USER_NOT_INITIALIZED;
    }
    if(0 != strcmp(_user -> m_password, _password))
    {
        return USER_WRONG_PASS;
    }
    _user -> m_active = 1;
    return USER_SUCCESS;
}
/*...........................................................*/
UserResult UserJoinGroup(User* _user, char* _groupName)
{
    if(_user == NULL|| _groupName == NULL)
    {
        return USER_NOT_INITIALIZED;
    }
    if(_user -> m_groupsMap == NULL)
    {
        if((_user -> m_groupsMap = HashMap_Create(USER_GROUPS_NUM, HashByAscii, CompareInt)) == NULL)
        {
            return USER_ALLOCATION_FAIL;
        }
    }
    if((HashMap_Insert(_user -> m_groupsMap, _groupName, NULL)) != MAP_SUCCESS)
    {
        return USER_GROUP_DUPLICATE;
    }
    return USER_SUCCESS;
}
/*...........................................................*/
UserResult UserLeaveGroup(User* _user, char* _groupName)
{
    void* key, *val;
    if(_user == NULL|| _groupName == NULL)
    {
        return USER_NOT_INITIALIZED;
    }
    if(HashMap_Remove(_user -> m_groupsMap, _groupName, &key, &val) != MAP_SUCCESS)
    {
        return USER_GROUP_NOT_FOUND;
    }
    return USER_SUCCESS;
}
/*...........................................................*/
UserResult UserLogOut(User* _user)
{
    if(_user == NULL)
    {
        return USER_NOT_INITIALIZED;
    }
    HashMap_Destroy(&(_user -> m_groupsMap), NULL, NULL);
    _user -> m_groupsMap = NULL;
    _user -> m_active = 0;
    return USER_SUCCESS;
}
/*...........................................................*/
int IsUserLoggedIn(User* _user)
{
    if(_user == NULL)
    {
        return -1;
    }
    return _user -> m_active;
}
/*...........................................................*/
HashMap* GetGroupMap(User* _user)
{
    if(_user == NULL)
    {
        return NULL;
    }
    return _user -> m_groupsMap;
}
/*...........................................................*/
/*.....................TEST FUNCTIONS........................*/
/*...........................................................*/
int GetUserId(User* _user)
{
    if(_user == NULL)
    {
        return -1;
    }
    return _user -> m_userId;
}
/*...........................................................*/
char* GetName(User* _user)
{
    if(_user == NULL)
    {
        return NULL;
    }
    return _user -> m_name;
}
/*...........................................................*/
char* GetPass(User* _user)
{
    if(_user == NULL)
    {
        return NULL;
    }
    return _user -> m_password;
}

/*...........................................................*/
/*....................ASSISTANCE FUNCTIONS...................*/
/*...........................................................*/
static size_t HashByAscii(void* _groupName)
{
    char* Name = (char*)_groupName;
    size_t i = 0, sumAscii = 0;
    while (Name[i] != '\0')
    {
        sumAscii += (i + 1) * Name[i];
        ++i;
    }
    return sumAscii;
}
/*...........................................................*/
static int CompareInt(void* _firstData, void* _secondData)
{
    return (*(int*)_firstData == *(int*)_secondData);
}
/*...........................................................*/
static int SaveGroupNamesAction(const void* _key, void* _value, void* _context)
{
    char* list = (char*)_context;
    char addRow[1] = "\n";
    strcat(list, (char*)_key);
    strcat(list, addRow);
    return 1;
}