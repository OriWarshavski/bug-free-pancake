#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__
#include "limit.h"
/*...................................................................*/
typedef struct ClientDetails
{
    char m_userName[MAX_SIZE_NAME];
    char m_password[MAX_SIZE_PASSWORD];
}ClientDetails;
/*...................................................................*/
typedef struct GroupDetails
{
    char m_userName[MAX_SIZE_NAME];
    char m_groupName[MAX_GROUP_NAME];
	char m_ip[MAX_IP_LEN];
	char m_port[MAX_PORT_LEN];
	int m_status;
	char m_groupList[MAX_GROUP_LIST_BUFFER_SIZE];
}GroupDetails;
/*...................................................................*/
typedef enum MsgTag {
	REG_REQ = 1,
	REG_REPLY,
	LOG_REQ,
	LOG_REPLY,
	GROUP_CREATE_REQ,
	GROUP_CREATE_REPLY,
	GROUP_JOIN_REQ,
	GROUP_JOIN_REPLY,
	GROUP_LEAVE_REQ,
	GROUP_LEAVE_REPLY,
	PRINT_GROUPS_REQ,
	PRINT_GROUPS_REPLY,
	LOG_OUT_REQ,
	LOG_OUT_REPLY
}MsgTag;
/*...................................................................*/
typedef enum ReplyResult
{
	REPLY_SUCCESS = 1,
	REPLY_NAME_FAIL = -1,
	REPLY_PASS_FAIL = -2
}ReplyResult;
/*...................................................................*/
/**  
 * @brief returns the message tag.
 * @param[in] _msg - a buffer with the massage - must be initialized.
 * @return the message tag/error.
		   error -1 for wrong input.
 */
int GetMsgTag(char* _msg);
/*...................................................................*/
/*.........................REGESTRATION..............................*/
/*...................................................................*/
/**  
 * @brief packs log request - name and password.
 * @param[in] _user- pointer to struct of ClientDetails - must be initialized.
 * @param[in] _buffer - a buffer to put the packed massage in - must be initialized.
 * @return the total length of the pack/error.
		   error - -1 - for wrong input.
 */
int PackRegReq(ClientDetails* _user, char* _buffer);
/**  
 * @brief unpacks registration request.
 * @param[in] _clientMsg - a buffer with the message - must be initialized.
 * @param[in] _msgLen- the length of the message (output from PackRegReq) - must be larger than 3.
 * @return pointer to struct of ClientDetails.
		   error - NULL - for wrong input.
 */
ClientDetails UnpackRegReq(char* _clientMsg, int _msgLen);
/*...................................................................*/
/**  
 * @brief packs registration reply.
 * @param[in] _val- the reply from server to client - REPLY_SUCCESS/REPLY_FAIL.
 * @param[in] _buffer - a buffer to put the packed massage in - must be initialized.
 * @return the total length of the pack (always 3)/error.
		   error - -1 - for wrong input.
 */
int PackRegReply(int _val, char* _buffer);
/**  
 * @brief unpacks registration reply.
 * @param[in] _clientMsg - a buffer with the massage - must be initialized.
 * @param[in] _msgLen- the length of the message (output from PackRegReply) - must be 3.
 * @return the value of the reply - REPLY_SUCCESS/REPLY_FAIL
		   error - -1 for wring input.
 */
int UnpackRegReply(char* _clientMsg, int _msgLen);
/*...................................................................*/
/*.............................LOGIN.................................*/
/*...................................................................*/
/**  
 * @brief packs log request - name and password.
 * @param[in] _user- pointer to struct of ClientDetails - must be initialized.
 * @param[in] _buffer - a buffer to put the packed massage in - must be initialized.
 * @return the total length of the pack/error.
		   error - -1 - for wrong input.
 */
int PackLogReq(ClientDetails* _user, char* _buffer);
/**  
 * @brief unpacks log request.
 * @param[in] _clientMsg - a buffer with the message - must be initialized.
 * @param[in] _msgLen- the length of the message (output from PackRegReq) - must be larger than 3.
 * @return pointer to struct of ClientDetails.
		   error - NULL - for wrong input.
 */
ClientDetails UnpackLogReq(char* _buffer, int _msgLen);
/*...................................................................*/
/**  
 * @brief packs log reply.
 * @param[in] _val- the reply from server to client - REPLY_SUCCESS/REPLY_FAIL.
 * @param[in] _buffer - a buffer to put the packed massage in - must be initialized.
 * @return the total length of the pack (always 3)/error.
		   error - -1 - for wrong input.
 */
