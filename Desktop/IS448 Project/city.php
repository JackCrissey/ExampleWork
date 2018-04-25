<?php
// Fill up array with names
//Program extracts parameter-value from query and looks to see if value is already in the array
//if value is already in array, program echoes 'taken' as the response
//if value does not exist in array, program echoes 'available' as the response
$arr[]="Bethesda";
$arr[]="Baltimore";
$arr[]="Catonsville";
$arr[]="Arbutus";
$arr[]="Rockville";
$arr[]="Arlington";
$arr[]="Gaithersburg";
$arr[]="Germantown";
$arr[]="Potomac";
$arr[]="Frederick";
$arr[]="Olney";
$arr[]="Fairifac";
$arr[]="Centreville";
$arr[]="Owens Mill";
$arr[]="Columbia";
$arr[]="Belair";
$arr[]="Rehobeth";
$arr[]="Annapolis";
$arr[]="College Park";
$arr[]="Laurel";
$arr[]="Hagerstown";
$arr[]="Pasadina";
$arr[]="North Bethesda";
$arr[]="Montgomery Villege";
$arr[]="Boyds";
$arr[]="Poolsville";
$arr[]="Damascus";
$arr[]="Ellicott City";
$arr[]="Jessup";
$arr[]="Hanover";
$arr[]="Severn";
$arr[]="Odenton";
$arr[]="Crofton";
$arr[]="Arnold";
$arr[]="Severna Park";
$arr[]="Glenarden";
$arr[]="Silver Spring";
$arr[]="Takoma Park";
$arr[]="Chevy Chase";
$arr[]="Cabin John";
$arr[]="Derwood";
$arr[]="Hancock";
$arr[]="Summit Point";
$arr[]="Sterling";
$arr[]="Reston";
$arr[]="Vienna";
$arr[]="Falls Church";
$arr[]="Oakton";
$arr[]="Burke";
$arr[]="Alexandria";
$arr[]="Springfield";
//get the q parameter from URL
$tag=$_GET["city"];


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