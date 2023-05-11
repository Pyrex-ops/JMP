<?php

$servername = getenv('PMA_HOST');
$username = getenv('MYSQL_USER');
$password = getenv('MYSQL_PASSWORD');
$database = new mysqli($servername, $username, $password, getenv('MYSQL_DATABASE'));
if ($database->connect_error) {
    exit('Connection failed: '.$database->connect_error);
}
//echo "Connected successfully";
