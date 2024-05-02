const char Webpage[] =
R"=====(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>He thong giam sat</title>
    <link rel="stylesheet" href="style.css" />
    <style>
      body,
      html {
        height: 100%;
        width: 100%;
        margin: 0;
        background-image: url(/PIC2.jpg);
        background-position: center;
        background-size: 100% 100%;
        background-repeat: no-repeat;
      }
      * {
  margin: 0;
  padding: 0;
}
.titleContainer {
  display: flex;
  justify-content: space-between;
  height: 5px;
  width: 100%;
}
.title {
  position: absolute;
  right: 9%;
  text-align: center; /* Căn lề giữa */
  font-weight: bold; /* Font in đậm */
  color: rgb(30, 2, 69);
  font-family: "Times New Roman", Times, serif;
  font-size: 39px;
  letter-spacing: 0.15em;
  padding-top: 30px;
}
.display {
  display: inline-flex;
  border: 1px solid transparent;
  margin-top: 180px;
}
.display .sensor {
  display: inline-block;
  position: relative;
  left: 160px;
  background-color: rgba(172, 172, 25, 0.897);
  text-size-adjust: 10%;
  text-align: center;
  width: 570px;
  border-radius: 5%;
}
.display .threshold {
  display: inline-block;
  border: 1px solid transparent;
  position: relative;
  left: 350px;
  background-color: rgba(172, 172, 25, 0.897);
  width: 500px; /* Độ rộng của phần tử */
  text-align: center;
  border-radius: 5%;
  padding: 30px;
  line-height: 2;
}
.temperature-threshold input {
  width: 200px;
  height: 40px;
  font-size: 19px;
  text-align: center;
  font-family: "Times New Roman", Times, serif;
  font-weight: bold;
}
.humidity-threshold input {
  width: 200px;
  height: 40px;
  font-size: 19px;
  text-align: center;
  font-family: "Times New Roman", Times, serif;
  font-weight: bold;
}

