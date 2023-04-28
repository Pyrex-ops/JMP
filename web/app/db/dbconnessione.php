<?php
$servername = "mysql";
$username = "jmp-user";
$password = "mysql-user-password";
$database = new mysqli($servername, $username, $password, "jmp-db");
if ($database->connect_error) {
    die("Connection failed: " . $database->connect_error);
}
echo "Connected successfully";

?>