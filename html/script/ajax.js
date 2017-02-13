setInterval(updateSwitch, 2000); //1000 MS == 1 s

function changeState() {
    var switchState = document.getElementById("relaySwitch");
    var relState = document.getElementById("relayState");

var xhttp;
if (window.XMLHttpRequest) {
    xhttp = new XMLHttpRequest();
    } else {
    // code for IE6, IE5
    xhttp = new ActiveXObject("Microsoft.XMLHTTP");
}
  xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
    if (this.responseText == "true"){
      switchState.checked = true;
      relState.innerHTML  = "Relay On";
    }
    else if (this.responseText == "false"){
      switchState.checked = false;
      relState.innerHTML  = "Relay Off";
    }
  }
  };
  xhttp.open("GET", "relayToggle", true);
  xhttp.send();
}


function updateSwitch() {
var switchState = document.getElementById("relaySwitch");
var relState = document.getElementById("relayState");
var xhttp;
if (window.XMLHttpRequest) {
    xhttp = new XMLHttpRequest();
    } else {
    xhttp = new ActiveXObject("Microsoft.XMLHTTP");
}
  xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
    if (this.responseText == "true"){
      switchState.checked = true;
      relState.innerHTML  = "Relay On";
    }
    else if (this.responseText == "false"){
      switchState.checked = false;
      relState.innerHTML  = "Relay Off";
    }
  }
  };
  xhttp.open("GET", "updateRelay", true);
  xhttp.send();
}