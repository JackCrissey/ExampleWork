//confirmation message
function display_verify_message(){
//If any of the fields are empty, you should alert the user to the problem and ask the user to
//fill the respective text box. You must point the user to the specific text box they left empty,
//by setting the focus and selecting the empty text box

  var name = document.getElementById("user").value;
  var pass= document.getElementById("password").value;

  var statement =  true;

  if (name == "" ){
    alert("empty box please fill boxes");
    name.focus();
    statement = false;
  }
  else if (pass == "" ) {
    alert("empty box please fill boxes");
    pass.focus();
    statement = false;
  }



  var pass = document.getElementById("password").value;

  if (pass != ajax.responseText){
    alert("Your username or password is incorrect");
    pass.focus();
    statement = false;
  }

//if all things are true and runs perfectly
  if (statement == true) {
    alert("Thank you. You've signed in successfully");
  
  }
}






function contactUs(name){
  new Ajax.Request("login.php",
  {
    method:"get",
    parameters: {name: name},
    onSuccess:displayResult
} );
}







function displayResult(ajax) {
  var answer = (ajax.responseText);
  var pass = document.getElementById("password").value;//password from the database
  if(answer == pass){
    alert("You have successfully logged in")
  } else {
    alert("Your username or password is incorrect")
  }
  
}







