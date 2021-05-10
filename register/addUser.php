<?php
// read data from web
$acc = $_POST["username"];
$pass = $_POST["password"];

// connect database
include("config.php");

// sent data to database
// create a variable save the command
$sql = "insert into accounts (user, password) value ( '$acc','$pass')";
// connect to sql
mysqli_query($conn, $sql);
 
// ngat connect
mysqli_close($conn);

?>