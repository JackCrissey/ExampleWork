<?php
	#connect to mysql database


	$db = mysqli_connect("studentdb-maria.gl.umbc.edu","plee6","plee6","plee6");

	if (mysqli_connect_errno())
		exit("Error - could not connect to MySQL");

	



$commentname = htmlspecialchars($_GET["avail"]);
$username = mysqli_real_escape_string($db, $commentname);

//$constructed_query = "insert into createAccount (username, password)
//values ('$commentname', '$commentpassword')";
 
$test= "select username from createAccount where createAccount.username = '$username'";

$result = mysqli_query($db, $test);

echo $result->fetch_object()->username;



//$mysql = mysql_query($db, $sql);

?>