.equipmentContainer {
  width: 100%;
  height: 300px;
  margin-top: 20px;
}
.equipmentContainer .equipmentTitle {
  font-family: "Orbitron", sans-serif;
  text-transform: uppercase;
  letter-spacing: 0.15em;
  font-size: 15px;
  background-color: rgba(172, 172, 25, 0.897);
  height: 15%;
  display: flex;
  justify-content: space-around;
  color: rgb(25, 30, 179);
  border-radius: 30px;
  font-weight: bold;
}
.equipmentContainer .equipmentTabContainer {
  display: flex;
  flex-direction: row;
  justify-content: space-around;
  background-color: rgba(53, 89, 119, 0.795);
  height: 85%;
  border: 3px solid rgb(25, 90, 230);
  border-radius: 30px;
}
.light {
  display: flex;
  flex-direction: column;
  flex-wrap: nowrap;
  justify-content: flex-start;
  align-items: stretch;
  align-content: stretch;
}
.fan {
  display: flex;
  flex-direction: column;
  flex-wrap: nowrap;
  justify-content: flex-start;
  align-items: stretch;
  align-content: stretch;
}
.phunsuong {
  display: flex;
  flex-direction: column;
  flex-wrap: nowrap;
  justify-content: flex-start;
  align-items: stretch;
  align-content: stretch;
}
img.light_on {
  width: 200px;
  height: 200px;
}
img.light_off {
  width: 200px;
  height: 200px;
}
img.fan_on {
  width: 200px;
  height: 200px;
}
img.fan_off {
  width: 200px;
  height: 200px;
}
img.PS_on {
  width: 200px;
  height: 200px;
}
img.PS_off {
  width: 200px;
  height: 200px;
}
#btn1 {
  width: 6rem;
  font-family: "Orbitron", sans-serif;
  text-transform: uppercase;
  letter-spacing: 0.15em;
  font-size: 20px;
  outline: none;
  cursor: pointer;
  background-color: rgb(255, 0, 0);
  border-radius: 30px;
}
#btn2 {
  width: 6rem;
  font-family: "Orbitron", sans-serif;
  text-transform: uppercase;
  letter-spacing: 0.15em;
  font-size: 20px;
  outline: none;
  cursor: pointer;
  background-color: rgb(0, 255, 76);
  border-radius: 30px;
}
#btn3 {
  width: 6rem;
  font-family: "Orbitron", sans-serif;
  text-transform: uppercase;
  letter-spacing: 0.15em;
  font-size: 20px;
  outline: none;
  cursor: pointer;
  background-color: rgb(255, 0, 0);
  border-radius: 30px;
}
#btn4 {
  width: 6rem;
  font-family: "Orbitron", sans-serif;
  text-transform: uppercase;
  letter-spacing: 0.15em;
  font-size: 20px;
  outline: none;
  cursor: pointer;
  background-color: rgb(0, 255, 76);
  border-radius: 30px;
}
#btn5 {
  width: 6rem;
  font-family: "Orbitron", sans-serif;
  text-transform: uppercase;
  letter-spacing: 0.15em;
  font-size: 20px;
  outline: none;
  cursor: pointer;
  background-color: rgb(255, 0, 0);
  border-radius: 30px;
}
#btn6 {
  width: 6rem;
  font-family: "Orbitron", sans-serif;
  text-transform: uppercase;
  letter-spacing: 0.15em;
  font-size: 20px;
  outline: none;
  cursor: pointer;
  background-color: rgb(0, 255, 76);
  border-radius: 30px;
}
.footer {
  font-family: "Orbitron", sans-serif;
  text-transform: uppercase;
  letter-spacing: 0.15em;
  font-size: 10px;
  color: white;
  padding-top: 10px;
  text-align: center;
  background-color: rgb(88, 86, 86);
  border-radius: 30px;
}

    </style>
  </head>
  <body>
    <div class="titleContainer">
      <div class="logo">
        <img src="ptit" alt="" style="width: 150px; height: 150px" />
      </div>
      <div class="title">HỆ THỐNG GIÁM SÁT VÀ ĐIỀU KHIỂN VƯỜN NẤM</div>
    </div>
    <div>
      <div class="display">
      <div class="sensor">
        <div class="nhietdo">
          <div class="nhietke">
            <img
              src="nhietke"
              alt=""
              style="width: 90px; height: 90px"
            />
          </div>
          <h2
          >
            TEMPERATURE: <span id="temp"> </span> °C
          </h2>
            

        </div>
        <div class="doamdat">
          <div class="amke">
            <img
              src="doam"
              alt=""
              style="width: 120px; height: 100px"
            />
          </div>
          <h2
          >
            SOID MOISTURE: <span id="humi"> </span> %
          </h2>
        </div>
      </div>
      <div class="threshold">
        <div class="temperature-threshold">
          <h2>TEMPERATURE SET:</h2>
          <input type="number" step="0.1" placeholder="Nhập nhiệt độ" id="NhietdoInput"/>
        </div>
        <div class="humidity-threshold">
          <h2>SOID MOISTURE SET:</h2>
          <input type="number" step="0.1" placeholder="Nhập độ ẩm" id="DoamInput"/>
        </div>
      </div>
    </div>
    <div class="equipmentContainer">
      <div class="equipmentTitle">
        <h1><i class="fas fa-wifi"></i>ĐIỀU KHIỂN THIẾT BỊ</h1>
      </div>
      <div class="equipmentTabContainer">
        <div class="light">
          <img src="light_off" class="light_on" id="light" alt="" />
          <div class="boxbutton1">
            <button type="button" id="btn1">On</button>
            <button type="button" id="btn2">Off</button><br /><br />
          </div>
        </div>
        <div class="fan">
          <img src="fan_off" class="fan_on" id="fan" alt="" />
          <div class="boxbutton2">
            <button type="button" id="btn3">On</button>
            <button type="button" id="btn4">Off</button><br /><br />
          </div>
        </div>
        <div class="phunsuong">
          <img src="PSoff" class="PS_on" id="phunsuong" alt="" />
          <div class="boxbutton3">
            <button type="button" id="btn5">On</button>
            <button type="button" id="btn6">Off</button><br /><br />
          </div>
        </div>
      </div>
    </div>
    <div class="footer">
      <label for="text">Nguyễn Minh Tiến - B20DCDT183</label><br />
      <label for="text">HỌC VIỆN CÔNG NGHỆ BƯU CHÍNH VIỄN THÔNG</label><br />
    </div>
    <script src="main.js"></script>
    <!------------------------------------------------------------------------------------>
    <script src="https://www.gstatic.com/firebasejs/8.10.0/firebase-app.js"></script>
    <script src="https://www.gstatic.com/firebasejs/8.8.1/firebase-database.js"></script>

    <!-- TODO: Add SDKs for Firebase products that you want to use
     https://firebase.google.com/docs/web/setup#available-libraries -->
    <script src="https://www.gstatic.com/firebasejs/8.6.7/firebase-analytics.js"></script>
    <script type="module">
      // Import the functions you need from the SDKs you need

      // TODO: Add SDKs for Firebase products that you want to use
      // https://firebase.google.com/docs/web/setup#available-libraries

      // Your web app's Firebase configuration
      // For Firebase JS SDK v7.20.0 and later, measurementId is optional
      const firebaseConfig = {
        apiKey: "AIzaSyDAP_GzmXvjV-8KawkBgDcMjSSHVJyt2Qk",
        authDomain: "garden-54e21.firebaseapp.com",
        databaseURL: "https://garden-54e21-default-rtdb.firebaseio.com",
        projectId: "garden-54e21",
        storageBucket: "garden-54e21.appspot.com",
        messagingSenderId: "354984548769",
        appId: "1:354984548769:web:d47c31474a7b44181ed3e0",
        measurementId: "G-Q73C9C0PG0",
      };

      // Initialize Firebase
      firebase.initializeApp(firebaseConfig);
      firebase.database();

      var tempElement = document.getElementById("temp");
      var dbRefTemp = firebase.database().ref("sensor/Nhietdo");
      dbRefTemp.on("value", (snap) => (tempElement.innerText = snap.val()));

      var humiElement = document.getElementById("humi");
      var dbRefHumi = firebase.database().ref("sensor/Doam");
      dbRefHumi.on("value", (snap) => (humiElement.innerText = snap.val()));

      // Sự kiện nghe và cập nhật giá trị cho ô input nhiệt độ từ Firebase
