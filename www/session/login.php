<?php

include "../H_DBCONNECT_lib.php";

?>

<html lang='fr'>
<head>
   <meta charset="UTF-8"/>
   <title>SERVER DRONEBALIOS</title>
   <link rel="shortcut icon" type="image/x-icon" href="../bateau_ico.ico">
</head>
<body>
<?php

if(isset($_GET) && !empty($_GET))
{
   if(isset($_SESSION) && !empty($_SESSION))
   {
   ?>
	<div class="modal">
	<h1><span class="error">Attention !</span></h1>
	   <p> Vous avez déjà une session en cours d'éxécution, veuillez arrêter votre session d'abord sur cette page: <a href="../Includes/stop_session.php">arrêt session</a></p>
	</div>
<?php
   }
   else
   {
      session_start();
      $_SESSION['dbname'] = $_GET['dbname'];
      $_SESSION['pret'] = 1;
      header("Location: ../index.php");
   }
}
else
{
   header("Location: ../Includes/charger_session.php?err=charge");
}

?>
</body>
</html>

<style>
   div {
   width: 50%;
   padding: 10px;
   text-align: center;
   background-color: #E6E6E6;
   border: 2px solid black;
   border-radius: 10px;
   position: absolute;
   top: 50%;
   left: 50%;
   transform: translate(-50%, -50%);
   }
   
.error {
   color:red;
   }

p {
   font-size: 18px;
   font-weight: bold;
   }

}
</style>