int PackLogReply(int _val, char* _buffer);
/**  
 * @brief unpacks log reply.
 * @param[in] _clientMsg - a buffer with the massage - must be initialized.
 * @param[in] _msgLen- the length of the message (output from PackRegReply) - must be 3.
 * @return the value of the reply - REPLY_SUCCESS/REPLY_FAIL
		   error - -1 for wring input.
 */
int UnpackLogReply(char* _clientMsg, int _msgLen);
/*...................................................................*/
/*.........................CREATE GROUP..............................*/
/*...................................................................*/
/**  
 * @brief packs group create request - user name and group name.
 * @param[in] _gruopD- pointer to struct of GroupDetails - must be initialized.
 * @param[in] _buffer - a buffer to put the packed massage in - must be initialized.
 * @return the total length of the pack/error.
		   error - -1 - for wrong input.
 */
int PackCreateGroupReq(GroupDetails* _gruopD, char* _buffer);
/**  
 * @brief unpacks create group request.
 * @param[in] _clientMsg - a buffer with the message - must be initialized.
 * @param[in] _msgLen- the length of the message (output from PackRegReq) - must be larger than 3.
 * @return pointer to struct of ClientDetails.
		   error - NULL - for wrong input.
 */
GroupDetails UnpackCreateGroupReq(char* _clientMsg, int _msgLen);
/*...................................................................*/
/**  
 * @brief packs CreateGroup reply.
 * @param[in] _groupD- need to be update with id, port and status.
 * @param[in] _buffer - a buffer to put the packed massage in - must be initialized.
 * @return the total length of the pack/error.
		   error - -1 - for wrong input.
 */
int PackCreateGroupReply(GroupDetails* _groupD, char* _buffer);
/**  
 * @brief unpacks create group reply.
 * @param[in] _clientMsg - a buffer with the massage - must be initialized.
 * @param[in] _msgLen- the length of the message (output from PackRegReply) - must be 3.
 * @return the value of the reply - REPLY_SUCCESS/REPLY_FAIL
		   error - -1 for wring input.
 */
GroupDetails UnpackCreateGroupReply(char* _clientMsg, int _msgLen);
/*...................................................................*/
/*.........................JOIN GROUP................................*/
/*...................................................................*/
/**  
 * same as create group request - members in GroupDetails to update - 
 * ip and port
 */
int PackJoinGroupReq(GroupDetails* _gruopD, char* _buffer);
GroupDetails UnpackJoinGroupReq(char* _clientMsg, int _msgLen);
/*...................................................................*/
/**  
 * same as create group reply - relevat members in GroupDetails - 
 * ip and port
 */
int PackJoinGroupReply(GroupDetails* _groupD, char* _buffer);
GroupDetails UnpackJoinGroupReply(char* _clientMsg, int _msgLen);
/*...................................................................*/
/*...........................LEAVE GROUP.............................*/
/*...................................................................*/
/**  
 * same as create&join group request.
 */
int PackLeaveGroupReq(GroupDetails* _groupD, char* _buffer);
GroupDetails UnpackLeaveGroupReq(char* _clientMsg, int _msgLen);
/*...................................................................*/
/**  
 * same as create group reply.
 */
int PackLeaveReply(int _val, char* _buffer);
GroupDetails UnpackLeaveReply(char* _clientMsg, int _msgLen);
/*...................................................................*/
/*.......................,.PRINT GROUP LIST..........................*/
/*...................................................................*/
/**  
 * @brief packs PrintGroup reply. 
 * @param[in] _groupD- need to be update with groupList and status members.
 * @param[in] _buffer - a buffer to put the packed massage in - must be initialized.
 * @return the total length of the pack/error.
		   error - -1 - for wrong input.
 */
int PackPrintGroupsReply(GroupDetails* _groupD, char* _buffer);
/**  
 * @brief unpacks create group reply.
 * @param[in] _serverMsg - a buffer with the massage - must be initialized.
 * @param[in] _msgLen- the length of the message (output from PackPrintGroupsReply).
 * @return GroupDetails struct with groupList and status members.
		   error - -1 for wring input.
 */
GroupDetails UnpackPrintGroupsReply(char* _serverMsg, int _msgLen);
/*...................................................................*/
/*............................LOGOUT.................................*/
/*...................................................................*/
/**  
 * same as create group request - members in GroupDetails to update - 
 * userName.
 */
int PackLogOutReq(GroupDetails* _gruopD, char* _buffer);
GroupDetails UnpackLogOutReq(char* _clientMsg, int _msgLen);
/*.....................................................................*/
/**  
 * same as create group reply.
 */
int PackLogOutReply(int _val, char* _buffer);
int UnpackLogOutReply(char* _serverMsg, int _msgLen);

#endif /*__PROTOCOL_H__*/

