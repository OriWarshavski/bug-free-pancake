#include "mu_test.h"
#include "pointers.h"

/*................................................................*/
BEGIN_TEST(test_single_linked_list)
    SingleLinkedList* list = create_single_linked();
    insert_to_head(list, 5);
    insert_to_head(list, 10);
    insert_to_head(list, 123);
    single_list_print(list);
    list_destroy(&list);
    ASSERT_EQUAL(0, 0);
END_TEST


TEST_SUITE("pointes practice")
	TEST(test_single_linked_list)

END_SUITE
