<?php

/* Information need to config */
$server_ = "localhost"; 		// use your server
$user_   = "admin_6";			// use your user
$pass_   = "123456";   		// use password of your user 
$dbname_  = "smartGarden";		// use your name's database

/* Create connect */
$conn = mysqli_connect($server_, $user_, $pass_, $dbname_);

/* Check error */
/*if( $conn == false){
	die("Error connect. Please try again." .mysqli_connect_error() );
}*/

?>


