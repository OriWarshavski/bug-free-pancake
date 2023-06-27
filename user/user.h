#ifndef __USER_H__
#define __USER_H__
#include "hashMap.h"

typedef struct User User;

typedef enum UserResult {
	USER_SUCCESS = 0,
	USER_NOT_INITIALIZED,
   USER_ALLOCATION_FAIL,
   USER_GROUP_DUPLICATE,
   USER_GROUP_NOT_FOUND,
   USER_WRONG_PASS
}UserResult;

/**  
 * @brief creates user.
 * @param[in] _clientId- client number - send it to SendMessage function to respond - must be possitive.
 * @param[in] _name - user name - must be initiaized.
 * @param[in] _password - user password  - must be initiaized.
 * @return pointer to the created user/NULL for incorrect input.
 */
User* UserCreate(int _userId, char* _name, char* _password);

/**  
 * @brief destroys user.
 * @param[in] _user- pointer to user address - must be initialized.
 * @return none.
 */
void DestroyUser(User** _user);

/**  
 * @brief change user mode to "login".
 * @param[in] _user- pointer to user- must be initialized.
* @param[in] _password- pointer to user- must be initialized and correct.
 * @return USER_SUCCESS/error - USER_NOT_INITIALIZED/USER_WRONG_PASS.
 */
UserResult UserLogIn(User* _user, char* _password);

/**  
 * @brief add group to user's list of groups.
 * @param[in] _user- pointer to user address - must be initialized.
 * @param[in] _groupName- group name - must be initialized.
 * @return USER_SUCCESS/error - USER_NOT_INITIALIZED/USER_GROUP_DUPLICATE.
 */
UserResult UserJoinGroup(User* _user, char* _groupName);

/**  
 * @brief deletes group from user's list.
 * @param[in] _user- pointer to user address - must be initialized.
 * @param[in] _groupName- group name - must be initialized.
 * @return USER_SUCCESS/error - USER_NOT_INITIALIZED/USER_GROUP_NOT_FOUND.
 */
UserResult UserLeaveGroup(User* _user, char* _groupName);

/**  
 * @brief change user mode to "logout".
 * @param[in] _user- pointer to user- must be initialized.
 * @return USER_SUCCESS/error - USER_NOT_INITIALIZED/USER_GROUP_NOT_FOUND.
 */
UserResult UserLogOut(User* _user);

/**  
 * @brief checks if user is an active user..
 * @param[in] _user- pointer to user - must be initialized.
 * @return 1 - user is active (logged in), 0 - user not active(logged out)/error .
    error - -1 -_user uninitialized;
 */
int IsUserLoggedIn(User* _user);

/**  
 * @brief returns the map of the user's groups.
 * @param[in] _user- pointer to user - must be initialized.
 * @return user ID/error.
    error - null for USER_NOT_INITIALIZED.
 */
HashMap* GetGroupMap(User* _user);


#endif /*__USER_H__*/