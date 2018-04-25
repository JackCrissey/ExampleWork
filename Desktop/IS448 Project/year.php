<?php
// Fill up array with names
//Program extracts parameter-value from query and looks to see if value is already in the array
//if value is already in array, program echoes 'taken' as the response
//if value does not exist in array, program echoes 'available' as the response
$arr[]="Freshman";
$arr[]="Sophomore";
$arr[]="Junior";
$arr[]="Senior";
$arr[]="Staff";
//get the q parameter from URL
$tag=$_GET["year"];


if (strlen($tag) > 0)
{
  $hint="";
  for($i=0; $i<count($arr); $i++)
  {
  if (strtolower($tag)==strtolower(substr($arr[$i],0,strlen($tag))))
    {
    if ($hint=="")
      {
         $hint=$arr[$i];
      }
    else
      {
         $hint=$hint.", ".$arr[$i];
      }
    }
  }
}

if ($hint == "")
{
   $response="no suggestion";
}
else
{
   $response=$hint;
}

echo $response;
?>