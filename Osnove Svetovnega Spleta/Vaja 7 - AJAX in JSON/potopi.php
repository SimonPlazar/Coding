<?php
session_start();

function pos_ok($ships, $ship)
{
    foreach ($ship as $arr) {
        if ($arr["x"] > 10 || $arr["y"] > 10) {
            return false;
        } elseif ($arr["x"] < 1 || $arr["y"] < 1) {
            return false;
        } elseif (in_array($arr, $ships)) {
            return false;
        }
    }
    return true;
}

function nova_ladja($len, &$ships)
{
    do {
        $smer_ladjice = rand(0, 1);
        $rnd = array("x" => rand(1, 10), "y" => rand(1, 10));
        $ship = array($rnd);
        if ($smer_ladjice == 0) {
            for ($i = 1; $i < $len; $i++) {
                $next = array("x" => $rnd["x"] + $i, "y" => $rnd["y"]);
                array_push($ship, $next);
            }
        } else {
            for ($i = 1; $i < $len; $i++) {
                $next = array("x" => $rnd["x"], "y" => $rnd["y"] + $i);
                array_push($ship, $next);
            }
        }
    } while (!pos_ok($ships, $ship));
    foreach ($ship as $arr) {
        array_push($ships, array("x" => $arr["x"], "y" => $arr["y"]));
    }
}

$lokacije_ladij = array();
nova_ladja(5, $lokacije_ladij);
nova_ladja(4, $lokacije_ladij);
nova_ladja(3, $lokacije_ladij);
nova_ladja(3, $lokacije_ladij);
nova_ladja(2, $lokacije_ladij);

$_SESSION["lokacije"] = $lokacije_ladij;
$_SESSION["poskusi"] = 1;
?>

<!DOCTYPE html>
<html>

<head>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <title>OSS Ladjice</title>
    <link rel="stylesheet" href="style.css">
    <script src="script.js"></script>
</head>

<body>
    <table></table>
    <button id="reset">Nova igra</button>
    <p></p>
</body>

</html>