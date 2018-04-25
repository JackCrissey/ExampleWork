<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns = "http://www.w3.org/1999/xhtml">
<head>
	<title> &#128664; &#128054; Sign Up </title>
	<link rel="stylesheet" href="sign_up.css" type="text/css"/>
	<script type="text/javascript" src="sign_up.js"> </script>
	<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/prototype/1.6.0.3/prototype.js"></script>
</head>
<body>
	<?php
	#connect to mysql database


	$db = mysqli_connect("studentdb-maria.gl.umbc.edu","plee6","plee6","plee6");

	if (mysqli_connect_errno())
		exit("Error - could not connect to MySQL");

	



	$username = htmlspecialchars($_POST["username"]);
	$password = htmlspecialchars($_POST["password"]);
	$curStatus = htmlspecialchars($_POST["curStatus"]);
	$city = htmlspecialchars($_POST["city"]);
	$state = htmlspecialchars($_POST["state"]);
	$studentYear = htmlspecialchars($_POST["studentYear"]);
	$schoolId = htmlspecialchars($_POST["schoolId"]);
	$permitNum = htmlspecialchars($_POST["permitNum"]);
	$email = htmlspecialchars($_POST["email"]);

	$username = mysqli_real_escape_string($db, $username);
	$password = mysqli_real_escape_string($db, $password);
	$curStatus = mysqli_real_escape_string($db, $curStatus);
	$city = mysqli_real_escape_string($db, $city);
	$state = mysqli_real_escape_string($db, $state);
	$studentYear = mysqli_real_escape_string($db, $studentYear);
	$schoolId = mysqli_real_escape_string($db, $schoolId);
	$permitNum = mysqli_real_escape_string($db, $permitNum);
	$email = mysqli_real_escape_string($db, $email);
 
	$insertQuery = "insert into createAccount (studentId, username, password, studentyear, permitnumber,
		email, currentstat, city, state) values('$schoolId','$username','$password',
		'$studentYear','$permitNum','$email','$curStatus','$city', '$state')";

	$result = mysqli_query($db, $insertQuery);


	//$mysql = mysql_query($db, $sql);

	?>
<p class="header">
	<a class = "title" href = "Home.html">iPark</a>
	<a href = "Home.html"><img class = "dogcar" src="https://swe.umbc.edu/~crissey1/448images/car.png" alt="dogcar"/></a>
	<a class = "icons" href = "http://www.umbc.edu"><img class = "icons" src="https://swe.umbc.edu/~crissey1/448images/UMBC_logo.jpg" alt="UMBC"/></a>
	<a class = "icons" href = "https://twitter.com"><img class = "icons" src="https://swe.umbc.edu/~crissey1/448images/Twitter_Icon.png" alt="twitter"/></a>
	<a class = "icons" href = "https://www.facebook.com"><img class = "icons" src="https://swe.umbc.edu/~crissey1/448images/facebook_icon.png" alt="facebook"/></a>
</p>
<ul class="top_list">
	<li class="top"><a class = "top_link" href = "Visitor_Parking.html">Visitor Map</a></li>
	<li class="top"><a class = "top_link" href = "Staff.html">Staff Map</a></li>
	<li class="top"><a class = "top_link" href = "RMap.html">Resident Map</a></li>
	<li class="top"><a class = "top_link" href = "CMap.html">Commuter Map</a></li>
	<li class="top_selected" style="float:right"><a class = "top_link" href = "login.html">Login</a></li>
	<li class="top" style="float:right"><a class = "top_link" href = "contact_us.html">Contact Us</a></li>
	<li class="top" style="float:right"><a class = "top_link" href = "about_us.html">About Us</a></li>
</ul>

<div class = "parking">
	<div class = "main_textbox">
		<h1 style="text-align:center; font-size:30pt;">Sign-Up</h1>
		<form method = "POST" action = "sign_up.php" class=box>
			<p>
				Thanks for signing up <?php echo $_POST["username"] ?>! We will update you on changes to the website and
				parking changes at the school due to events and closures.
			</p>
		</form>
	</div>
</div>


<div class="bottom_list_all">
	<ul class = "bottom_list">
		<li class = "list_header">About Us</li>
		<li class = "bottom_banner"><a class = "footer" href = "about_us.html">About Us</a></li>
		<li class = "bottom_banner"><a class = "footer" href = "contact_us.html">Contact Us</a></li>
		<li class = "bottom_banner"> </li>
	</ul>
	<ul class = "bottom_list">
		<li class = "list_header">UMBC Links</li>
		<li class = "bottom_banner"><a class = "footer" href = "http://www.umbc.edu">Home</a></li>
		<li class = "bottom_banner"><a class = "footer" href = "http://news.umbc.edu">News and Events</a></li>
		<li class = "bottom_banner"><a class = "footer" href = "http://about.umbc.edu/visitors-guide/directions/">Directions</a></li>
	</ul>
	<ul class = "bottom_list">
		<li class = "list_header">UMBC Parking</li>
		<li class = "bottom_banner"><a class = "footer" href = "http://parking.umbc.edu">Home</a></li>
		<li class = "bottom_banner"><a class = "footer" href = "https://umbc.t2hosted.com/Account/Portal">Get a Permit</a></li>
		<li class = "bottom_banner"><a class = "footer" href = "http://parking.umbc.edu/visitor-parking/">Visitors</a></li>
		<li class = "bottom_banner"><a class = "footer" href = "http://parking.umbc.edu/citations-3/">Citations</a></li>
	</ul>
</div>
</body>
</html>

