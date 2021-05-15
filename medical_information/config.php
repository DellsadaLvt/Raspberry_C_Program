<?php
	
	// information
	$server_ 	=	"localhost";
	$user_  	= 	"admin_6";
	$pass_	 	= 	"123456";
	$dbname_  	= 	"medical_information";
	
	// declare connection
	$conn    = 	mysqli_connect($server_, $user_, $pass_, $dbname_);
	
	// check connect
	if( $conn == false){
		die( "error connected!" .mysqli_connect_error() );
	}
?>