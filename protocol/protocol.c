#include "protocol.h"
#include "limit.h"
#include <string.h>
#include <stdio.h>
/*...................................................................*/
static int BuildNamePassPack(ClientDetails* _user, char* _buffer);
static ClientDetails BuildClient(char* _buffer); 
static int BuildNameGroupPack(GroupDetails* _gruopD, char* _buffer);
static GroupDetails BuildGroup(char* _buffer);
/*...................................................................*/
int GetMsgTag(char* _buffer)
{
    if(_buffer == NULL)
    {
        return -1;
    }
    return _buffer[0];
}
/*...................................................................*/
int PackRegReq(ClientDetails* _user, char* _buffer)
{
    if(_user == NULL || _buffer == NULL)
    {
        return -1;
    }
    _buffer[0] = REG_REQ;
    return BuildNamePassPack( _user, _buffer);
}
/*...................................................................*/
ClientDetails UnpackRegReq(char* _clientMsg, int _msgLen)
{
    if(_clientMsg == NULL || _msgLen < 3)
    {
        return;
    }
    return BuildClient(_clientMsg);
}
/*...................................................................*/
int PackRegReply(int _val, char* _buffer)
{
    if(_buffer == NULL || (_val != REPLY_SUCCESS && _val != REPLY_NAME_FAIL))
    {
        return -1;
    }
    _buffer[0] = REG_REPLY;
    _buffer[1] = 2;
    _buffer[2] = _val;
    return 3;
}
/*...................................................................*/
int UnpackRegReply(char* _buffer, int _msgLen)
{
    if(_buffer == NULL || _msgLen != 3)
    {
        return -1;
    }
    return _buffer[2];
}
/*...................................................................*/
int PackLogReq(ClientDetails* _user, char* _buffer)
{
    if(_user == NULL || _buffer == NULL)
    {
        return -1;
    }
    _buffer[0] = LOG_REQ;
    return BuildNamePassPack( _user, _buffer);
}
/*...................................................................*/
ClientDetails UnpackLogReq(char* _buffer, int _msgLen)
{
    if(_buffer == NULL || _msgLen < 3)
    {
        return;
    }
    return BuildClient(_buffer);
}
/*...................................................................*/
int PackLogReply(int _val, char* _buffer)
{
    if(_buffer == NULL || (_val != REPLY_SUCCESS && _val != REPLY_NAME_FAIL && _val != REPLY_PASS_FAIL))
    {
        return -1;
    }
    _buffer[0] = LOG_REPLY;
    _buffer[1] = 2;
    _buffer[2] = _val;
    return 3;
}
/*...................................................................*/
int UnpackLogReply(char* _clientMsg, int _msgLen)
{
    if(_clientMsg == NULL || _msgLen != 3)
    {
        return -1;
    }
    return _clientMsg[2];
}
/*...................................................................*/
int PackCreateGroupReq(GroupDetails* _gruopD, char* _buffer)
{
    if(_gruopD == NULL || _buffer == NULL)
    {
        return -1;
    }
    _buffer[0] = GROUP_CREATE_REQ;
    return BuildNameGroupPack(_gruopD, _buffer);
}
/*...................................................................*/
GroupDetails UnpackCreateGroupReq(char* _clientMsg, int _msgLen)
{
    if(_clientMsg == NULL || _msgLen < 3)
    {
        return;
    }
    return BuildGroup(_clientMsg);
}
/*...................................................................*/
int PackCreateGroupReply(GroupDetails* _groupD, char* _buffer)
{
    int ipLen, totalLen, portLen;
    if(_buffer == NULL)
    {
        return -1;
    }
    ipLen = strlen(_groupD -> m_ip);
    portLen = strlen(_groupD -> m_port);
    totalLen = ipLen + portLen + 5;
    _buffer[0] = GROUP_CREATE_REPLY;
    _buffer[1] = totalLen - 2;
    _buffer[2] = ipLen;
    strcpy(&_buffer[3], _groupD -> m_ip);
    _buffer[ipLen + 3] = portLen;
    strcpy(&_buffer[ipLen + 4], _groupD -> m_port);
    _buffer[ipLen + portLen + 4] = _groupD -> m_status;
    return totalLen;
}
/*...................................................................*/
GroupDetails UnpackCreateGroupReply(char* _clientMsg, int _msgLen)
{
    GroupDetails groupD;
    int ipLen, portLen;
    if(_clientMsg == NULL || _msgLen < 3)
    {
        return;
    }
    ipLen = _clientMsg[2];
    portLen = _clientMsg[ipLen + 3];
    strncpy(groupD.m_ip, &(_clientMsg[3]), ipLen);
    groupD.m_ip[ipLen] = '\0';
    strncpy(groupD.m_port, &(_clientMsg[ipLen + 4]), portLen);
    groupD.m_port[portLen] = '\0';
    groupD.m_status = _clientMsg[ipLen + portLen + 4];
    return groupD;
}
/*...................................................................*/
int PackJoinGroupReq(GroupDetails* _gruopD, char* _buffer)
{
    if(_gruopD == NULL || _buffer == NULL)
    {
        return -1;
    }
    _buffer[0] = GROUP_JOIN_REQ;
    return BuildNameGroupPack(_gruopD, _buffer);
}
/*...................................................................*/
GroupDetails UnpackJoinGroupReq(char* _clientMsg, int _msgLen)
{
    if(_clientMsg == NULL || _msgLen < 3)
    {
        return;
    }
    return BuildGroup(_clientMsg);
}
/*...................................................................*/
int PackJoinGroupReply(GroupDetails* _groupD, char* _buffer)
{
    int ipLen, totalLen, portLen;
    if(_buffer == NULL)
    {
        return -1;
    }
    ipLen = strlen(_groupD -> m_ip);
    portLen = strlen(_groupD -> m_port);
    totalLen = ipLen + portLen + 5;
    _buffer[0] = GROUP_JOIN_REPLY;
    _buffer[1] = totalLen - 2;
    _buffer[2] = ipLen;
    strcpy(&_buffer[3], _groupD -> m_ip);
    _buffer[ipLen + 3] = portLen;
    strcpy(&_buffer[ipLen + 4], _groupD -> m_port);
    _buffer[ipLen + portLen + 4] = _groupD -> m_status;
    return totalLen;
}
/*...................................................................*/
GroupDetails UnpackJoinGroupReply(char* _clientMsg, int _msgLen)
{
    GroupDetails groupD;
    int ipLen, portLen;
    if(_clientMsg == NULL || _msgLen < 3)
    {
        return;
    }
    ipLen = _clientMsg[2];
    portLen = _clientMsg[ipLen + 3];
    strncpy(groupD.m_ip, &(_clientMsg[3]), ipLen);
    groupD.m_ip[ipLen] = '\0';
    strncpy(groupD.m_port, &(_clientMsg[ipLen + 4]), portLen);
    groupD.m_port[portLen] = '\0';
    groupD.m_status = _clientMsg[ipLen + portLen + 4];
    return groupD;
}
/*...................................................................*/
int PackLeaveGroupReq(GroupDetails* _groupD, char* _buffer)
{
    if(_buffer == NULL)
    {
        return -1;
    }
    _buffer[0] = GROUP_LEAVE_REQ;
    return BuildNameGroupPack(_groupD, _buffer);
}
/*...................................................................*/
GroupDetails UnpackLeaveGroupReq(char* _clientMsg, int _msgLen)
{
    if(_clientMsg == NULL || _msgLen < 3)
    {
        return;
    }
    return BuildGroup(_clientMsg);
}
/*...................................................................*/
int PackLeaveReply(int _val, char* _buffer)
{
    if(_buffer == NULL)
    {
        return -1;
    }
    _buffer[0] = GROUP_LEAVE_REPLY;
    _buffer[1] = 2;
    _buffer[2] = _val;
    return 3;
}
/*...................................................................*/
GroupDetails UnpackLeaveReply(char* _clientMsg, int _msgLen)
{
    GroupDetails groupD;
    if(_clientMsg == NULL || _msgLen != 3)
    {
        return;
    }
    groupD.m_status = _clientMsg[2];
    return groupD;
}
/*...................................................................*/
int PackPrintGroupsReply(GroupDetails* _groupD, char* _buffer)
{
    int totalLen, listLen;
    if(_buffer == NULL)
    {
        return -1;
    }
    listLen = strlen(_groupD -> m_groupList);
    totalLen = listLen + 4;
    _buffer[0] = PRINT_GROUPS_REPLY;
    _buffer[1] = totalLen - 2;
    _buffer[2] = listLen;
    strcpy(&_buffer[3], _groupD -> m_groupList);
    _buffer[listLen + 3] = _groupD -> m_status;
    return totalLen;
}
/*...................................................................*/
GroupDetails UnpackPrintGroupsReply(char* _serverMsg, int _msgLen)
{
    GroupDetails groupD;
    int listLen;
    if(_serverMsg == NULL || _msgLen < 3)
    {
        return;
    }
    listLen = _serverMsg[2];
    strncpy(groupD.m_groupList, &(_serverMsg[3]), listLen);
    groupD.m_groupList[listLen] = '\0';
    groupD.m_status = _serverMsg[listLen + 3];
    return groupD;
}
/*...................................................................*/
int PackLogOutReq(GroupDetails* _gruopD, char* _buffer)
{
    int totalLen, userLen;
    if(_gruopD == NULL || _buffer == NULL)
    {
        return -1;
    }
    _buffer[0] = LOG_OUT_REQ;
    userLen = strlen(_gruopD -> m_userName);
    totalLen = userLen + 3;
    _buffer[1] = totalLen - 2;
    _buffer[2] = userLen;
    strcpy(&_buffer[3], _gruopD -> m_userName);
    return totalLen;
}
/*...................................................................*/
GroupDetails UnpackLogOutReq(char* _clientMsg, int _msgLen)
{
    int userLen;
    GroupDetails groupD;
    if(_clientMsg == NULL || _msgLen < 3)
    {
        return;
    }
    userLen = _clientMsg[2];
    strncpy(groupD.m_userName, &(_clientMsg[3]), userLen);
    groupD.m_userName[userLen] = '\0';
    return groupD;
}
/*...................................................................*/
int PackLogOutReply(int _val, char* _buffer)
{
    if(_buffer == NULL)
    {
        return -1;
    }
    _buffer[0] = LOG_OUT_REPLY;
    _buffer[1] = 2;
    _buffer[2] = _val;
    return 3;
}
/*...................................................................*/
int UnpackLogOutReply(char* _serverMsg, int _msgLen)
{
    if(_serverMsg == NULL || _msgLen < 3)
    {
        return;
    }
    return _serverMsg[2];
}
/*...................................................................*/
/*......................ASSISTANCE FUNCTIONS.........................*/
/*...................................................................*/
static int BuildNamePassPack(ClientDetails* _user, char* _buffer)
{
    int totalLen, nameLen, passLen;
    nameLen = strlen(_user -> m_userName);
    passLen = strlen(_user -> m_password);
    totalLen = nameLen + passLen + 4;
    _buffer[1] = totalLen - 2;
    _buffer[2] = nameLen;
    strcpy(&_buffer[3], _user -> m_userName);
    _buffer[nameLen + 3] = passLen;
    strcpy(&_buffer[nameLen + 4], _user -> m_password);
    return totalLen;
}
/*...................................................................*/
static ClientDetails BuildClient(char* _buffer)
{
    int nameLen, passLen;
    ClientDetails client;
    nameLen = _buffer[2];
    passLen = _buffer[nameLen + 3];
    strncpy(client.m_userName, &(_buffer[3]), nameLen);
    client.m_userName[nameLen] = '\0';
    strncpy(client.m_password, &(_buffer[nameLen + 4]), passLen);
    client.m_password[passLen] = '\0';
    return client;
}
/*...................................................................*/
static int BuildNameGroupPack(GroupDetails* _gruopD, char* _buffer)
{
    int totalLen, userLen, groupLen;
    userLen = strlen(_gruopD -> m_userName);
    groupLen = strlen(_gruopD -> m_groupName);
    totalLen = userLen + groupLen + 4;
    _buffer[1] = totalLen - 2;
    _buffer[2] = userLen;
    strcpy(&_buffer[3], _gruopD -> m_userName);
    _buffer[userLen + 3] = groupLen;
    strcpy(&_buffer[userLen + 4], _gruopD -> m_groupName);
    return totalLen;
}
/*...................................................................*/
static GroupDetails BuildGroup(char* _buffer)
{
    int userLen, groupLen;
    GroupDetails groupD;
    userLen = _buffer[2];
    groupLen = _buffer[userLen + 3];
    strncpy(groupD.m_userName, &(_buffer[3]), userLen);
    groupD.m_userName[userLen] = '\0';
    strncpy(groupD.m_groupName, &(_buffer[userLen + 4]), groupLen);
    groupD.m_groupName[groupLen] = '\0';
    return groupD;
}
