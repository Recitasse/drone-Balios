
let toggle = document.getElementById("all_exp");
let sonar = document.getElementById("sonar_val");
let gps = document.getElementById("GPS_val");
let cam = document.getElementById("camera_val");

toggle.addEventListener("click", function() {
  if (sonar.disabled) {
    sonar.disabled = false;
    gps.disabled = false;
    cam.disabled = false;
  } else {
    sonar.disabled = true;
    gps.disabled = true;
    cam.disabled = true;
  }
});


let toggle1 = document.getElementById("deco_all");
let joy = document.getElementById("Joystick_co");
let son = document.getElementById("Sonar_co");
let gps_c = document.getElementById("GPS_co");
let cam_c = document.getElementById("Camera_co");
let HC = document.getElementById("Module_H");
let Phare = document.getElementById("Phare");
let Rout = document.getElementById("Routeur");
let mysql_c = document.getElementById("MySQL");
let ap = document.getElementById("Apache2");
let ard = document.getElementById("Arduino");

toggle1.addEventListener("click", function() {
  if (joy.disabled) {
    joy.disabled = false;
    son.disabled = false;
    gps_c.disabled = false;
    cam_c.disabled = false;
    HC.disabled = false;
    Phare.disabled = false;
    Rout.disabled = false;
    mysql_c.disabled = false;
    ap.disabled = false;
    ard.disabled = false;
  } else {
    joy.disabled = true;
    son.disabled = true;
    gps_c.disabled = true;
    cam_c.disabled = true;
    HC.disabled = true;
    Phare.disabled = true;
    Rout.disabled = true;
    mysql_c.disabled = true;
    ap.disabled = true;
    ard.disabled = true;
  }
});
  
  
  setInterval(function() {
    var image1 = document.getElementById("war1");
    var image2 = document.getElementById("war2");
    
    if (image1.style.visibility === "hidden") {
      image1.style.visibility = "visible";
      image2.style.visibility = "visible";
    } else {
      image1.style.visibility = "hidden";
      image2.style.visibility = "hidden";
    }
  }, 750);
  
