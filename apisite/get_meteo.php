<?php
include("db_connect.php");
getProducts();

function getProducts()
{
    global $db_b;
    $sql = $db_b->prepare('SELECT temp,hum,pres FROM table_meteo');

    // Vérifie si la requête s'est exécutée correctement
    if ($sql->execute()) {
        // Récupère les données
        $data = $sql->fetchAll(PDO::FETCH_ASSOC);

        // Définit le type de contenu à JSON
        header('Content-Type: application/json');
        
        // Renvoie les données au format JSON
        echo json_encode($data, JSON_PRETTY_PRINT);
    } else {
        // En cas d'erreur lors de l'exécution de la requête
        $errorInfo = $sql->errorInfo();
        // Affiche les informations sur l'erreur
        echo "Erreur lors de l'exécution de la requête : " . $errorInfo[2];
    }
}

include("close_pdo.php");
?>
