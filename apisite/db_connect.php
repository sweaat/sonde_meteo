<?php
$dburl="localhost:3306";
$dblogin="root";
$dbpass="";
$dbtable="base";

try 
	{
	$db_b = new PDO
	('mysql:host='.$dburl.';dbname='.$dbtable.';charset=utf8',$dblogin,$dbpass);
	$db_b->query("SET NAMES 'utf8'");
	$db_b->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_WARNING);
	}
catch (PDOException $e)
	{
		echo "Erreur connexion BDD : ".$e->getMessage()."";
	echo "Merci de revenir d'ici quelques heures.";
	}

?>