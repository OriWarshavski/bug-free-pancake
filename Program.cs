using System.Threading;

namespace Train;

class Program
{
    static void Main(string[] args)
    {
        Platform p = new Platform(3);
        p.Locomotive.MassegeForPassengers("We are ready to go!");
        Thread.Sleep(1000);
        p.Locomotive.StartMoving();
        Thread.Sleep(5000);

        p.Locomotive.MassegeForPassengers("Our first stop is: Beer Sheva - north");
        Thread.Sleep(1000);
        p.Locomotive.Stop();
        Thread.Sleep(1000);

        p.Locomotive.StartMoving();
        Thread.Sleep(3000);

        p.Locomotive.MassegeForPassengers("Our last station is: Beer Sheva - center");
        Thread.Sleep(1000);
        p.Locomotive.Stop();
        Thread.Sleep(1000);

        p.Locomotive.MassegeForPassengers("Please dont forget your belongings!\n Thank you for choosing our train.");
    }
}

