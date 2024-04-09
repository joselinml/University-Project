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
    // Mostrar elementos de la interfaz
    loginElement.style.display = 'none';
    contentElement.style.display = 'block';
    authBarElement.style.display ='block';
    userDetailsElement.style.display ='block';
    userDetailsElement.innerHTML = user.email;

    var uid = user.uid;
    console.log(uid);

    var dbPathTemp =  uid.toString() + '/temperatura';
    var dbPathPh =  uid.toString() + '/pH';
    // Database references
   var dbRefTemp = firebase.database().ref().child(dbPathTemp);
    var dbRefPh = firebase.database().ref().child(dbPathPh);
   


    // Actualizar la página con las nuevas lecturas de temperatura
    dbRefTemp.on('value', snap => {
      tempElement.innerText = snap.val().toFixed(2);
    });

    // Actualizar la página con las nuevas lecturas de pH
    dbRefPh.on('value', snap => {
      phElement.innerText = snap.val().toFixed(2);
    });

  } else {
    // Ocultar elementos de la interfaz si el usuario no está autenticado
    loginElement.style.display = 'block';
    authBarElement.style.display ='none';
    userDetailsElement.style.display ='none';
    contentElement.style.display = 'none';
  }
}
