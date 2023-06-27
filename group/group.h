#ifndef __GROUP_H__
#define __GROUP_H__

typedef struct Group Group;

typedef enum GroupResult
{
    GROUP_SUCCESS,
    GROUP_UNINITIALIZED
}GroupResult;

/**  
 * @brief creates new group.
 * @param[in] _name - the new of the group - must be initialized.
 * @param[in] _ip - the ip for the new group - must be initialized.
 * @return the message tag/error.
		   error NULL for wrong input.
 */
Group* GroupCreate(char* _name, char* _ip);

/**  
 * @brief destroys new group.
 * @param[in] _group - pointer to group's address - must be initialized.
 * @return the group's ip!/error
		   error NULL for wrong input (uninitialized).
 */
char* GroupDestroy(Group** _group);

/**  
 * @brief returns the group's name.
 * @param[in] _group - pointer to group's address - must be initialized.
 * @return the group's name.
		   error NULL for wrong input (uninitialized).
 */
char* GetGroupName(Group* _group);

/**  
 * @brief returns the group's IP.
 * @param[in] _group - pointer to group's address - must be initialized.
 * @return the group's name.
		   error NULL for wrong input (uninitialized).
 */
char* GetGroupIp(Group* _group);

/**  
 * @brief returns the group's PORT.
 * @param[in] _group - pointer to group's address - must be initialized.
 * @return the group's PORT.
		   error -1 for wrong input (uninitialized).
 */
int GetGroupPort(Group* _group);

/**  
 * @brief returns the address group's  counter of users.
 * @param[in] _group - pointer to group's address - must be initialized.
 * @return the group's PORT.
		   error -1 for wrong input (uninitialized).
 */
int* GetGroupCounter(Group* _group);
#endif /*__GROUP_H__*/
