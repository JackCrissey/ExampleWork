<?php
	#connect to mysql database


	$db = mysqli_connect("studentdb-maria.gl.umbc.edu","plee6","plee6","plee6");

	if (mysqli_connect_errno())
		exit("Error - could not connect to MySQL");

	#get the parameter from the HTML form that this PHP program is connected to
	#since data from the form is sent by the HTTP POST action, use the $_POST array here

	
/*secures it from injection*/
//------------------------------------------------------------------------------------------------------------------------
/*$commentname = htmlspecialchars($_POST['name']);
$commentpassword = htmlspecialchars($_POST['password']);

$commentname = mysqli_real_escape_string($db, $commentname);
$commentpassword = mysqli_real_escape_string($db, $commentpassword);
*/
//-------------------------------------------------------------------------------------------------------------------------


//	$commentname = $_POST['username'];
//	$commentpassword = $_POST['password'];



$commentname = htmlspecialchars($_GET["name"]);
$username = mysqli_real_escape_string($db, $commentname);

//$constructed_query = "insert into createAccount (username, password)
//values ('$commentname', '$commentpassword')";
 
$test= "select password from createAccount where createAccount.username ='$username'";

$result = mysqli_query($db, $test);

echo $result->fetch_object()->password;



//$mysql = mysql_query($db, $sql);

?>