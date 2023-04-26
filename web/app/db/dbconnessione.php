<?php
$servername = "mysql";
$username = "jmp-user";
$password = "mysql-user-password";
$conn = new mysqli($servername, $username, $password, "jmp-db");
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
echo "Connected successfully";

?>