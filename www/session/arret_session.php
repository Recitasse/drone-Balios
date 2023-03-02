<?php

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

session_start();

if(isset($_POST) && !empty($_POST))
{
    if(isset($_POST['restart']) && $_POST['restart'] == '1')
    {
       session_destroy();
       header('Location: ../index.php');
    }
    elseif(isset($_POST['restart_effacer']) && $_POST['restart_effacer'] == '1')
    {
       include "../H_DBCONNECT_lib.php";
       $nom = $_SESSION['dbname'];
       if (!mysqli_query($mysqli, "DROP DATABASE $nom")) 
       {
         header("Location: ../Includes/stop_session.php?err=1");
       }
       
       session_destroy();
       header('Location: ../index.php');
    }
}
else
{
   echo 'non';
   header("Location: ../Includes/stop_session.php?err=empty");
}

?>
