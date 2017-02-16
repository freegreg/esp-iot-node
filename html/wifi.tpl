<!DOCTYPE html>
<html>
<head>
<title>WiFi connection</title>
<link rel="stylesheet" href="./css/normalize.css">
<link rel="stylesheet" href="./css/skeleton.css">
<link rel="stylesheet" type="text/css" href="./css/style.css">
<link rel="stylesheet" href="./css/custom.css">

  <!-- Favicon
  –––––––––––––––––––––––––––––––––––––––––––––––––– -->
<link rel="icon" type="image/png" href="./images/favicon.png">

<script type="text/javascript" src="./script/140medley.min.js"></script>
<script type="text/javascript">

var xhr=j();
var currAp="%currSsid%";

function createInputForAp(ap) {
	if (ap.essid=="" && ap.rssi==0) return;
	var tr=document.createElement("tr");
	tr.id="aptr";

	var td_rssi=document.createElement("td");
	var rssi=document.createElement("div");
	td_rssi.appendChild(rssi);
	var rssiVal=-Math.floor(ap.rssi/51)*32;
	rssi.className="icon";
	rssi.style.backgroundPosition="0px "+rssiVal+"px";

	var td_encrypt=document.createElement("td");
	var encrypt=document.createElement("div");
	td_encrypt.appendChild(encrypt);
	var encVal="-64"; //assume wpa/wpa2
	if (ap.enc=="0") encVal="0"; //open
	if (ap.enc=="1") encVal="-32"; //wep
	encrypt.className="icon";
	encrypt.style.backgroundPosition="-32px "+encVal+"px";

	var td_input=document.createElement("td");
	var input=document.createElement("input");
	td_input.appendChild(input);
	input.type="radio";
	input.name="essid";
	input.value=ap.essid;
	if (currAp==ap.essid) input.checked="1";
	input.id="opt-"+ap.essid;

	var td_label=document.createElement("td");
	var label=document.createElement("label");
	td_label.appendChild(label);
	label.htmlFor="opt-"+ap.essid;
	label.textContent=ap.essid;

	tr.appendChild(td_input);
	tr.appendChild(td_label);
	tr.appendChild(td_rssi);
	tr.appendChild(td_encrypt);
	return tr;
}

function getSelectedEssid() {
	var e=document.forms.wifiform.elements;
	for (var i=0; i<e.length; i++) {
		if (e[i].type=="radio" && e[i].checked) return e[i].value;
	}
	return currAp;
}


function scanAPs() {
	xhr.open("GET", "wifiscan.cgi");
	xhr.onreadystatechange=function() {
		if (xhr.readyState==4 && xhr.status>=200 && xhr.status<300) {
			var data=JSON.parse(xhr.responseText);
			currAp=getSelectedEssid();
			if (data.result.inProgress=="0" && data.result.APs.length>1) {
				$("#aps").innerHTML="";
				for (var i=0; i<data.result.APs.length; i++) {
					if (data.result.APs[i].essid=="" && data.result.APs[i].rssi==0) continue;
					$("#aps").appendChild(createInputForAp(data.result.APs[i]));
				}
				window.setTimeout(scanAPs, 20000);
			} else {
				window.setTimeout(scanAPs, 1000);
			}
		}
	}
	xhr.send();
}


window.onload=function(e) {
	scanAPs();
};
</script>
</head>
<body>

<!--HEADER-->
<header>
  <div class="container">
    <div class="row">
      <div class="twelve columns">
        <nav>
          <ul>
            <li><a href="#">About</a></li>
            <li><a href="wifi">Relay Control</a></li>
            <li><a href="index.html">WiFi Control</a></li>
          </ul>
        </nav>  
      </div> 
    </div>

    <div class="row">    
      <div class="twelve columns">
        <h1>- Design What You Imagine -</h1>
        <h4>Phasellus ullamcorper ipsum rutrum nunc. Nunc nonummy metus. Vestibulum volutpat pretium libero. Cras id dui.</h4>
        <a href="#" class="btn">Hire me</a> 
      </div>
    </div>
   </div><!--end of .container-->
</header>

<div class="section main">
	<div class="container">
		<div class="row">
			<div class="one-half column">
				<p>Current WiFi mode: %WiFiMode%</p>
			</div> 
			<div class="one-half column">
				<p>Note: %WiFiapwarn%</p>
			</div> 
		</div> 
	<div/>
<div/>
<div class="section wifis">
	<div class="container">	
		<div class="row">
			<p>To connect to a WiFi network, please select one of the detected networks...<br></p>	
				<form name="wifiform" action="connect.cgi" method="post">  
				<table class="u-full-width">
					<thead>
    					<tr>
        					<th>Select</th>
    						<th>Name (SSID)</th>
      						<th>Power (RSSI)</th>
      						<th>Security</th>
    					</tr>
  					</thead>
  					<tbody  id="aps">
  						Scanning...
  					</tbody>
				</table>
   		</div>
 	</div>
</div>
<div class="section log-input">
	<div class="container">	
		<div class="row">
			 <label for="wifiPass">WiFi password, if applicable: </label>
      		<input type="text" placeholder="Password" id="wifiPass" val="%WiFiPasswd%"><br>
			<input type="submit" class="button-primary" name="connect" value="Connect!">
   		</div>
 	</div>
</div>
</body>
</html>