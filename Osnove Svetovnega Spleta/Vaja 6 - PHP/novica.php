<?php
include_once 'baza.php';
session_start();
?>

<!DOCTYPE html>
<html>

<head>
    <style>
        .novica {
            border: 1px black solid;
        }
    </style>
    <title>OSS Vaja 6</title>
</head>

<body>

    <h1>Novice</h1>
    <?php
    if (isset($_SESSION["user"])) {
        $_SESSION["loggedIn"] = true;
        echo "Pozdravljen, " . $_SESSION["user"] . "</br>";
        echo "<a href='odjava.php'><button id='odjava'>Odjava</button></a>";
    } else {
        echo "<a href='prijava.php'><button id='prijava'>Prijava</button></a>";
        $_SESSION["loggedIn"] = false;
    }
    ?>

    <hr>

    <?php
    if ($_SESSION["loggedIn"] == true) {
        $found = false;
        foreach ($novice as $novica) {
            if ($_GET["id"] == $novica->id) {
                echo "<div class='novica'><h2>" . $novica->naslov . "</h2>";
                echo "<p>" . $novica->povzetek . "</p><br>";
                echo "<p>" . $novica->vsebina . "</p>";
                echo "<p>" . $novica->avtor . "</p>";
                echo "<p>" . $novica->datum . "</p></div>";
                $found = true;
            }
        }
        if($found == false){
            echo "Novica ne obstaja";
        }
    }
    if ($_SESSION["loggedIn"] == false) {
        echo "Prosim prijavi se";
    }
    ?>
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