#include "group.h"
#include <string.h>
#include <stdlib.h>
#define PORT 8070
#define IP_LEN 13
/*...................................................................*/
struct Group
{
    char m_groupName[30];
    int m_countUsers;
    char m_ip[IP_LEN];
    int m_port;
};
/*...................................................................*/
Group* GroupCreate(char* _name, char* _ip)
{
    Group* newGroup;
    if(_name == NULL)
    {
        return NULL;
    }
    if((newGroup = (Group*)malloc(sizeof(Group))) == NULL)
    {
        return NULL;
    }
    strcpy(newGroup -> m_groupName, _name);
    newGroup -> m_countUsers = 1;
    newGroup -> m_port = PORT;
    strcpy(newGroup -> m_ip, _ip);
    return newGroup;
}
/*...................................................................*/
char* GroupDestroy(Group** _group)
{
    char* saveIp;
    if(_group == NULL || *_group == NULL)
    {
        return NULL;
    }
    saveIp = (*_group) -> m_ip;
    free(*_group);
    *_group = NULL;
    return saveIp;
}
/*...................................................................*/
char* GetGroupName(Group* _group)
{
    if(_group == NULL)
    {
        return NULL;
    }
    return _group -> m_groupName;
}
/*...................................................................*/
char* GetGroupIp(Group* _group)
{
    if(_group == NULL)
    {
        return NULL;
    }
    return _group -> m_ip;
}
/*...................................................................*/
int GetGroupPort(Group* _group)
{
    if(_group == NULL)
    {
        return -1;
    }
    return _group -> m_port;
}
/*...................................................................*/
int* GetGroupCounter(Group* _group)
{
    if(_group == NULL)
    {
        return -1;
    }
    return &(_group -> m_countUsers);
}