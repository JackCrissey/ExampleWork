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
//get the q parameter from URL
$tag=$_GET["state"];


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