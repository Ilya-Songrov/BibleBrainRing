let HOST = window.location.origin;
const form = document.querySelector(".validate-form");
form.addEventListener("submit", (e) => {
  e.preventDefault();
  const inputs = document.querySelectorAll(".login100-form input");
  const guid = localStorage.getItem('guid');
  const sendingData = `name=${inputs[0].value}&color=${inputs[1].value}&guid=${guid==undefined ? "" : guid}`;
  sendData(sendingData);
});

function sendData(data) {
  var http = new XMLHttpRequest();
  var url = `${HOST}/register`;
  var params = data;
  http.open("POST", url, true);
  http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
  http.onreadystatechange = function () {
    if (http.readyState == 4 && http.status == 200) {
        const obj = JSON.parse(http.responseText);
        if(obj.status=="success") {
        	window.location.replace(`${HOST}/waiting-hall`);
          return obj;
        }
        if (obj.status=="error") {
          alert (obj.error);
        }
        console.log(obj);
     
    }
  };
  http.send(params);
}
