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
   <link rel="stylesheet" href="../styles.css">
   <link rel="shortcut icon" type="image/x-icon" href="../bateau_ico.ico">
</head>
<body>


<h1>ARRÊTER LA SESSION</h1>
<h2>MODOP L'ARRÊT DE LA SESSION</h2>
<p>L'arrêt de la session permet de se déconnecter de la base de donnée sur laquelle vous travaillez. Cette opération permet d'arrêter le drône. </p>


<center>
<span style="font-size: 20px; font-weight: bold; color:red;">
<img id="war1" src="../attention.png" alt="Attention" class="warning" >
N'ARRÊTEZ PAS LE DRONE EN SERVICE
<img id="war2" src="../attention.png" alt="Attention" class="warning">
</span>
</center>


<p>Vous risquez de ne pouvoir ramener le drône s'il est encore en opération.</p>
<p>Pour ce qui est de l'arrêt de la session vous avez plusieurs paramètres:
Vous pouvez sauvegarder la base de donnée du drone et l'exploiter plus tard, ou l'effacer si vous n'en avez pas besoin. Vous devez être conscient qu'une fois supprimée, la base de donnée ne sera pas récupérable. Sinon vous pouvez exporter les valeurs récupérer et ensuite effacer ou non la base de donnée.</p>

<h3>SÉLÉCTION DES OPTIONS D'ARRÊT</h3>
<h4>RESTART</h4>
<p>L'option restart permet juste d'arrêter la session en cours pour en commencer une nouvelle, sans toucher aux paramètres de connexion et à la base de donnée de celle-ci.</p>

<h2>ARRÊT SESSION</h2>

<?php
if(isset($_GET) && !empty($_GET))
{
   if($_GET['err'] == '1')
   {
      ?>
      <p style="font-size: 20px; font-weight: bold; color:red;">Erreur ! Impossible d'effectuer l'oppération.</p>
      <?php
   }


   ?>
   <p style="font-size: 20px; font-weight: bold; color:red;">Vous devez sélectionner au moins une option !</p>
   <?php
}
?>


<form action="../session/arret_session.php" method="post"  class="option">
  <div class="option2">
  <fieldset>
    <legend>Sélectionnez vos options d'arrêt</legend>
    <input type="checkbox" id="restart" name="restart" value="1">
    <label for="restart">Restart</label>
    <br>
    <input type="checkbox" id="restart_effacer" name="restart_effacer" value="1">
    <label for="restart_effacer">Restart + effacer base de donnée active</label>
  </fieldset>
  <br>
    <fieldset>
    <legend>Sélectionnez vos options d'export</legend>
    <input type="checkbox" id="all_exp" name="all_exp" value="1">
    <label for="all_exp">Tout exporter</label>
    <br>
    <input type="checkbox" id="sonar_val" name="sonar_val" value="1">
    <label for="sonar_val">Sonar</label>
    <br>
    <input type="checkbox" id="GPS_val" name="GPS_val" value="1">
    <label for="GPS_val">GPS</label>
    <br>
    <input type="checkbox" id="camera_val" name="camera_val" value="1">
    <label for="camera_val">Caméra/photos</label>
  </fieldset>
  <br>
    <fieldset>
    <legend>Sélectionnez vos options de déconnexion</legend>
    <input type="checkbox" id="deco_all" name="deco_all" value="1">
    <label for="deco_all">Tout déconnecter</label>
    <br>
    
    <input type="checkbox" id="Joystick_co" name="Joystick_co" value="1">
    <label for="Joystick_co">Joystick</label>
    <br>
    
    <input type="checkbox" id="Sonar_co" name="Sonar_co" value="1">
    <label for="Sonar_co">Sonar</label>
    <br>
    <input type="checkbox" id="Module_H" name="Module_H" value="1">
    <label for="Module_H">Module-HC</label>
    <br>
    <input type="checkbox" id="Camera_co" name="Camera_co" value="1">
    <label for="Camera_co">Caméra</label>
    <br>
    <input type="checkbox" id="GPS_co" name="GPS_co" value="1">
    <label for="GPS_co">GPS</label>
    <br>
    <input type="checkbox" id="Phare" name="Phare" value="1">
    <label for="Phare">Phare</label>
    <br>
    <input type="checkbox" id="Routeur" name="Routeur" value="1">
    <label for="Routeur">Routeur</label>
    <br>
    <input type="checkbox" id="MySQL" name="MySQL" value="1">
    <label for="MySQL">MySQL</label>
    <br>
    <input type="checkbox" id="Apache2" name="Apache2" value="1">
    <label for="Apache2">Apache2</label>
    <br>
    <input type="checkbox" id="Arduino" name="Arduino" value="Arduino">
    <label for="Arduino">Arduino</label>
    <br>
    </fieldset>
    <input type="submit" value="Valider">
  <br>
  </div>
  
    
</form>
<script src="script_button.js"></script>
</body>
</html>



