using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net.Http.Headers;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;

namespace princeton
{
    public partial class MainPage : TabbedPage
    {
        public MainPage()
        {
            InitializeComponent();
        }

        private async void Button_Clicked(object sender, EventArgs e)
        {
            string key = Convert.ToBase64String(Guid.NewGuid().ToByteArray()).Substring(0, 16);
            string con = "\"description\":" +
                    " \"Potato grown on one acre of Sally's Farm.\"," +
                    " \"external_url\": \"https://openseacreatures.io/3\"," +
                    " \"image\": \"https://freepngimg.com/download/potato/22753-1-potato-clipart.png\", " +
                    " \"name\": \"Potato\"," +
                    "\"ID\": 67238321";
            var client = new HttpClient();
            var request = new HttpRequestMessage
            {
                Method = HttpMethod.Post,
                RequestUri = new Uri("https://api.verbwire.com/v1/nft/mint/quickMintFromMetadata"),
                Headers =
    {
        { "accept", "application/json" },
        { "X-API-Key", "sk_live_5a03b097-0797-49eb-ae7e-27d3c4b17780" },
    },
                Content = new MultipartFormDataContent
    {
        new StringContent("goerli")
        {
            Headers =
            {
                ContentDisposition = new ContentDispositionHeaderValue("form-data")
                {
                    Name = "chain",
                }
            }
        },
        new StringContent(con)
        {
            Headers =
            {
                ContentDisposition = new ContentDispositionHeaderValue("form-data")
                {
                    Name = "data",
                }
            }
        },
    },
            };
            using (var response = await client.SendAsync(request))
            {
                response.EnsureSuccessStatusCode();
                var body = await response.Content.ReadAsStringAsync();
                Console.WriteLine(body);
            }
        }

        private void Button_Clicked_1(object sender, EventArgs e)
        {
            App.Current.MainPage = new newmain();
        }
    }
}
