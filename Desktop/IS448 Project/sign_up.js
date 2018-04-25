function usernameAvail(username){
	if (username.length==0)
	{ 
		$("usernameValidity").innerHTML="";
     	return;
  	}
  	
  	new Ajax.Request( "username.php",
  	{
  		method: "get",
  		parameters: {avail:username},
  		onSuccess: usernameSuccess
  	});
}

function usernameSuccess(ajax){
	var responce = ajax.responseText;
  var username = document.getElementById("username").value;
	if(responce == username){
    $("usernameValidity").innerHTML="This username is not availiable";
  } else {
    $("usernameValidity").innerHTML="This username is availiable";
  }
}

function statusHelp(status){
  if (status.length==0)
  { 
    $("statusHelp").innerHTML="";
      return;
    }
    
    new Ajax.Request( "status.php",
    {
      method: "get",
      parameters: {status:status},
      onSuccess: statusSuccess
    });
}

function statusSuccess(ajax){
  var responce = ajax.responseText;
  $("statusHelp").innerHTML=responce;
}

function cityHelp(city){
  if (city.length==0)
  { 
    $("cityHelp").innerHTML="";
      return;
    }
    
    new Ajax.Request( "city.php",
    {
      method: "get",
      parameters: {city:city},
      onSuccess: citySuccess
    });
}

function citySuccess(ajax){
  var responce = ajax.responseText;
  $("cityHelp").innerHTML=responce;
}

function stateHelp(state){
  if (state.length==0)
  { 
    $("stateHelp").innerHTML="";
      return;
    }
    
    new Ajax.Request( "state.php",
    {
      method: "get",
      parameters: {state:state},
      onSuccess: stateSuccess
    });
}

function stateSuccess(ajax){
  var responce = ajax.responseText;
  $("stateHelp").innerHTML=responce;
}

function yearHelp(year){
  if (year.length==0)
  { 
    $("yearHelp").innerHTML="";
      return;
    }
    
    new Ajax.Request( "year.php",
    {
      method: "get",
      parameters: {year:year},
      onSuccess: yearSuccess
    });
}

function yearSuccess(ajax){
  var responce = ajax.responseText;
  $("yearHelp").innerHTML=responce;
}

function usernameFormat(username){
  if(!username == ""){
    if(username.search(/\s/)>=0){
      alert("The username you entered is an invalid formate. It can't have any whitespaces");
    }
  }
}

function passwordFormate(password){
  if(!password == ""){
    if(password.search(/[A-Z]/)<0 || password.search(/\d/)<0 || password.search(/\s/)>=0){
      alert("Password isn't valid you need at least one Capital letter, a number, and no whitespaces");
    }
  }
}

function studentYearFormate(year){
  if(!year == ""){
    var lowerYear = year.toLowerCase();
    if(lowerYear == "freshman" || lowerYear == "sophomore" || lowerYear == "junior" || lowerYear == "senior" || lowerYear == "staff"){

    } else {
     alert("Year needs to be freshman, sophomore, junior, senior, or staff");
    }
  }
}

function schoolIdFormate(schoolId)
{
  if(!schoolId == ""){
    var idPattern = /[A-Za-z]{2}\d{5}/;
    if(!idPattern.test(schoolId)){
      alert("School Id is not in the right format the correct formate is AA99999, 2 letters and 5 numbers.");
    }
  }
}

function permitFormate(permit){
  if(!permit == ""){
    var permitPattern = /\d{2}[-]\d{5}/;
    if(!permitPattern.test(permit)){
      alert("Parking Permit is not in the right format the correct formate is XX-XXXXX 2 numbers a dash and 5 numbers");
    }
  }
}






