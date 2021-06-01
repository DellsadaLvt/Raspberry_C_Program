<?php

$server_ = "localhost";
$user_   = "admin_10";
$pass_   = "123456";
$dbname_ = "smartHome";


$conn = mysqli_connect($server_, $user_, $pass_, $dbname_);


if ( $conn == false){
	die("Connect error. "   .mysqli_connect_error() );
}

?>



