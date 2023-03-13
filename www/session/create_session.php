<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);
include "../H_DBCONNECT_lib.php";

$ss_Name = "droneBalios_".$_POST['Name'];

$sql_verif = "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '$ss_Name'";
$result = mysqli_query($mysqli, $sql_verif);

if (mysqli_num_rows($result) > 0) 
{
    header('Location: ../Includes/new_session.php?err=dbnameDouble');
}

$ss_Lieu = $_POST['lieu'];
$ss_coord = $_POST['coord'];
$ss_joystick = $_POST['joy'];
$ss_Arduino = $_POST['ard'];

if(isset($_POST['sonar']) && $_POST['sonar'] == 'o')
{
  $param_sonar = 1;
}
else
{
  $param_sonar = 0;
}

if(isset($_POST['cam']) && $_POST['cam'] == 'o')
{
  $param_cam = 1;
}
else
{
  $param_cam = 0;
}

if(empty($_POST['ard']))
{
   $ss_Arduino = 'ttyACM0';
}


// Pour le nom de la base de donnée
if(isset($_POST['Name']) && !empty($_POST['Name'])) 
{
   $ss_Name = htmlspecialchars(preg_replace('/[^a-zA-Z0-9\']/', '_',"droneBalios_".$_POST['Name']));
}
else
{
   unset($ss_Name);
   header('Location: ../Includes/new_session.php?err=dbname');
}


// Pour le lieu dans la base de donnée
if(isset($_POST['lieu']) && !empty($_POST['lieu'])) 
{
   $ss_Lieu = htmlspecialchars($_POST['lieu']);
}
else
{
   header('Location: ../Includes/new_session.php?err=lieu');
}

// Pour le joystick dans la base de donnée
if(isset($_POST['joy']) && !empty($_POST['joy'])) 
{
   $ss_joystick = htmlspecialchars($_POST['joy']);
}
else
{
   header('Location: ../Includes/new_session.php?err=joy');
}

if(isset($_POST['coord']) && !empty($_POST['coord'])) 
{
   $ss_coord = "https://www.google.fr/maps/@".$_POST['coord'].",300m/data=!3m1!1e3!5m1!1e4";
}

if(isset($_POST['pswd']) && !empty($_POST['pswd'])) 
{
   $pswd = htmlspecialchars($_POST['pswd']);
}
else
{
   header('Location: ../Includes/new_session.php?err=pswd');
}


// Création de la base de donnée

$sql = "CREATE DATABASE ".$ss_Name."";

if (mysqli_query($mysqli, $sql)) 
{
   session_start();
   $_SESSION['dbname'] = $ss_Name;
   $_SESSION['lieu'] = $ss_Lieu;
   $_SESSION['sonar'] = $param_sonar;
   $_SESSION['cam'] = $param_cam;
   $_SESSION['joy_ad'] = $ss_joystick;
   $_SESSION['ard_ad'] = $ss_Arduino;
   $_SESSION['coord'] = $ss_coord;
   $_SESSION['pret'] = 1;
   $_SESSION['date'] = date("Y-m-d H:i:s");
   $_SESSION['pswd'] = $pswd;

   include "../H_DBCONNECT_lib.php";
   
   // Création de la table méta-donnée
   $sql = "CREATE TABLE IF NOT EXISTS SESSION_METADATA (
   Nom VARCHAR(30) NOT NULL DEFAULT '".$_SESSION['dbname']."',
   Lieu VARCHAR(50) NOT NULL DEFAULT '".$_SESSION['lieu']."',
   Coordonnees VARCHAR(300) NOT NULL DEFAULT '".$_SESSION['coord']."',
   Date TIMESTAMP NULL,
   Joystick VARCHAR(20) NOT NULL DEFAULT '".$_SESSION['joy_ad']."',
   Sonar TINYINT(1) NOT NULL DEFAULT '".$_SESSION['sonar']."',
   Camera TINYINT(1) NOT NULL DEFAULT '".$_SESSION['cam']."',
   Arduino VARCHAR(30) NOT NULL DEFAULT '".$_SESSION['ard_ad']."')";
   
   if (!mysqli_query($mysqli, $sql)) 
   {
      header("Location: ../new_session.php?err=creat");
   }
   if (!mysqli_query($mysqli, "INSERT INTO SESSION_METADATA (Date) VALUES (CURRENT_TIMESTAMP)")) 
   {
      header("Location: ../new_session.php?err=creat");
   }
   else
   {
      header("Location: ../index.php");
   }
   
} 
else 
{
    header("Location: ../new_session.php?err=creat");
    
}
?>


