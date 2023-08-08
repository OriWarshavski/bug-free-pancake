using System;
namespace Train
{
	public class Train
	{
		private List<Cabin> _locomotive = new List<Cabin>();

        internal void AddCabins(int num)
        {
            for (int i = 0; i < num; ++i)
            {
                _locomotive.Add(new Cabin(i + 1));
            }
        }

        public void StartMoving()
        {
            var enu = _locomotive.GetEnumerator();
            while(enu.MoveNext())
            {
                enu.Current.DoorsClosing();
            }
        }

        public void Stop()
        {
            var enu = _locomotive.GetEnumerator();
            while (enu.MoveNext())
            {
                enu.Current.DoorsOpenning();
            }
        }

        public void MassegeForPassengers(string message)
        {
            var enu = _locomotive.GetEnumerator();
            while (enu.MoveNext())
            {
                enu.Current.MessageForPassengers(message);
            }
        }
    }

	public class Platform     
    {
        public Train Locomotive { get; private set; }

        public Platform(int cabinsNum)
        {
            Locomotive = new Train();
            if (cabinsNum < 0)
            {
                throw new TrainException("Train must have 0, 1 or more cabins");
            }
            Locomotive.AddCabins(cabinsNum);
        }
    }

    public class TrainException : Exception
    {
        public TrainException(string msg) : base(msg)
        {
        }
    }
}

