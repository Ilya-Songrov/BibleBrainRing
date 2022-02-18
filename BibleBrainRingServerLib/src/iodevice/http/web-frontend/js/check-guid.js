let guid = localStorage.getItem('guid');
sendData(`guid=${guid==undefined ? "" : guid}`); 
function sendData(data) {
    var http = new XMLHttpRequest();
    var url = `${window.location.origin}/check-guid`;
    var params = data;
    http.open("POST", url, true);
    http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    http.onreadystatechange = function () {
      if (http.readyState == 4 && http.status == 200) {
          const obj = JSON.parse(http.responseText);
        localStorage.setItem("guid",obj.guid);
        console.log(obj);
        if(`${"http://" + window.location.host}/${obj.page}`!=window.location.href) {
            window.location.replace(`${window.location.origin}/${obj.page}`);
        }
      }
    };
    http.send(params); 
}
