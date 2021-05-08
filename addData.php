<?php

// read data from wed
$name = $_POST["userName"];
$pass = $_POST["password"];
$confirm = $_POST["confirmPassword"];

include("config.php");

// log in and insert data in database
$sql = "insert into accounts (user, password) value ('$name','$pass') ";

// send the re quest
mysqli_query($conn, $sql);

// disconnect database
mysqli_close($conn);

?>
