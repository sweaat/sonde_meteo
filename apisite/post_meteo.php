<?php
include("db_connect.php");
AddProduct($db_b);

function AddProduct($db_b)
{
    // Récupère le flux JSON brut du corps de la requête
    $json_data = file_get_contents('php://input');
    $data = json_decode($json_data, true);

    if ($data) {
        // Les données JSON ont été correctement décodées
        $temp = isset($data["temp"]) ? floatval($data["temp"]) : null;
        $hum = isset($data["hum"]) ? floatval($data["hum"]) : null;
        $pres = isset($data["pres"]) ? floatval($data["pres"]) : null;

        // Prépare et exécute la requête SQL
        $sql = $db_b->prepare("INSERT INTO table_meteo (temp, hum, pres) VALUES (:temp, :hum, :pres)");
        $sql->execute(["temp" => $temp, "hum" => $hum, "pres" => $pres]);
        
        // Ajoute un message de log pour vérifier si les données sont correctement insérées
        error_log("Données insérées - Temp: $temp, Hum: $hum, Pres: $pres");
    } else {
        // Erreur lors du décodage JSON
        error_log("Erreur lors du décodage JSON");
    }
}

include("close_pdo.php");
?>
