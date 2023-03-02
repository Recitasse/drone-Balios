<!DOCTYPE html> 
<html lang='fr'>
<head>
   <meta charset="UTF-8"/>
   <title>SERVER DRONEBALIOS</title>
   <link rel="stylesheet" href="../styles.css">
   <link rel="shortcut icon" type="image/x-icon" href="../bateau_ico.ico">
</head>

<h3>Vérification du branchement de la manette</h3>
<p>Vérifier si votre manette est bien branchée. Si vous avez plusieurs manettes faite attention dans le choix de celle-ci dans le prompt suivant. Pour le moment le logiciel n'est configuré que pour une seule manette.</p>
<p>Si jamais votre manette est branchée mais qu'elle n'est toujours pas détectée peut être que <b>son nom est différent de ce qu'attend le logiciel</b> ("Controller" en l'occurence ici), il vous faudra vérifier par vous même via le lien ici <a target="_blank" href='config.php?voir=joystick'>aide pour configuration de la manette</a>.</p>

<?php 
// On affiche via le terminal les bus et précisément les manettes
$output_device = shell_exec("cat /proc/bus/input/devices | grep -B 2 -A 9 Controller");
?>

<div id="event" style="background-color: #E0E6F8; border-radius: 5px; border: 1px solid black; word-wrap: break-word;">
      <?php
      if (isset($output_device) && !empty($output_device)) {
      	?>
      	<pre style="margin-left: 15px">
      	   <code id="event" style="font-size: 15px; margin-left: 10px">
      	      <?php echo str_replace('event',"<span style='color:red; font-weight:bold;'>event</span>",$output_device); ?>
      	   </code>
      	</pre>
      	<?php
         }
      else {
       ?>
       <p style="color:red; font-weight: bold; padding: 5px;">Aucune manette détecté !</p>
     <?php
     }
     ?>
</div>
