using System;

namespace TrainWithDelegate
{
	public class Cabin
	{
        private int _id;

		public Cabin(int id)
		{
			_id = id;
		}

		public void DoorsOpenning()
		{
			Console.WriteLine($"Cabin #{_id}: Doors OPENNING");
		}

        public void DoorsClosing()
        {
            Console.WriteLine($"Cabin #{_id}: Doors CLOSING");
        }

        public void MessageForPassengers(string message)
        {
            Console.WriteLine($"Cabin #{_id}: message for passengers:\n\"{message}\"");
        }
    }
}

