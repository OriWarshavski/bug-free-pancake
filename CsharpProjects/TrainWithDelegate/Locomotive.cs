using System;

namespace TrainWithDelegate
{
	public class Locomotive
	{
        public Locomotive()
		{

		}


		public void StartMoving()
		{
			Console.WriteLine("Locomotive start MOVING");
		}

        public void Stop()
        {
            Console.WriteLine("Locomotive STOPS");
        }

        public void Massege(string msg)
        {
            Console.WriteLine($"Locomotive send MESSAGE: {msg}");
        }
    }
}

