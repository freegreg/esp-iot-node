function addTimer(){
// Find a <table> element with id="myTable":
var tableTimers = document.getElementById("timersTable");

// Create an empty <tr> element and add it to the 1st position of the table:
var row = tableTimers.insertRow(0);

//Get info for new timer
var timerEnable = document.getElementById("hours");
var time = document.getElementById("time").cloneNode(true);
var timerAction = document.getElementById("hours");

// Insert new cells (<td> elements) at the 1st and 2nd position of the "new" <tr> element:
var inputEnable = document.createElement("input");                 // Create input
inputEnable.setAttribute("class", "w3-check");
inputEnable.setAttribute("type", "checkbox");
inputEnable.checked = true;

// Get days
var periodEveryday = document.getElementById("Everyday");
var periodToday = document.getElementById("Only Today");
var periodTomorrow = document.getElementById("Only Tomorrow");
var periodMonday = document.getElementById("Monday");
var periodTuesday = document.getElementById("Tuesday");
var periodWednesday = document.getElementById("Wednesday");
var periodThursday = document.getElementById("Thursday");
var periodFriday = document.getElementById("Friday");
var periodSaturday = document.getElementById("Saturday");
var periodSunday = document.getElementById("Sunday");

//Get action
var action = document.getElementById("option");
var actionOption = action.cloneNode(true);
actionOption.selectedIndex = action.selectedIndex

var cellEnable	= row.insertCell(0);
var cellDate 	= row.insertCell(1);
var cellTime 	= row.insertCell(2);
var cellAction 	= row.insertCell(3);

// Add some text to the new cells:
cellEnable.appendChild(inputEnable);
cellDate.innerHTML 		= "24/02/2017";
cellTime.appendChild(time);
cellAction.appendChild(actionOption);
}
function changedTimer(){
	
}

