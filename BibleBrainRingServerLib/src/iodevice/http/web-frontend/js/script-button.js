const sendTimeBtn = document.querySelector("#send-time-btn");

sendTimeBtn.addEventListener("click", () => {
  sendTime();
});

function sendTime() {
  const sendingTime = `time=${new Date().getTime()}`;
  sendData(sendingTime);
}

function sendData(data) {
  var http = new XMLHttpRequest();
  var url = "http://192.168.0.104:8080/post";
  var params = data;
  http.open("POST", url, true);

  //Send the proper header information along with the request
  http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

  http.onreadystatechange = function () {
    //Call a function when the state changes.
    console.log("onreadystatechange", http.responseText);
    if (http.readyState == 4 && http.status == 200) {
      alert(http.responseText);
    }
  };
  http.send(params);
}
