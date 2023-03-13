<?php

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

?>

<!DOCTYPE html> 
<html lang='fr'>
<head>
   <meta charset="UTF-8"/>
   <title>SERVER DRONEBALIOS</title>
   <link rel="stylesheet" href="../styles.css">
   <link rel="shortcut icon" type="image/x-icon" href="../bateau_ico.ico">
</head>
<body>

<h1>LISTES DES SESSIONS</h1>
Ici se trouvent toutes les sessions créées et sauvées.
<br>

  <?php
  if(isset($_GET) && !empty($_GET))
  {
     if($_GET['err'] == 'charge')
     {
        echo "<p style='color:red; font-weight: bold; font-size: 18px;'>Erreur de chargement !</p>";
     }
  }
  
  

    // récupération des bases de données
    $BDD = array();
    $BDD['host'] = "localhost";
    $BDD['user'] = "balios";
    $BDD['pass'] = "droneBalios1";
    
    $mysqli = new mysqli($BDD['host'], $BDD['user'], $BDD['pass']);

    $DATA = $mysqli->query("SHOW DATABASES");
    $databases = array();
    
    while ($row = $DATA ->fetch_array(MYSQLI_NUM)) {
       if(strpos($row[0], 'droneBalios'))
       {
       	array_push($databases, $row[0]);
       }
    }

    // boucle sur les bases de données
    
    ?>
    <table>
    <thead>
     <tr>
       <th>Nom session</th>
       <th>Lieu</th>
       <th>Date</h>
       <th>Données</th>
       <th>Charger session</th>
     </tr>
    </thead>
    <tbody>
    <?php
    
    mysqli_close($mysqli);
    echo var_dump($databases)." oui";
    for ($i = 1; $i <= count($databases); $i++) {
       // connexion à la base de donnée $i
       $mysqli = new mysqli($BDD['host'], $BDD['user'], $BDD['pass'], $databases[$i]);
       
       $sql = "SELECT * FROM SESSION_METADATA";
       $result = mysqli_query($mysqli, $sql);

       if (mysqli_num_rows($result) > 0) {
         echo "<tr>";
         while($row = mysqli_fetch_assoc($result)) {
           echo "<td>" . $row["Nom"]. "</td>";

           // Pour le lieu et les coordonnées
           
           if(!empty($row["Coordonnees"])) 
           {
              if(!empty($row["Lieu"])) {
                 echo "<td><a href='".$row["Coordonnees"]."' target='_blank'>".$row["Lieu"]."</a></td>";
               }
              else
              {
                 "<td><a href='".$row["Coordonnees"]."' target='_blank'>Accéder à la carte</a></td>";
              }
           }
           
           else
           {
              if(!empty($row["lieu"])) {
                 echo $row["lieu"];
               }
              else
              {
                 "<span style='color:red;'>Aucun lieu renseigné.</span>";
              }
           }
           
           
           echo "<td>" . $row["Date"]. "</td>";
           echo "<td>";
           // Pour le sonar
           if($row["Sonar"] == '1') 
           {
              echo "Sonar activé";
           }
           else
           {
           echo "<span style='color:red;'>Sonar désactivé</span>";
           }
           // Pour la caméra
           if($row["Camera"] == '1') 
           {
              echo "<br>Caméra activée";
           }
           else
           {
           echo "<br><span style='color:red;'>Caméra désactivée</span>";
           }

         
         echo "</td>";
         // Pour le bouton d'activation
         echo "<td>";

         if($row["Sonar"] == 1)
         {
         ?>
           <button id="<?php echo $row["Nom"]; ?>" class="input1">Charger <?php echo $row["Nom"]; ?></button>
         <?php
         }
         else
         {
         ?>
           <button id="<?php echo $row["Nom"]; ?>" class="input2">Charger <?php echo $row["Nom"]; ?></button>
         <?php
         }
         ?>
         <script>
  document.getElementById("<?php echo $row["Nom"]; ?>").addEventListener("click", function() {
    window.location.href = "../session/login.php?dbname=<?php echo $row["Nom"]; ?>";
  });
  </script>
         <?php

         echo "</td>";
         
         echo "</tr>";
       
       }
       mysqli_close($mysqli);

       }
       }

  ?>
  

   </table>
</body>
</html>

<style>

form {
  padding: 2px;
  }

table {
  border-collapse: collapse;
  width: 100%;
}

td, th {
  border: 1px solid #dddddd;
  text-align: left;
  padding: 8px;
}

tr:nth-child(even) {
  background-color: #f2f2f2;
}

  .input1, .input2 {
    font-weight: bold;
    background-color: #088A08;
    width: 100%;
    border: none;
    color: white;
    padding: 8px 16px;
    text-decoration: none;
    display: inline-block;
    font-size: 16px;
    margin: 4px 2px;
    cursor: pointer;
    border-radius: 16px;
  }
  
  .input1:hover {
   background-color: #04B404;
  }
  
  .input2 {
    background-color: red;
    }
  
  .input2:hover {
     background-color: #FE2E2E;
  }

</style>

