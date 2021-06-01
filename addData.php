<?php

include("config.php");


$stateLed0 = $_POST["stateLed0"];
$stateLed1 = $_POST["stateLed1"];
$stateLed2 = $_POST["stateLed2"];
$stateLed3 = $_POST["stateLed3"];
$stateFan  = $_POST["fan"];
$password  = $_POST["password"];
$ena	   = $_POST["ena"];


$sql = "update control set stateLed0='$stateLed0', stateLed1='$stateLed1', stateLed2='$stateLed2', 
							stateLed3='$stateLed3', stateFan='$stateFan', password='$password', ena='$ena' ";

mysqli_query($conn, $sql);



?>