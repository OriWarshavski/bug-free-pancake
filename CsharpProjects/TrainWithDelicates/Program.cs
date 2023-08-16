using System.Threading;

namespace TrainWithDelegate;

class Program
{
    static void Main(string[] args)
    {
        Platform p = new Platform(3);
        p.StartMoving();
        Thread.Sleep(1000);
        p.MassegeForPassangers("first stop: Tel-Aviv Hagana");
        Thread.Sleep(1000);
        p.Stop();
    }
}

