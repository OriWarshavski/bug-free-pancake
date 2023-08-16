using System;
namespace TrainWithDelegate
{
	public class Platform
	{
        //private List<Cabin> _cabins = new List<Cabin>();
        private Locomotive _locomotive = new Locomotive();
        private Action _movingFunc;
        private Action _stopingFunc;
        private Send _massegeFunc;

        delegate void Action();
        delegate void Send(string msg);

        public Platform(int cabinsNum)
		{
            _movingFunc = new Action(_locomotive.StartMoving);
            _stopingFunc = new Action(_locomotive.Stop);
            _massegeFunc = new Send(_locomotive.Massege);

            for (int i = 1; i <= cabinsNum; ++i)
			{
                Cabin c = new Cabin(i);
                _movingFunc += c.DoorsClosing;
                _stopingFunc += c.DoorsOpenning;
                _massegeFunc += c.MessageForPassengers;
                //_cabins.Add(c);
            }
		}

        public void StartMoving()
        {
            _movingFunc.Invoke();
        }

        public void Stop()
        {
            _stopingFunc.Invoke();
        }

        public void MassegeForPassangers(string msg)
        {
            _massegeFunc.Invoke(msg);
        }
    }
}

