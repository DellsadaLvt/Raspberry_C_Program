<?php

$server_ = "localhost";
$user_ 	 = "admin_6";
$pass_   = "123456";
$dbname_ = "prac_rgb";

$conn = mysqli_connect($server_, $user_, $pass_, $dbname_);

if($conn == false ){
	die( "Error connected." .mysqli_connect_error()	);
}


?>