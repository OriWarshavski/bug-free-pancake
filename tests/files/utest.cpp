#include "mu_test.h"
#include "pointers.h"

typedef struct Person
{
	int m_id; /*Primary Key*/
	char m_name[128];
	int m_age;
}Person;

Person persons[5] = {{600, "Yarden", 30},{200, "Ori", 27},{300, "Shaul", 35},{400,"Miko", 1},{500, "Persi", 1}};

BEGIN_TEST(test_write_to_file)
    FILE* fp;
    char a = 'a';
	if((fp = fopen("person.txt", "w")) == NULL)
	{
		printf("File could not be opend\n");
	}
	fprintf(fp, "%d %s %d\n", persons[0].m_id, persons[0].m_name, persons[0].m_age);
    fprintf(fp, "the ascii of '%c' is: %d\n", a, a);	
    fclose(fp);
    ASSERT_EQUAL(0, 0);
END_TEST

BEGIN_TEST(test_reed_from_file)
	FILE* cfptr;
    Person emptyPersons[5];
	if((cfptr = fopen("person.txt", "r")) == NULL)
	{
		printf("File could not be opend\n");
	}
	else
	{
		printf("%-5s%-6s%s\n", "id", "name", "age");
		fscanf(cfptr, "%d %s %d", &emptyPersons[0].m_id, emptyPersons[0].m_name, &emptyPersons[0].m_age);
	}
	fclose(cfptr);
    ASSERT_EQUAL(emptyPersons[0].m_id, 600);
END_TEST

TEST_SUITE("pointes practice")
    TEST(test_write_to_file)
	TEST(test_reed_from_file)
END_SUITE
