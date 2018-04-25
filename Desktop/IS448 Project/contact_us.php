<?php
// Fill up array with names
//Program extracts parameter-value from query and looks to see if value is already in the array
//if value is already in array, program echoes 'taken' as the response
//if value does not exist in array, program echoes 'available' as the response
$arr[]="AL";
$arr[]="AK";
$arr[]="AZ";
$arr[]="AR";
$arr[]="CA";
$arr[]="CO";
$arr[]="CT";
$arr[]="DE";
$arr[]="DC";
$arr[]="FL";
$arr[]="GA";
$arr[]="HI";
$arr[]="ID";
$arr[]="IL";
$arr[]="IN";
$arr[]="IA";
$arr[]="KS";
$arr[]="KY";
$arr[]="LA";
$arr[]="ME";
$arr[]="MD";
$arr[]="MA";
$arr[]="MI";
$arr[]="MN";
$arr[]="MS";
$arr[]="MO";
$arr[]="MT";
$arr[]="NE";
$arr[]="NV";
$arr[]="NH";
$arr[]="NJ";
$arr[]="NM";
$arr[]="NY";
$arr[]="NC";
$arr[]="ND";
$arr[]="OH";
$arr[]="OK";
$arr[]="OR";
$arr[]="PA";
$arr[]="RI";
$arr[]="SC";
$arr[]="SD";
$arr[]="TN";
$arr[]="TX";
$arr[]="UT";
$arr[]="VT";
$arr[]="VA";
$arr[]="WA";
$arr[]="WV";
$arr[]="WI";
$arr[]="WY";
#retrieve value of parameter by name 'username' and store the value in the local variable $q
$q=$_GET["name"];

if (in_array($q,$arr)) 
{
	$response="Valid State";
}
else{
	$response = "Not Valid State";
}
echo $response;


?>