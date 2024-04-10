const loginElement = document.querySelector('#login-form');
const contentElement = document.querySelector("#content-sign-in");
const userDetailsElement = document.querySelector('#user-details');
const authBarElement = document.querySelector("#authentication-bar");

// Elements for sensor readings
const tempElement = document.getElementById("temperatura");
const phElement = document.getElementById("pH");


// MANAGE LOGIN/LOGOUT UI
const setupUI = (user) => {
  if (user) {
    //toggle UI elements
    loginElement.style.display = 'none';
    contentElement.style.display = 'block';
    authBarElement.style.display ='block';
    userDetailsElement.style.display ='block';
    userDetailsElement.innerHTML = user.email;

    // get user UID to get data from database
    var uid = user.uid;
    console.log(uid);

    // Database paths (with user UID)
    var dbPathTemp =   '/temperatura';
    var dbPathPh =  '/pH';
    

    // Database references
    var dbRefTemp = firebase.database().ref().child(dbPathTemp);
    var dbRefPh = firebase.database().ref().child(dbPathPh);
    

    // Update page with new readings
    dbRefTemp.on('value', snap => {
      tempElement.innerText = snap.val().toFixed(2);
    });

    dbRefPh.on('value', snap => {
      phElement.innerText = snap.val().toFixed(2);
    });

    

  // if user is logged out
  } else{
    // toggle UI elements
    loginElement.style.display = 'block';
    authBarElement.style.display ='none';
    userDetailsElement.style.display ='none';
    contentElement.style.display = 'none';
  }
}