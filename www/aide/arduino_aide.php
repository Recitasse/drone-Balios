<!DOCTYPE html> 
<html lang='fr'>
<head>
   <meta charset="UTF-8"/>
   <title>SERVER DRONEBALIOS</title>
   <link rel="stylesheet" href="../styles.css">
   <link rel="shortcut icon" type="image/x-icon" href="../bateau_ico.ico">
</head>
<body>
<div class="whole">
<h3>Vérification du branchement de la carte Arduino</h3>
<p>Vérifier si votre carte est bien branchée. Si vous avez plusieurs cartes faite attention dans le choix de celle-ci dans le prompt suivant. Pour le moment le logiciel n'est configuré que pour une seule carte.</p>
<p>Si jamais votre carte est branchée mais qu'elle n'est toujours pas détectée peut être que <b>son nom est différent de ce qu'attend le logiciel</b> ("ACM*" en l'occurence ici), il vous faudra vérifier par vous même via le lien ici <a target="_blank" href='config.php?voir=carte'>aide pour configuration de la carte</a>.</p>

<?php 
// On affiche via le terminal les bus et précisément les manettes
$output_device = shell_exec("ls /dev/ttyACM*");
?>

<div id="event" style="background-color: #E0E6F8; border-radius: 5px; border: 1px solid black;">
      <?php
      if (isset($output_device) && !empty($output_device)) {
      	?>
      	<pre style="margin-left: 15px">
      	   <code id="event" style="font-size: 15px; margin-left: 10px">
      	      <?php 
      	      $text = str_replace('ttyACM0',"<span style='color:red; font-weight:bold;'>ttyACM0</span>",$output_device);
      	      echo str_replace('/dev/',"",$text);
      	       ?>
      	   </code>
      	</pre>
      	<?php
         }
      else {
       ?>
       <p style="color:red; font-weight: bold; padding: 5px;">Aucune carte détectée !</p>
     <?php
     }
     ?>
</div>
</div>
</body>
</html>
