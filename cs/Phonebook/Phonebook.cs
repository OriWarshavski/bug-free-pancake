using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using static System.Console;

namespace Phonebook
{
    public interface IPhonebook
    {
        ContactDetails GetContactDetails(int id);
        IEnumerable<ContactDetails> GetContactDetails(string fullName);
        int HowManyHasPhonePrefix(string prefixPhone);
        List<ContactDetails> SearchContacts(string subString);
    }

    class Phonebook : IPhonebook
    {
        private List<ContactDetails> Book = new List<ContactDetails>();

        public void AddNewContact(int id, string fullName, string city, List<string> phones)
        {
            ContactDetails newContact = new ContactDetails(id, fullName, city, phones);
            Book.Add(newContact);
        }

        //indexer
        public ContactDetails this[int id]
        {
            get
            {
                return GetContactDetails(id);
            }
        }

        public ContactDetails GetContactDetails(int id)
        {
            var enu = Book.GetEnumerator();
            List<ContactDetails> list = new List<ContactDetails>();

            while (enu.MoveNext())
            {
                if ((enu.Current).ID == id)
                {
                   return enu.Current;
                }
            }
            return null;
        }

        public IEnumerable<ContactDetails> GetContactDetails(string fullName)
        {
            var enu = Book.GetEnumerator();
            //List<ContactDetails> list = new List<ContactDetails>();

            //while (enu.MoveNext())
            //{
            //    if ((enu.Current).FullName == fullName)
            //    {
            //        list.Add(enu.Current);
            //    }
            //}

            foreach(ContactDetails cd in Book)
            {
                if(cd.FullName == fullName)
                {
                    yield return cd;
                }
            }
        }

        public int HowManyHasPhonePrefix(string prefixPhone)
        {
            int countContacts = 0;
            var enu = Book.GetEnumerator();
            while (enu.MoveNext())
            {
                var phonesEnu = ((enu.Current).Phones).GetEnumerator();
                while (phonesEnu.MoveNext())
                {
                    if ((phonesEnu.Current).StartsWith(prefixPhone))
                    {
                        ++countContacts;
                        break;
                    }
                }
            }
            return countContacts;
        }

        public List<ContactDetails> SearchContacts(string subString)
        {
            var enu = Book.GetEnumerator();
            List<ContactDetails> list = new List<ContactDetails>();

            while (enu.MoveNext())
            {
                string currentFullName = (enu.Current).FullName.ToLower();
                string subLower = subString.ToLower();
                if (currentFullName.Contains(subLower))
                {
                    list.Add(enu.Current);
                }
            }
            return list;
        }

        public override string ToString()
        {
            return string.Format(string.Join("\n", Book));
        }
    }

    public class ContactDetails
    {
        private int _id;
        private string _fullName;
        private string _city;
        private List<string> _phones = new List<string>();

        //constructor
        public ContactDetails(int id, string fullName, string city, List<string> phones)
        {
            this._id = id;
            this._fullName = fullName;
            this._city = city;
            this._phones = phones;
        }


        public int MyProperty { get; private set; }
        //gets
        public int ID
        {
            get
            {
                return _id;
            }
        }
        public string FullName
        {
            get
            {
                return _fullName;
            }
        }
        public string City
        {
            get
            {
                return _city;
            }
        }
        public List<string> Phones
        {
            get
            {
                return _phones;
            }
        }

        public override string ToString()
        {
            return string.Format("Id: {0}\nFull Name: {1}\nCity: {2}\nPhones: {3}\n"
                                , _id, _fullName, _city, string.Join(", ", _phones));
        }
    }
}
