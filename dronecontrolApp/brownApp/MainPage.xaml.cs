using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Xamarin.Forms;

namespace brownApp
{
    public partial class MainPage : ContentPage
    {
        static double PosX = 0;
        static double PosY = 0;
        static List<point> points = new List<point>();
        static bool trig = true;
        public MainPage()
        {
            InitializeComponent();
           

        }

        private void Button_Clicked(object sender, EventArgs e)
        {
            UdpClient udpClient = new UdpClient();

            udpClient.Connect("192.168.10.1", 8889);
            Byte[] sendBytes = Encoding.UTF8.GetBytes("command");
            udpClient.Send(sendBytes, sendBytes.Length);
            Device.StartTimer(new TimeSpan(10), () =>
            {

                UdpClient listener = new UdpClient(8890);
                IPEndPoint groupEP = new IPEndPoint(IPAddress.Any, 8890);
                try
                {

                    Console.WriteLine("Waiting for broadcast");
                    byte[] bytes = listener.Receive(ref groupEP);

                    Console.WriteLine($"Received broadcast from {groupEP} :");
                    Console.WriteLine($" {Encoding.ASCII.GetString(bytes, 0, bytes.Length)}");
                    var a = Encoding.ASCII.GetString(bytes, 0, bytes.Length);
                    var b = a.Split(';');
                    var c = b[13].Split(':');
                    var d = int.Parse(c[1]); //z

                    var tvx = b[8].Split(':');
                    var vx = int.Parse(tvx[1]);

                    var tvy = b[9].Split(':');
                    var vy = int.Parse(tvy[1]);

                    if (vx != 0 || vy != 0)
                    {
                        PosX = PosX + vx;
                        PosY = PosY + vy;
                        points.Add(new point { x = PosX, y = PosY, z = d });
                    }

                    //8 = vx, 9= vy, 10 vz
                }
                catch (Exception exc)
                {
                    //Console.WriteLine(e);
                }
                finally
                {
                    listener.Close();
                }
                return trig;
            });
        }

        private async void Button_Clicked2(object sender, EventArgs e)
        {
            UdpClient udpClient = new UdpClient();
            try
            {
               
                udpClient.Connect("192.168.10.1", 8889);
                Byte[] sendBytes = Encoding.UTF8.GetBytes("takeoff");
                udpClient.Send(sendBytes, sendBytes.Length);
                await Task.Delay(5000);

                sendBytes = Encoding.UTF8.GetBytes("forward 40");
                udpClient.Send(sendBytes, sendBytes.Length);
                await Task.Delay(5000);

                sendBytes = Encoding.UTF8.GetBytes("right 40");
                udpClient.Send(sendBytes, sendBytes.Length);
                await Task.Delay(5000);

                sendBytes = Encoding.UTF8.GetBytes("back 40");
                udpClient.Send(sendBytes, sendBytes.Length);
                await Task.Delay(5000);

                sendBytes = Encoding.UTF8.GetBytes("left 40");
                udpClient.Send(sendBytes, sendBytes.Length);
                await Task.Delay(5000);

                sendBytes = Encoding.UTF8.GetBytes("right 20");
                udpClient.Send(sendBytes, sendBytes.Length);
                await Task.Delay(5000);

                sendBytes = Encoding.UTF8.GetBytes("forward 40");
                udpClient.Send(sendBytes, sendBytes.Length);
                await Task.Delay(5000);

                sendBytes = Encoding.UTF8.GetBytes("back 20");
                udpClient.Send(sendBytes, sendBytes.Length);
                await Task.Delay(5000);

                sendBytes = Encoding.UTF8.GetBytes("left 20");
                udpClient.Send(sendBytes, sendBytes.Length);
                await Task.Delay(5000);

                sendBytes = Encoding.UTF8.GetBytes("right 40");
                udpClient.Send(sendBytes, sendBytes.Length);
                

              




            }
            catch (Exception ex)
            { 
            }
        }

        private void Button_Clicked_1(object sender, EventArgs e)
        {
            trig = false;
            UdpClient udpClient = new UdpClient();
            udpClient.Connect("192.168.10.1", 8889);
            Byte[] sendBytes = Encoding.UTF8.GetBytes("land");
            udpClient.Send(sendBytes, sendBytes.Length);
            string s = "";
            int temp = 128;
            foreach(point p in points)
            {
                s = s + p.x.ToString() + " " + p.y.ToString() + " " + p.z.ToString() + " " + temp.ToString() + " " + temp.ToString() + " " + temp.ToString() + " " + "0" + " " + "0" + " " + "1";
                s = s + "\n";
            }
        }
    }
}
