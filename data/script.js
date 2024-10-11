const userName  = "ThinhNguyen1801";
const base_url  = `https://io.adafruit.com/api/v2/${userName}/feeds`;
const API_Key   = "" // Feed key goes here

const tempContainer = document.getElementById("temp"); // HTML ID
const humidContainer = document.getElementById("humid"); // HTML ID  

const getSensorValue = async (feedKey, container) => {
  fetch(base_url + `/${feedKey}/data?limit=1`, {
    headers: {
      "X-AIO-Key": API_Key,
    },
    method: "GET",
  })
    .then((response) => {
      {
        if (!response.ok) {
          throw new Error("Network didn't reponse");
        }
        return response.json();
      }
    })
    .then((data) => {
      container.innerText = data[0].value;
    });
};
setInterval(() => {
    getSensorValue("temperature", tempContainer); // Temperature feed key
    getSensorValue("humidity", humidContainer);   // Humidity feed key
  }, 1000);
