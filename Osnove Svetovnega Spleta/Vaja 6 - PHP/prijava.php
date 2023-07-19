<?php
include_once 'baza.php';
session_start();

$napaka = "";

if (isset($_POST["login"])) {
    $username = $_POST["usern"];
    $password = $_POST["passw"];

    if (strlen($username) > 0) {
        $_SESSION["user"] = $username;
        header("Location: index.php");
        die();
    }

    foreach ($uporabniki as $uporabnik) {
        if ($uporabnik->username == $username && $uporabnik->geslo == $password) {
            $_SESSION["user"] = $username;
            $_SESSION["loggedIn"] = true;
            header("Location: index.php");
            die();
        } else {
            $_SESSION["loggedIn"] = false;
            $napaka = "Username or password are invalid";
        }
    }
}
?>

<!DOCTYPE html>
<html>

<head>
    <title>OSS Vaja 6</title>
</head>

<body>
    <form action="prijava.php" method="POST">
        Username: <input type="text" name="usern" /> <br>
        Password: <input type="password" name="passw" /> <br>
        <input type="submit" name="login" value="Prijavi" /> <br>
        <?php echo $napaka; ?>
    </form>
</body>

</html>

<?php

if (isset($_SESSION['LAST_ACTIVITY']) && (time() - $_SESSION['LAST_ACTIVITY'] > 1800)) {
    // last request was more than 30 minutes ago
    session_unset();
    session_destroy();
    header("Location: index.php");
}
$_SESSION['LAST_ACTIVITY'] = time(); // update last activity time stamp

?>