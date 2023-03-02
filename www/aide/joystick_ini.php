<?php

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

$VAR_COND = array();

// On vérifie si le script du joystick est activé
$cond1 = shell_exec("ps -ef | grep python | grep -v grep | grep lecture_event.py");

$event = "event11";

if (empty($cond1)) {
    ?>
    <p style="font-size: 16px; color: red; font-weight: bold;">Le script de lecture du joystick n'est pas mise en route ou a échoué à se mettre en route.</p>
    <p>Les erreurs en cause:</p>
    
    <?php
    // On récupère le log
    exec("python3 ../../joystick/lecture_event.py $event", $cond);
    var_dump($out);
    //file_put_contents("error_log".time().".txt", $output);
    
     ?>
    <?php
} else {
    echo "Python script is running.";
}
?>
