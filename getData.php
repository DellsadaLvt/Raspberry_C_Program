<?php
//send a json message to website 
header('Content-Type: application/json');

// include config file
include("config.php");

// connect and read databases
$sql = "select * from accounts";
$result = mysqli_query($conn, $sql);

// seperate data
$data = array();
foreach( $result as $row){
    $data[] = $row;
}

mysqli_close($conn);

echo json_encode($data);

?>