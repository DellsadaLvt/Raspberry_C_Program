<?php

// handle then read data from wed
$user = $password = $confirmPassword = "";
$user_temp = $password_temp = $confirmPassword_temp = "";
$user_err = $password_err = $confirmPassword_err = "";

if($_SERVER["REQUEST_METHOD"] == "POST")
{
	include("config.php");
	// handle for user name
	if(empty(trim($_POST["userName"]))){
		$user_err = "Please enter the user name";
	}else{
		$user_temp = trim($_POST["userName"]);
		$sql = "SELECT id FROM accounts WHERE user = '$user_temp'";
        $result = mysqli_query($conn,$sql);
		$count = mysqli_num_rows($result);
		if($count == 1){
			$user_err = "The user is exist.";
		}else{
			$user = trim($_POST["userName"]);
		}
		
	} 
	
	// handle for passowrd
	if(empty(trim($_POST["password"]))){
		$password_err = "Please enter the password.";
	}else{
		//$password_temp = trim($_POST["password"]);
		if(strlen(trim($_POST["password"])) < 6){
			$password_err = "Please enter password longer than six characters.";
		}else{
			$password = trim($_POST["password"]);
		}
	} 
	
	
	
	if( empty($user_err) & empty($password_err)){
	// sent data to databases
	$sql = "insert into accounts (user, password) value ('$user', '$password')";
	mysqli_query($conn, $sql);
	
	// disconnect sql
	mysqli_close($conn);
	}
	

}
?>


<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <title> Practice Register </title>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
        <style>
            body
            {
                font:  20px bold;
                background: wheat;
            }

            .form_enter
            {
                width: 350px;
                padding: 10px;
            }
        </style>
    </head>

    <body>
        <div class="form_enter">
            <h2>Sign in</h2><br>
            <p>Please inter info</p>

            <form action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" method="POST">

				<div class="form-group">
                <label for="userName">User name</label><br>
                <input type="text" class="form-control <?php echo (!empty($user_err))? "is-invalid": "";  ?>" name="userName" value="<?php echo $user; ?>"><br>
                <span class="invalid-feedback" ><?php echo $user_err; ?></span><br>
				</div>
				
				<div class="form-group>
                <label for="password" >Password</label><br>
                <input type="text" class="form-control <?php echo (!empty($password_err))? "is-invalid": ""; ?>" name="password" value="<?php echo $password; ?>" ><br>
				<span class="invalid-feedback"><?php echo $password_err; ?></span>
				</div>

				<div class="form-group">
                <label for="confirmPassword">Confirm password</label>
                <input type="text" class="form-control" name="confirmPassword" <?php echo (!empty($confirmPassword_err))? "is-valid": ""; ?> value="<?php echo $confirmPassword; ?>">
				<span class="invalid-feedback"><?php echo confirmPassword_err ?></span>
				</div>

                <input type="submit" value="Submit"><br><br>

                <p>You have not had account?<a href="#">Sign up</a></p>
                
            </form>
        </div>
    </body>
</html>