const sendTimeBtn = document.querySelector("#send-btn-wrapper");

sendTimeBtn.addEventListener("click", () => {
  console.log("click");
  sendTime();
});

function sendTime() {
  let myGuid = localStorage.getItem("guid");
  const sendingTime = `guid=${myGuid==undefined ? "" : myGuid}&time=${new Date().getTime()}`;
  sendData(sendingTime);
}

function sendData(data) {
  var http = new XMLHttpRequest();
  var url = `${window.location.origin}/button-pressed`;
  var params = data;
  http.open("POST", url, true);

  //Send the proper header information along with the request
  http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

  http.onreadystatechange = function () {
    if (http.readyState == 4 && http.status == 200) {
      const obj = JSON.parse(http.responseText);  
      if(obj.status=="redirect") {
        window.location.replace(`${window.location.origin}/${obj.page}`);
      }
      console.log(obj);
    }
  };
  http.send(params);
}
