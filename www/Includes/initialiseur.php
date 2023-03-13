<?php
include "fonc_ini.php";
// Les initialisations
$_SESSION['joy'] = array(0);
$_SESSION['carte'] = array(0);

$cond_joy = array(0, 0, 0, 0);
// On doit vérifier 4 états, on commence par le plus simple
// Vérification du branchement ============================
//$output_device = substr(trim(shell_exec("cat /proc/bus/input/devices | grep ".$_SESSION['joy_ad'])), -4);
$output_device = shell_exec("cat /proc/bus/input/devices | grep js0");
if(!empty($output_device))
{
  $output_device = str_replace('H: Handlers=','',$output_device);
  $output_device = substr($output_device,0,-6);
}

if($output_device == $_SESSION['joy_ad'])
{
  $_SESSION['ini'][0] = 1;
}
else
{
  $_SESSION['ini'][0] = 0;
}

// Vérification de Arduino ===========================
$output_ard = shell_exec("ls /dev/".$_SESSION['ard_ad']);
// 1) Pour le branchement
if(!empty($output_ard))
{
  if(substr(str_replace('/dev/','',$output_ard),0,-1) == $_SESSION['ard_ad'])
  {
    $_SESSION['carte'][0] = 1;
  }
  else
  {
    $_SESSION['carte'][0] = 0;
  }
}
else
{
   $_SESSION['carte'][0] = 0;
}

// 2) Pour la connexion entre la carte 1 et la 2e
$arduino_cli = "../Initialisation_arduino/bin/arduino-cli";
$commu_script = "../Initialisation_arduino/Communication_sender/Communication_sender.ino";
//$tty = "/dev/".$_SESSION['ard_ad'];
$tty = '/dev/ttyACM0';

$pwd = $_SESSION['pswd'];
exec("echo '$pwd' | sudo -S /bin/bash ../Initialisation_arduino/__SCRIPT__/ini_communication.sh");
$data = file_get_contents('../Initialisation_arduino/__SCRIPT__/commu_output.txt');
echo "Screen output : " . $data;

   

?>
<div id='refresh'>
<h3>Les branchements</h3>
<table>
  <thead>
    <tr>
      <th>Joystick</th>
      <th>Carte Arduino</th>
    <tr>
  </thead>
  <tbody>
    <tr>
      <td><?php Validation_joy($_SESSION['ini'][0]) ?></td>
      <td><?php Validation_carte($_SESSION['ini'][0]) ?></td>
    </tr>
  </tbody>
</table>
</div>
</div>
<script>
/*function refreshDiv() {
  // Use AJAX to fetch updated content from PHP file
  var xmlhttp = new XMLHttpRequest();
  xmlhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("refresh").innerHTML = this.responseText;
    }
  };
  xmlhttp.open("GET", "index.php", true);
  xmlhttp.send();
}

setInterval(refreshDiv, 1000); // Refresh every 1 second (1000ms)*/
</script>


