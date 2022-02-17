const form = document.querySelector(".validate-form");

form.addEventListener("submit", (e) => {
  e.preventDefault();
  const inputs = document.querySelectorAll(".login100-form input");
  const sendingData = `name=${inputs[0].value}&color=${inputs[1].value}`;
  sendData(sendingData);
});

function sendData(data) {
  var http = new XMLHttpRequest();
  var url = "http://176.36.224.228:8080/bogdan_post";
  var params = data;
  http.open("POST", url, true);

  //Send the proper header information along with the request
  http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

  http.onreadystatechange = function () {
    //Call a function when the state changes.
    console.log("onreadystatechange", http.responseText);
    if (http.readyState == 4 && http.status == 200) {
        const obj = JSON.parse(http.responseText);
        if(obj.your_name == "ilya"){
        	console.log("obj.your_name", obj.your_name);
        	window.location.replace("http://176.36.224.228:8080/button");
        }
      // alert(http.responseText);
      //window.location.replace("http://192.168.0.104:8080/button");
    }
  };
  http.send(params);
}
