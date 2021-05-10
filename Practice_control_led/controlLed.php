<?php

// include config files
include("config.php");

// read data
$brightness = $_POST["brightness"];
$red		= $_POST["red"];
$blue		= $_POST["blue"];
$green		= $_POST["green"];
$test		= 33;




if($_SERVER["REQUEST_METHOD"] == "POST"){
	
$sql = "update stateLed set red=$red, green=$green, blue=$blue, brightness=$brightness";
mysqli_query($conn, $sql);	

}

// write data
$sql = "select * from stateLed";
$result = mysqli_query($conn, $sql);
$rgb = mysqli_fetch_row($result);
$color = (($rgb[1]<<16) | ($rgb[3]<<8) | $rgb[2]) ;



	

mysqli_close($conn);

?>


<!DOCTYPE html>
<html lang="en" dir="ltr"><!--ltr: left to right -->
	<head>
		<title> My Dashboard On Rasp </title>
		<meta name="description" content="Page Description Here" >
    	<meta http-equiv="Content-Type" content="text/html"; charset="utf-8">
    	<meta name="viewport" content="width=device-width, initial-scale=1">
		<link rel="stylesheet" type="text/css" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.3/css/all.min.css">
		<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta3/dist/css/bootstrap.min.css">

	</head>
	
	

	<!-- -->
	<body style="background:#7B7D7D;">
	
		
			<div class="border border-dark rounded-3" style="float:left; width:500px; margin:20px; padding:20px;">
				<h3 class="text-center text-decoration-underline" style="font-weight=bold;">CONTROL PANNEL</h3>
				<form  action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="POST">
					<label for="brightness" class="form-label">Brightness</label><br>
									   <input type="range" class="form-range" min="0" max="255" step="10" name="brightness" value="<?php echo $rgb[5] ?>"><br>
					<label>Red</label><input type="range" class="form-range" min="0" max="255" step="10" name="red" value="<?php echo $rgb[1] ?>">
					<label>Green</label><input type="range" class="form-range" min="0" max="255" step="10" name="green" value="<?php echo $rgb[3] ?>">
					<label>Blue</label><input type="range" class="form-range" min="0" max="255" step="10" name="blue" value="<?php echo $rgb[2] ?>">
					<br><br>
					<input type="submit" class="btn btn-primary" style="margin-left:390px;" value="Apply">
				</form>
			</div>
			
			<div class="border border-dark rounded-3" style="float:left; width:350px; margin:20px; padding:20px; ">
				<h3 style="font-weight: bold; text-align: center;" class="text-decoration-underline">STATUS</h3>
				<div class="border border-2  border-dark rounded-2 " style="margin:20px; padding:20px; width:280px; height: 100px; background-color: rgb(<?php echo $rgb[1] ?>,<?php echo $rgb[3] ?>,<?php echo $rgb[2] ?>);"></div>
				<h5 style="text-align: center; font-weight: bold; text-shadow:rebeccapurple; margin-top:45px; ">Table color value</h6>
				<table class="table	table table-striped">
					<thead>
						<tr>
							<th scope="col">Red</th>
							<th scope="col">Green</th>
							<th scope="col">Blue</th>
							<th scope="col">Brightness</th>
							<th scope="col">Hex</th>
						</tr>
					</thead>
					
					<tbody style="text-align:center;">
						<tr>
							<td><?php echo $rgb[1]; ?></td>
							<td><?php echo $rgb[3]; ?></td>
							<td><?php echo $rgb[2]; ?></td>
							<td><?php echo $rgb[5]; ?></td>
							<td><?php echo dechex($color); ?></td>
						</tr>
						
					</tbody>
					
				</table>
				</div>
			
		
		
	</body>
</html>