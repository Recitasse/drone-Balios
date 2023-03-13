<?php
//Script des fonctions d'affichage

// ================= Pour le joystick
function Validation_joy($val)
{
   if($val == 0)
   {
      ?>
      <div class="carre_r"></div>
      <?php
   }
   elseif($val == 1)
   {
      ?>
      <div class="carre_v"></div>
      <?php
   }
   else
   {
      ?>
      <div class="carre_j"></div>
      <?php
   }
}

// =================== Pour les cartes

function Validation_carte($val)
{
   if($val == 0)
   {
      ?>
      <div class="carre_r"></div>
      <?php
   }
   elseif($val == 1)
   {
      ?>
      <div class="carre_v"></div>
      <?php
   }
   else
   {
      ?>
      <div class="carre_j"></div>
      <?php
   }
}

?>

<style>
.carre_r {
   width: 50px;
   height: 50px;
   background-color: red;
   border: 1px solid black;
   border-radius: 5px;
   margin: auto;
   margin-top: 10px;
   margin-bottom: 10px;
}

.carre_v {
   width: 50px;
   height: 50px;
   background-color: green;
   border: 1px solid black;
   border-radius: 5px;
   margin: auto;
   margin-top: 10px;
   margin-bottom: 10px;
}

.carre_j {
   width: 50px;
   height: 50px;
   background-color: yellow;
   border: 1px solid black;
   border-radius: 5px;
   margin: auto;
   margin-top: 10px;
   margin-bottom: 10px;
}
</style>

