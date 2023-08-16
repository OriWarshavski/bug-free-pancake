namespace Practice;

class Program
{
    static void Main(string[] args)
    {
        List<int> nums = new List<int> {1, 2, 3, 4, 5, 6, 7 };
        List<string> strings = new List<string> { "ori", "yarden", "bye", "shaul", "persi", "miko", "hi" };

        //List<int> updated = Pickup(nums, IsOdd);
        //printList<int>(updated);

        //List<string> updated2 = Pickup(strings, IsMoreThan3Chars);
        //printList<string>(updated2);

        //List<int> trans = Transform(nums, PowerOfThree);
        //printList<int>(trans);

        List<int> trans2 = Transform(strings, LengthOfString);
        printList<int>(trans2);
    }

    //Operations
    static Predicate<int> IsEven = (n) => n % 2 == 0;
    static Predicate<int> IsOdd = (n) => n % 2 != 0;
    static Predicate<string> IsMoreThan3Chars = (str) => str.Length > 3;

    static Func<int, int> PowerOfThree = (n) => n*n*n;
    static Func<string, int> LengthOfString = (str) => str.Length;

    //Generic functions
    static List<T> Pickup<T>(List<T> input, Predicate<T> prdFun)
    {
        List<T> updated = new List<T>();

        var enu = input.GetEnumerator();

        while (enu.MoveNext())
        {
            if (prdFun.Invoke(enu.Current))
            {
                updated.Add(enu.Current);
            }
        }
        return updated;
    }

    static List<T2> Transform<T1, T2>(List<T1> input, Func<T1, T2> prdFun)
    {
        List<T2> transformed = new List<T2>();

        var enu = input.GetEnumerator();

        while (enu.MoveNext())
        {
            transformed.Add(prdFun(enu.Current));
        }
        return transformed;
    }

    //simple loops
    static List<int> EvenNums(List<int> input)
    {
        List<int> updated = new List<int>();

        var enu = input.GetEnumerator();

        while(enu.MoveNext())
        {
            if(enu.Current % 2 == 0)
            {
                updated.Add(enu.Current);
            }
        }
        return updated;
    }

    static List<int> OddNums(List<int> input)
    {
        List<int> updated = new List<int>();

        var enu = input.GetEnumerator();

        while (enu.MoveNext())
        {
            if (enu.Current % 2 != 0)
            {
                updated.Add(enu.Current);
            }
        }
        return updated;
    }

    static List<string> StringMoreThan3Chars(List<string> input)
    {
        List<string> updated = new List<string>();

        var enu = input.GetEnumerator();

        while (enu.MoveNext())
        {
            if (enu.Current.Length > 3)
            {
                updated.Add(enu.Current);
            }
        }
        return updated;
    }

    //print function for tests
    static void printList<T>(List<T> list)
    {
        var enu = list.GetEnumerator();

        while (enu.MoveNext())
        {
            Console.WriteLine(enu.Current);
        }
    }

}

