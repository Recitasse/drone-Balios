<!DOCTYPE html> 
<html lang='fr'>
<head>
   <meta charset="UTF-8"/>
   <title>SERVER DRONEBALIOS</title>
   <link rel="stylesheet" href="../styles.css">
   <link rel="shortcut icon" type="image/x-icon" href="../bateau_ico.ico">
</head>
<body>
<?php

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

  if(isset($_GET['voir']) && !empty($_GET['voir'])) {
     if($_GET['voir'] == 'joystick') {
	$output = shell_exec("cat /proc/bus/input/devices");
	?>
	<h3>AIDE MANETTE</h3>
	<p>Chercher dans les informations suivantes votre contrôlleur, généralement on <b>les reconnait</b> par la notation <i>jsX</i> ou X est son numéro, et prenez l'évènement qui lui est associé (juste à sa gauche).</p>
	<p>Si vous ne parvenez toujours pas à trouver votre contrôleur, cela peut venir des permissions de l'ordinateur ou d'un problème du contrôleur directement.</p>
	<div style="background-color: #E0E6F8; border-radius: 5px;overflow-wrap: break-word; border: 1px solid black;">
	   <pre style="margin-left: 15px; overflow-wrap: break-word;">
	     <code style="font-size: 15px; margin-left: 10px;overflow-wrap: break-word;">
	      <?php echo $output; ?>
	     </code>
	   </pre>
	</div>
	<?php
	}
    elseif($_GET['voir'] == 'carte') {
    	$output = shell_exec("ls /dev/ttyACM0*");
	?>
	<h3>AIDE ARDUINO</h3>
	<p>Chercher dans les informations suivantes votre carte, généralement on <b>les reconnait</b> par la notation <i>ACMX</i> ou X est son numéro, et prenez celui de la carte que vous voulez.</p>
	<p>Si vous ne parvenez toujours pas à trouver votre carte, cela peut venir des permissions de l'ordinateur ou d'un problème de la carte directement.</p>
	
	<?php
	if(!empty($output))
	{
	?>
	
	<div style="background-color: #E0E6F8; border-radius: 5px;word-wrap: break-word; border: 1px solid black;">
	   <pre style="margin-left: 15px">
	     <code style="font-size: 15px; margin-left: 10px; word-wrap: break-word;">
	      <?php echo $output; ?>
	     </code>
	   </pre>
	</div>
	<?php
	}
	else
	{
	?>
           <div style="background-color: #E0E6F8; border-radius: 5px;">
             <p style="padding: 5px; color:red; font-weight:bold; font-size: 18px;"> Aucune carte détéctée sur le terminal. Veuillez brancher une carte.</p>
	</div>
	<?php
	}
     }
     }
?>

</body>
</html>
