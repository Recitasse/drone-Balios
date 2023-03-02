<?php

session_start();

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

?>
<!DOCTYPE html> 
<html lang='fr'>
<head>
   <meta charset="UTF-8"/>
   <title>SERVER DRONEBALIOS</title>
   <link rel="stylesheet" href="styles.css">
   <link rel="shortcut icon" type="image/x-icon" href="bateau_ico.ico">
   <script type="text/javascript" src="script.js"></script>
</head>
<body>

<h1><u>CENTRE ADMIN BALIOS</u></h1>

<div id="boatContainer">
  <div id="boat"></div>
</div>
<center>
<i>Bienvennue sur le centre de Contrôle du drone Balios <b>v.1.0</b>.</i><br>
<div class="title_board">

<div class="demarrage">
<?php
if(isset($_SESSION) && !empty($_SESSION))
{
  // Session prête mais non initialisée
  if($_SESSION['pret'] == 1)
  {
  ?>
  <div class="session" id="ss1">
    <p>Session <?=$_SESSION['dbname'];?> du <?=$_SESSION['date'];?>.</p>
  </div>
  <?php
  }
  elseif($_SESSION['pret'] == 2)
  {
  ?>
  <div class="session" id="ss2">
    <p>Session <?=$_SESSION['dbname'];?> ERREUR</p>
  </div>
  <?php
  }
  elseif($_SESSION['pret'] == 3)
  {
  ?>
  <div class="session" id="ss3">
    <p>Session <?=$_SESSION['dbname'];?> ATTENTION</p>
  </div>
  <?php
  }
  elseif($_SESSION['pret'] == 4)
  {
  ?>
  <div class="session" id="ss4">
    <p>Session <?=$_SESSION['dbname'];?> active</p>
  </div>
  <?php
  }
}
else
{
  ?>
    <div class="session" id="ss0">
      <p>Aucune session active</p>
    </div>
  <?php
}

if(isset($_GET['err']) && !empty($_GET['err'])) {
  if($_GET['err'] == 'db') {
  ?>
  <p style="margin-left: 20px; color:red; font-weight: bold;">Erreur, impossible de se connecter à la base de donnée.</p>
  <?php
  }
}
?>

<?php
if(isset($_SESSION) && !empty($_SESSION))
{
  $nom = "Arrêter la session '".$_SESSION['dbname']."'";
  ?>
     <button id="ss"><?php echo $nom; ?></button>
          <script>
       document.getElementById("ss").addEventListener("click", function() {
    window.location.href = "Includes/stop_session.php";
  });
     </script>
  <?php
}
else
{
  ?>
     <button id="ns">Nouvelle session</button>
     <script>
  document.getElementById("ns").addEventListener("click", function() {
    window.location.href = "Includes/new_session.php";
  });
  </script>
     <button id="cs">Charger session</button>
     <script>
  document.getElementById("cs").addEventListener("click", function() {
    window.location.href = "Includes/charger_session.php";
  });
  </script>
</div>
<?php
}
if(isset($_SESSION) && !empty($_SESSION))
{
include "Includes/initialiseur.php";
}
?>

<br>

<details>
<summary class="title" style="border-top: 1px solid black;">MODE D'EMPLOI</summary>

<div class="image_center">
<img src="bateau.jpg" class="image_desc" alt="Image d'un bateau">
<span class="dot">* </span><i class="description">Image d'un bateau </i><span class="dot">*</span>
</div>

<div class="text">
<h3>Avant propos</h3>
<p>On fait un test</p>
</div>
</details>

<details>
<summary class="title">PARAMÈTRES DRONE</summary>
<p>Test</p>
</details>


<details>
<summary class="title">LECTURE DES DONNÉES</summary>
<p>Test</p>
</details>
</div>

</div>
</body>
</html>

<script>
const boat = document.querySelector("#boat");

let left = 0;
let angle = 0;
var cond = 1;

setInterval(() => {
  left += 2;
  angle += cond*1;
  if (left > 500) {
    left = 0;
  }
  if (angle > 15) {
     cond = -1
  };
  if (angle <-10) {
     cond = 1;
  };
  
  boat.style.left = `${left}px`;
  boat.style.transform = `rotate(${angle}deg)`;
}, 50);
</script>


