//the onclick event handler
//text filled box
/*
function myGreeting(){
  document.getElementById("fullName").value = "Please enter your Full Name";
  document.getElementById("streetName").value = "Please enter your Street Address";
  document.getElementById("cityName").value = "Please enter your City";
  document.getElementById("stateName").value = "Please enter your State";
  document.getElementById("zipcodeNum").value = "Please enter your Zipcode";
  document.getElementById("statusName").value;
  document.getElementById("phoneNumber").value = "Please enter your Phone Number";
  document.getElementById("email").value = "Please enter your Email"; 

}*/
//confirmation message
function display_verify_message(){
//If any of the fields are empty, you should alert the user to the problem and ask the user to
//fill the respective text box. You must point the user to the specific text box they left empty,
//by setting the focus and selecting the empty text box

  var fullName = document.getElementById("fullName").value;
  var streetName = document.getElementById("streetName").value;
  var cityName = document.getElementById("cityName").value;
  var stateName = document.getElementById("stateName").value;
  var statusName = document.getElementById("statusName").value;
  var phoneNumber = document.getElementById("phoneNumber").value;
  var email = document.getElementById("email").value;
  var zipcode =document.getElementById("zipcodeNum").value;

  var statement =  true;

  if (fullName == "" ){
    alert("empty box please fill boxes");
    fullName.focus();
    statement = false;
  }
  else if (streetName == "" ) {
    alert("empty box please fill boxes");
    streetName.focus();
    statement = false;
  }
  else if (cityName == "" ) {
    alert("empty box please fill boxes");
    cityName.focus();
    statement = false;
  }
  else if (stateName == "" ) {
    alert("empty box please fill boxes");
    stateName.focus();
    statement = false;
  }
  else if (statusName == "Please choose one of the following" ) {
    alert("please select your status");
    statusName.focus();
    statement = false;
  }
  else if (phoneNumber == "" ) {
    alert("empty box please fill boxes");
    phoneNumber.focus();
    statement = false;
  }
  else if (email == "" ) {
    alert("empty box please fill boxes");
    email.focus();
    statement = false;
  }



//If user enters a number in the text box for their name, you should display an error
//message and ask the user to re-enter their name. You must bring the focus to the name
//text box.
  var properName = document.getElementById("fullName").value;
  properName.search(/\d/);
  if(properName.search(/\d/) >= 0 || statement == false){
    alert("Please re-enter your name");
    properName.focus();
    statement = false;
  }


//Verify that the street address begins with a number. If not, display an error message and
//bring focus to the street address field
  var streetNum = document.getElementById("streetName").value;
  var numStreet = streetNum.search(/^\d/);

  if (numStreet) {
    alert("Number must be first for Street Address");
    streetNum.focus();
    statement = false;
  }

//Verify that the user only submits the following values for the state: MD, DC or VA. Display
//an error message and ask the user to re-type the state. Bring focus to the field

//function findState(){
  var StateFind = document.getElementById("stateName").value;
  var properState = StateFind.search(/\d/);
  if(!properState){
  	alert("re-type state");
  	StateFind.focus();
    statement = false;
	}

//ZIPCODE HERE
  var zipcode = document.getElementById("zipcodeNum").value;
  var ZC = zipcode.search(/^\d/);
  if(ZC){
  	alert("re-type zipcode");
  	ZC.focus();
    
 	}


//For the email address text box, check that the email address has the ‘@’ symbol, which
//indicates that the email address is a legitimate email address. Also verify that there is a ‘.’
//in the email address after the ‘@’ symbol for further validation. Again, if the email address 
//is entered incorrectly, ask the user to re-enter the email address and bring focus to the
//email text box.
  //var myEmail = document.getElementById("email").value;
  var myEmail = /\w+\@\w+\.\w+/;
  var tempEmail = myEmail.test(email);
  if(!tempEmail){
    alert("re-enter email address");
    statement = false;
  } 






//For the phone number, check that the user is entering the phone number in the following
//format: ‘(xxx)xxx-xxxx’. If not, ask the user to re-enter the phone number and bring focus
//to the phone text box.
  var phonePattern = /\d{3}\d{3}\d{4}/; 
  var PP1 = /\(\d{3}\)\d{3}-\d{4}/;
  var PP2 = /\d{3}-\d{3}-\d{4}/;
  var ok1 = PP1.test(phoneNumber);
  var ok = phonePattern.test(phoneNumber);
  //var ok1 = PP1.test(phoneNumber);
  var ok2 = PP2.test(phoneNumber);

  if (ok || ok1 || ok2){
  	statement = true;
  }
  else{
    alert("invalid phone number.");
    ok.focus();
    statement = false;
}

//if all things are true and runs perfectly
  if (statement == true) {
    alert("Thank you. We will contact you with additional information");
  

  var reply = confirm("This is the info you entered." + 
  "\nFull name: "+ fullName +
  "\nStreet Address: "+ streetName +
  "\nCity: "+ cityName +
  "\nState: "+ stateName +
  "\nCounty: "+ statusName + 
  "\nPhone Number: "+ phoneNumber + 
  "\nZipcode: "+ zipcode +
  "\nEmail Address: "+ email);
  }
}

function contactUs(myState){

  new Ajax.Request("contact_us.php",
  {
    method:"get",
    parameters: {name: myState},
    onSuccess:displayResult
} );
}


function displayResult(ajax) {
  $("msgbox").innerHTML = ajax.responseText;
}

