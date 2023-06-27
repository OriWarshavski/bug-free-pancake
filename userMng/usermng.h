#ifndef __USER_MANANGER_H__
#define __USER_MANANGER_H__
#include "listG.h"  

typedef enum UMResult {
    UM_SUCCESS,
    UM_DUPLICATE,
    UM_UNINITIALIZED_ERROR,
    UM_ALLOCATION_ERROR,
    UM_SAVE_FILE_ERROR,
    UM_USER_NOT_EXIST,
    UM_INVALID_PASS,
    UM_GROUP_NOT_FOUND,  
    UM_ACTIVE_ERROR,        /*----ori's update----*/ 
    UM_NOT_ACTIVE_ERROR,      
    UM_LOGOUT_ERROR
} UMResult;

typedef struct UserMng UserMng;

/*
description:	create a new UserMng.
arguments:		none.
return value:	handling to the new UserMng.
errors:			NULL:   -if malloc failed.
                        -if HashMap_Create() failed. */
UserMng* CreateUserMng();

/*
description:	Destroy the UserMng and all of it's members.
arguments:		_userMng: pointer to pointer to the UserMng.
return value:	none.
errors:			none. */
void DestroyUserMng(UserMng** _userMng);

/*
description:	add a new user to the hashmap struct.
arguments:		_userMng: pointer to the UserMng.
                _userId: the socket of the user.
                _name: name of the user.
                _password: password of the user.
return value:	UM_SUCCESS: if user added successfully to the hasmap.
errors:			UM_UNINITIALIZED_ERROR: - if _userMng is invalid.
                                        - if _name is invalid.
                                        - if _password is invalid.
                UM_DUPLICATE:           - if _name is already exist.
                UM_ALLOCATION_ERROR:    - if UserCreate() failed.
                                        - if HashMap_Insert() failed. */
UMResult AddUser(UserMng* _userMng, int _userId, char* _name, char* _password);

/*
description:    change status of activity to active if LogIn() successed.
arguments:		_userMng: pointer to the UserMng.
                _name: name of the user.
                _password: password of the user.
return value:	UM_SUCCESS: if user logged in successfully.
errors:			UM_UNINITIALIZED_ERROR: - if _userMng is invalid.
                                        - if _name is invalid.
                                        - if _password is invalid.
                UM_USER_NOT_EXIST:      - if _name doesn't exist.
                UM_INVALID_PASS:        - if _name is exist but the
                                            password is incorrect.*/
UMResult LogIn(UserMng* _userMng, char* _name, char* _password);


UMResult JoinGroup(UserMng* _userMng, char* _name, char* _groupName);

/**  
 * @brief deletes group from user's list.
 * @param[in] _userMng- pointer to userMng address - must be initialized.
 * @param[in] _name- userMng name - must be initialized.
 * @param[in] _groupName- group name - must be initialized.
 * @return USER_SUCCESS/error - UM_UNINITIALIZED_ERROR/UM_USER_NOT_EXIST/UM_GROUP_NOT_FOUND.
 */
UMResult LeaveGroup(UserMng* _userMng, char* _name, char* _groupName);

/**  
 * @brief change user status to "logged out".
 * @param[in] _userMng- pointer to userMng address - must be initialized.
 * @param[in] _name- userMng name - must be initialized.
 * @param[in] _groupList- pounter to empty list to put in the user's group names.
 * @return USER_SUCCESS/error - UM_UNINITIALIZED_ERROR/UM_USER_NOT_EXIST/UM_LOGOUT_ERROR.
 */
UMResult LogOut(UserMng* _userMng, char* _name, List* _groupList);
#endif /* __USER_MANANGER_H__ */