var tempInputElement = document.getElementById("NhietdoInput");
var dbRefTempset = firebase.database().ref("sensorset/Nhietdoset");
dbRefTempset.on("value", function(snapshot) {
  var valueFromFirebase = snapshot.val();
  tempInputElement.value = valueFromFirebase;
});

// Sự kiện nghe cho ô input nhiệt độ để cập nhật giá trị lên Firebase
tempInputElement.addEventListener("input", function(event) {
  var newValue = parseFloat(event.target.value);
  firebase.database().ref("sensorset/Nhietdoset").set(newValue);
});

// Sự kiện nghe và cập nhật giá trị cho ô input độ ẩm từ Firebase
var humiInputElement = document.getElementById("DoamInput");
var dbRefDoamset = firebase.database().ref("sensorset/Doamset");
dbRefDoamset.on("value", function(snapshot) {
  var valueFromFirebase = snapshot.val();
  humiInputElement.value = valueFromFirebase;
});

// Sự kiện nghe cho ô input độ ẩm để cập nhật giá trị lên Firebase
humiInputElement.addEventListener("input", function(event) {
  var newValue = parseFloat(event.target.value);
  firebase.database().ref("sensorset/Doamset").set(newValue);
});


      document.addEventListener("DOMContentLoaded", function () {
        var btn1On = document.getElementById("btn1");
        var btn1Off = document.getElementById("btn2");
        var lightImage = document.getElementById("light");

        firebase
          .database()
          .ref("device/light")
          .on("value", function (snapshot) {
            var lightStatus = snapshot.val();
            if (lightStatus === 1) {
              lightImage.src = "light_on";
            } else {
              lightImage.src = "light_off";
            }
          });

        btn1On.addEventListener("click", function () {
          lightImage.src = "light_on";
          firebase.database().ref("device").update({
            light: 1,
          });
        });

        btn1Off.addEventListener("click", function () {
          lightImage.src = "light_off";
          firebase.database().ref("device").update({
            light: 0,
          });
        });
        // Điều khiển quạt
        var fanOnButton = document.getElementById("btn3");
        var fanOffButton = document.getElementById("btn4");
        var fanImage = document.getElementById("fan");
        firebase
          .database()
          .ref("device/fan")
          .on("value", function (snapshot) {
            var fanStatus = snapshot.val();
            if (fanStatus === 1) {
              fanImage.src = "fan_on";
            } else {
              fanImage.src = "fan_off";
            }
          });
        fanOnButton.addEventListener("click", function () {
          fanImage.src = "fan_on";
          firebase.database().ref("device").update({
            fan: 1,
          });
        });

        fanOffButton.addEventListener("click", function () {
          fanImage.src = "fan_off";
          firebase.database().ref("device").update({
            fan: 0,
          });
        });

        // Điều khiển máy phun sương
        var phunsuongOnButton = document.getElementById("btn5");
        var phunsuongOffButton = document.getElementById("btn6");
        var phunsuongImage = document.getElementById("phunsuong");

        firebase
          .database()
          .ref("device/phunsuong")
          .on("value", function (snapshot) {
            var phunsuongStatus = snapshot.val();
            if (phunsuongStatus === 1) {
              phunsuongImage.src = "PSon";
            } else {
              phunsuongImage.src = "PSoff";
            }
          });

        phunsuongOnButton.addEventListener("click", function () {
          phunsuongImage.src = "PSon";
          firebase.database().ref("device").update({
            phunsuong: 1,
          });
        });

        phunsuongOffButton.addEventListener("click", function () {
          phunsuongImage.src = "PSoff";
          firebase.database().ref("device").update({
            phunsuong: 0,
          });
        });
      });
      var tabButtons = document.querySelectorAll(
  ".tabContainer .buttonContainer button"
);

function showPanel(panel) {
  tabButtons.forEach(function (node) {
    node.style.backgroundColor = "";
    node.style.color = "";
  });
}

// khoi tao cac thong so
let btn1 = document.querySelector("#btn1");
let img = document.querySelector("#light");
let btn2 = document.querySelector("#btn2");

// functions nut bam
btn1.addEventListener("click", () => {
  img.src = "light_on";
});

btn2.addEventListener("click", () => {
  img.src = "light_off";
});

let btn3 = document.querySelector("#btn3");
let img2 = document.querySelector("#fan");
let btn4 = document.querySelector("#btn4");

// functions nut bam
btn3.addEventListener("click", () => {
  img2.src = "fan_on";
});

btn4.addEventListener("click", () => {
  img2.src = "fan_off";
});

let btn5 = document.querySelector("#btn5");
let img3 = document.querySelector("#phunsuong");
let btn6 = document.querySelector("#btn6");

// functions nut bam
btn5.addEventListener("click", () => {
  img3.src = "PSon";
});

btn6.addEventListener("click", () => {
  img3.src = "PSoff";
});


    </script>
  </body>
</html>
)=====";
