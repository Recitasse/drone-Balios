<?php

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

include "../H_DBCONNECT_lib.php";
session_start();
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
<h1>CONFIGURER UNE SESSION<h1>

<h2>COMMENT CRÉER UNE SESSION<h2>
<h3>DESCRIPTION DE LA SESSION</h3>
<p>La session sert à stocker des variabes, qui serviront à récupérer des données (données bathymétriques) et les exploiter plus tard quand bon nous sembles, mais aussi à stocker des paramètres importants indispensables à l'initialisation du drone.</p>
<p>Vous disposez de 4 champs dont 2 absolument obligatoires, <b>le nom du joystick</b> et le <b>nom de la carte Arduino</b> (bien que celui ci possède une valeur par défaut).</p>


<h2>CRÉATION DE LA SESSION</h2>
<?php
if(isset($_GET['err']) && !empty($_GET['err']))
{
  if($_GET['err'] == 'creat')
  {
  ?>
  <p style="color:red; font-weight: bold; font-size: 20px;">La création de la session a échoué.</p>
  <?php
  }
}
?>

<p>Le <b>nom de la session</b> sera le nom de la base de donnée, le <b>Lieu</b> est le nom du lac, le <b>nom du joystick</b> correspond au nom de <i>l'évènement</i> (<a href="../aide/joystick_aide.php" target="_blank">voir ici</a>) qui lui est associé pour l'ordinateur et le <b>nom d'Arduino</b> comme pour le joystick est le nom du port utilisé par Arduino (<a href="../aide/arduino_aide.php" target="_blank">voir ici</a>).

<div class="creation_session">
<form action="../session/create_session.php" method="post" id="new_s">
  <div>
  
  <?php
  if(isset($_GET['err']) && !empty($_GET['err']))
  {
   if($_GET['err'] == 'dbnameDouble')
   {
      ?>
      <p style="color:red; font-weight: bold;">Ce nom existe déjà, veuillez en choisir un autre.</p>
      <?php
   }
   elseif($_GET['err'] == 'dbname')
   {
      ?>
      <p style="color:red; font-weight: bold;">Nom invalide, saisissez un nom.</p>
      <?php
   }
   }
   ?>
    <label for="Name">Nom session:</label>
    <input type="text" id="Name" name="Name" required="required" style="background-color: #F6D8CE;">
    
    
  </div>
  <div>
    <?php
  if(isset($_GET['err']) && !empty($_GET['err']))
  {
   if($_GET['err'] == 'lieu')
   {
      ?>
      <p style="color:red; font-weight: bold;">Nom invalide.</p>
      <?php
   }
  }
   ?>
    <label for="Lieu">Nom lieu:</label>
    <input type="text" id="lieu" name="lieu" required="required" style="background-color: #F6D8CE;">
    <label for="Lieu">Coordonnées (Long, Lat)</label>
    <input type="text" id="coord" name="coord">
    <i>Par exemple : "47.9371596,1.9160537"</i>
  </div>
  <div>
      <?php
  if(isset($_GET['err']) && !empty($_GET['err']))
  {
   if($_GET['err'] == 'joy')
   {
      ?>
      <p style="color:red; font-weight: bold;">Nom invalide.</p>
      <?php
   }
  }
   ?>
    <label for="joy">Joystick nom:</label>
    <input type="text" id="joy" name="joy" required="required" style="background-color: #F6D8CE;">
  </div>
  <div>
    <?php
  if(isset($_GET['err']) && !empty($_GET['err']))
  {
   if($_GET['err'] == 'ard')
   {
      ?>
      <p style="color:red; font-weight: bold;">Nom invalide.</p>
      <?php
   }
  }
   ?>
    <label for="ard">Arduino nom:</label>
    <input type="text" id="ard" name="ard">
    <p><i>Valeur par défaut 'ttyACM0'</i></p>
    </div>
  
  <?php
  // Pour le mot de passe
  if(isset($_GET['err']) && !empty($_GET['err']))
  {
   if($_GET['err'] == 'pswd')
   {
      ?>
      <p style="color:red; font-weight: bold;">Mot de passe invalide.</p>
      <?php
   }
  }
    ?>

    <div>
    <label for="pswd">Mot de passe</label>
    <input type="password" id="pswd" name="pswd" style="background-color: #F6D8CE;" require="required">
    <p><i>Votre mot de passe utilisateur (root)</i></p>
     </div>

    <div>
    <label for="sonar">Récupérer des données:</label>
    <input type="checkbox" id="sonar" name="sonar" value="o">
     </div>
     <div>
    <label for="cam">Activation caméra:</label>
    <input type="checkbox" id="cam" name="cam" value="o">
     </div>
    <div>
    <button type="submit">Créer session</button>
  </div>
</form>

</div>
</body>
</html>


