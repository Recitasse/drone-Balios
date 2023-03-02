<?php

  if (isset($_POST['Joystick_verif'])) {
    $cond_joy = array(0, 0, 0, 0);
  // On doit vérifier 4 états, on commence par le plus simple
  // Vérification du branchement ============================
    $output_device = substr(trim(shell_exec("cat /proc/bus/input/devices | grep ".$_SESSION['joy_ad'])), -4);
    if($output_device == ' js0')
    {
      $cond_joy[0] = 1;
    }
    $pwd = $_SESSION['pswd'];
    $args_joy = array($_SESSION['joy_ad'],$_SESSION['dbname'], " > joystick.log 2>&1 &");
    $commande = "echo '$pwd' | sudo -S python3 ../joystick/lecture_event.py " . implode(" ", $args_joy);

  // Vérification du script python ==========================
     shell_exec($commande);
  // La commande pour vérifier l'input est :ps -ef | grep -E 'lecture_event.*sudo|sudo.*lecture_event'*/ ==============================
   


}

?>

<table>
 <thead>
  <tr>
    <th>Joystick</th>
    <th>Sonar</th>
    <th>GPS</th>
    <th>Accéléromètre</th>
    <th>GPS</th>
    <th>Radars</th>
  </tr>
 </thead>
 <tbody>
  <tr>
    <td>
     <div class="board">
      <div class="light" id="light1"></div>
      <div class="text" id="text1"></div>
     </div>
     <div class="run">
	<form action="" method="post">
	  <input type="submit" name="Joystick_verif" value="Initialiser">
	</form>
	<span class="verif_ok"></span>

     </div>
    </td>
    <td>
     <div class="board">
      <div class="light" id="light2"></div>
      <div class="text" id="text2"></div>
     </div>
    </td>
    <td>
     <div class="board">
      <div class="light" id="light3"></div>
      <div class="text" id="text3"></div>
     </div>
    </td>
    <td>Row 2, Column 4</td>
    <td>Row 2, Column 5</td>
    <td>Row 2, Column 5</td>
  </tr>
 </tbody>
 <tfoot>
  <tr>
    <td>Row 3, Column 1</td>
    <td>Row 3, Column 2</td>
    <td>Row 3, Column 3</td>
    <td>Row 3, Column 4</td>
    <td>Row 3, Column 5</td>
    <td>Row 2, Column 5</td>
  </tr>
 </tfoot>
</table>
</div>

<script>
const light = document.querySelector('#light1');
const text = document.querySelector('#text1');

setInterval(function() {
  const condition_Joystick = Math.floor(Math.random() * 3);

  if (condition_Joystick === 0) {
    light.classList.remove('yellow');
    light.classList.remove('green');
    light.classList.add('red');
    text.textContent = 'Stop';
    
  } else if (condition_Joystick === 1) {
    light.classList.remove('red');
    light.classList.remove('green');
    light.classList.add('yellow');
    text.textContent = 'Wait';
    
  } else {
    light.classList.remove('red');
    light.classList.remove('yellow');
    light.classList.add('green');
    text.textContent = 'Go';
  }
}, 1000);


</script>




