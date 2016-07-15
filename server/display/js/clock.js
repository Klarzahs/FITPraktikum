function checkTime(i) {
	if (i < 10) {i = "0" + i};  // add "0"
	return i;
}

function startTime() {
	var today = new Date();
	
	var monthNames = ["January", "February", "March", "April", "May", "June",
					"July", "August", "September", "October", "November", "December"];

	var weekday = ["Sunday","Monday","Tuesday",
				   "Wednesday","Thursday","Friday","Saturday"];

	var y = today.getFullYear();
	var mo = today.getMonth();
	var date = today.getDate();
	var wd = today.getDay();
	var h = today.getHours();
	var min = today.getMinutes();
	var s = today.getSeconds();
	min = checkTime(min);
	s = checkTime(s);
	//[<span class=\"bold\">]mm[</span>]
	document.getElementById('clock').innerHTML = h + ":" + min + "<span class=\"seconds\">"+s+"</span>"
	
	document.getElementById('day').innerHTML = weekday[wd]+", "+date+" "+monthNames[mo]+" "+y;
	//document.getElementById('clock').innerHTML = h + ":" + min + ":" + s;
	var t = setTimeout(startTime, 500);
}
window.onload = startTime;

