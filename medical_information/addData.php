<?php

include("config.php");

$name 	= $_POST["name"];
$DoB  	= $_POST["DoB"];
$gender = $_POST["gender"];
$height = 178;
$weight = 60;
$BMI 	= 21;


$sql = "insert into medical_inf ( name, date_of_birth, gender) value ('$name', '$DoB', '$gender')";
mysqli_query($conn, $sql);

mysqli_close($conn);


?>