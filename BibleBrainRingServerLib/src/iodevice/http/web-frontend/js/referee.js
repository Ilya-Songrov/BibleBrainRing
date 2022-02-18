const refButtons = document.querySelectorAll(".btn-ref");
refButtons.forEach((elem)=>{
    elem.addEventListener("click",(e)=>{
        if(e.target.classList.contains("reset-ref-btn")){
            sendRef("referee-reset");
        }
        if(e.target.classList.contains("start-ref-btn")){
            sendRef("referee-start-time");
        }
    })
})

function sendRef(route) {
    console.log(route);
  const currentTime = `time=${new Date().getTime()}`;
  const guid = localStorage.getItem('guid');
  let data = `guid=${guid==undefined ? "" : guid}&`+currentTime;
  var http = new XMLHttpRequest();
  var url = `${window.location.origin}/${route}`;
  var params = data;
  http.open("POST", url, true);
  http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
  http.onreadystatechange = function () {
    if (http.readyState == 4 && http.status == 200) {
        const obj = JSON.parse(http.responseText);
        if (obj.status=="error") {
          alert (obj.error);
        }
    }
  };
  http.send(params);
}