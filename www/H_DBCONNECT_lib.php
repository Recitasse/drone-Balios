<?php
// Connexion à la base de donnée

$BDD = array();
$BDD['host'] = "localhost";
$BDD['user'] = "balios";
$BDD['pass'] = "droneBalios1";

if(isset($_SESSION) && !empty($_SESSION))
{
  $mysqli = mysqli_connect($BDD['host'], $BDD['user'], $BDD['pass'], $_SESSION['dbname']);
  if (!$mysqli) 
  {
     die("La connexion à échoué :" .mysqli_connect_error());
  }
}
else
{
  $mysqli = mysqli_connect($BDD['host'], $BDD['user'], $BDD['pass']);
  if (!$mysqli) 
  {
     die("La connexion à échoué :" .mysqli_connect_error());
  }
}

