setInterval(updateSwitch, 2000); //1000 MS == 1 s

function setSwitch(isOn){
  var relNote = document.getElementById("idRelaySwitchNote");
  var relSwitch = document.getElementById("idRelaySwitch");
  var relButton = document.getElementById("idRelayButton");
  var relButtonNote = document.getElementById("idButtonRelayNote");
  if (isOn){
      relNote.innerHTML = "Switch off Relay";
      relSwitch.checked = true;
      relButton.innerHTML = "Relay Off";
      relButtonNote.innerHTML = "or push buttons to switch off Relay";
  }
  else{
      relNote.innerHTML = "Switch on Relay";
      relSwitch.checked = false;
      relButton.innerHTML = "Relay ON";
      relButtonNote.innerHTML = "or push buttons to switch on Relay";
  }
}

function updateSwitch() {
var xhttp;

if (window.XMLHttpRequest) {
    xhttp = new XMLHttpRequest();
    } else {
    xhttp = new ActiveXObject("Microsoft.XMLHTTP");
}
  xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
    if (this.responseText == "true"){
      setSwitch(true);
    }
    else if (this.responseText == "false"){
      setSwitch(false);
    }
  }
  };
  xhttp.open("GET", "updateRelay", true);
  xhttp.send();
}

function onClickRelaySwtich(){
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
      setSwitch(true);
    }
    else if (this.responseText == "false"){
      setSwitch(false);
    }
  }
  };
  xhttp.open("GET", "relayToggle", true);
  xhttp.send();
}