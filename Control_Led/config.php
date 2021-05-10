<?php

$server_    ="localhost";
$user_      ="admin_3";
$pass_      ="123456";
$dbname_    ="ledControl";

$conn= mysqli_connect($server_, $user_, $pass_, $dbname_);

if($conn == false){
    die("ERROR: Could not connect." .mysqli_connect_error());
}


?>