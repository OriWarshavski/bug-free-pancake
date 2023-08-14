using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using static System.Console;

namespace Phonebook
{
    class Test
    {
        public static void Main()
        {
            TestPrintBook();
            TestGetDetailsById();
            TestGetDetailsByIdIndex();
            TestGetDetailsByName();
            TestHowManyHasPhonePrefix();
            TestSearchContact();
        }

        static void TestPrintBook()
        {
            Phonebook book = new Phonebook();
            List<string> phones1 = new List<string>() { "054-454986", "054-898195" };
            List<string> phones2 = new List<string>() { "052-054986", "09-898195" };

            WriteLine($"Empty contacts book:\n\n{book}");

            book.AddNewContact(316493931, "Ori Shriqui", "Tel Aviv", phones1);
            book.AddNewContact(203763024, "Yarden Shriqui", "Tel Aviv", phones2);
            book.AddNewContact(1234, "Shaul haya", "Beer Sheva", phones2);

            WriteLine($"Full contacts book:\n\n{book}");
            WriteLine("TestPrintBook...................PASS");

        }

        static void TestGetDetailsById()
        {
            Phonebook book = new Phonebook();
            List<string> phones1 = new List<string>() { "054-454986", "054-898195" };
            List<string> phones2 = new List<string>() { "052-054986", "09-898195" };

            book.AddNewContact(316493931, "Ori Shriqui", "Tel Aviv", phones1);
            book.AddNewContact(203763024, "Yarden Shriqui", "Tel Aviv", phones2);

            ContactDetails contact1 = book.GetContactDetails(316493931);
            ContactDetails contact2 = book.GetContactDetails(316);

            if (contact1.FullName == "Ori Shriqui" && contact1.Phones[0] == "054-454986" && contact1.Phones[1] == "054-898195"
                && contact2 == null)
            {
                WriteLine("TestGetDetailsById...................PASS");
            }
            else
            {
                WriteLine("TestGetDetailsById...................FAIL");
            }
        }

        static void TestGetDetailsByIdIndex()
        {
            Phonebook book = new Phonebook();
            List<string> phones1 = new List<string>() { "054-454986", "054-898195" };
            List<string> phones2 = new List<string>() { "052-054986", "09-898195" };

            book.AddNewContact(316493931, "Ori Shriqui", "Tel Aviv", phones1);
            book.AddNewContact(203763024, "Yarden Shriqui", "Tel Aviv", phones2);

            if (book[316493931].FullName == "Ori Shriqui" && book[316493931].City == "Tel Aviv"
                && book[203763024].FullName == "Yarden Shriqui"
                && book[123] == null)
            {
                WriteLine("TestGetDetailsByIdIndex...................PASS");
            }
            else
            {
                WriteLine("TestGetDetailsByIdIndex...................FAIL");
            }
        }

        static void TestGetDetailsByName()
        {
            Phonebook book = new Phonebook();
            List<string> phones1 = new List<string>() { "054-454986", "054-898195" };
            List<string> phones2 = new List<string>() { "052-054986", "09-898195" };

            book.AddNewContact(316493931, "Ori Shriqui", "Tel Aviv", phones1);
            book.AddNewContact(203763024, "Yarden Shriqui", "Tel Aviv", phones2);
            book.AddNewContact(058745632, "Yarden Shriqui", "Beer Sheva", phones1);

            IEnumerable<ContactDetails> list = book.GetContactDetails("Ori Shriqui");
            IEnumerable<ContactDetails> list2 = book.GetContactDetails("Yarden Shriqui");


            foreach (ContactDetails cd in list2)
            {
                Console.WriteLine(cd);
            }


            //if (list.Count() == 1 && list. == "Ori Shriqui" && list[0].ID == 316493931
            //    && list[0].Phones[0] == "054-454986"
            //    && list2.Count() == 2 && list2[0].ID == 203763024 && list2[1].ID == 058745632
            //    && list2[0].Phones[0] == "052-054986" && list2[1].Phones[1] == "054-898195")
            //{
            //    WriteLine("TestGetDetailsByName...................PASS");
            //}
            //else
            //{
            //    WriteLine("TestGetDetailsByName...................FAIL");
            //}
        }

        static void TestHowManyHasPhonePrefix()
        {
            Phonebook book = new Phonebook();
            List<string> phones1 = new List<string>() { "054-454986", "054-898195" };
            List<string> phones2 = new List<string>() { "052-054986", "09-898195" };

            book.AddNewContact(316493931, "Ori Shriqui", "Tel Aviv", phones1);
            book.AddNewContact(203763024, "Yarden Shriqui", "Tel Aviv", phones2);
            book.AddNewContact(058745632, "Yarden Shriqui", "Beer Sheva", phones1);

            int result = book.HowManyHasPhonePrefix("054");

            if (result == 2 && book.HowManyHasPhonePrefix("052") == 1 && book.HowManyHasPhonePrefix("050") == 0)
            {
                WriteLine("TestHowManyHasPhonePrefix...................PASS");
            }
            else
            {
                WriteLine("TestHowManyHasPhonePrefix...................FAIL");
            }
        }

        static void TestSearchContact()
        {
            Phonebook book = new Phonebook();
            List<string> phones1 = new List<string>() { "054-454986", "054-898195" };
            List<string> phones2 = new List<string>() { "052-054986", "09-898195" };

            book.AddNewContact(316493931, "Ori Shriqui", "Tel Aviv", phones1);
            book.AddNewContact(203763024, "Yarden shriqui", "Tel Aviv", phones2);
            book.AddNewContact(058745632, "Padden Shre", "Beer Sheva", phones1);

            List<ContactDetails> result = book.SearchContacts("sh");
            List<ContactDetails> result2 = book.SearchContacts("Or");
            List<ContactDetails> result3 = book.SearchContacts("ori shriqui");

            //WriteLine(string.Join("\n", result));

            if (result.Count == 3 && result[0].ID == 316493931 && result[1].ID == 203763024 && result[2].City == "Beer Sheva"
                && result2.Count == 1 && result2[0].ID == 316493931 && book.SearchContacts("XX").Count == 0
                && book.SearchContacts("den").Count == 2
                && result3.Count == 1 && result3[0].ID == 316493931)
            {
                WriteLine("TestSearchContact...................PASS");
            }
            else
            {
                WriteLine("TestSearchContact...................FAIL");
            }
        }
    }
}
