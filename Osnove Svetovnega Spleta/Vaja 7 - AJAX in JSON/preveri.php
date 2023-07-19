<?php
    session_start();

    if(!isset($_SESSION["poskusi"])){
        $_SESSION["poskusi"] = 0;
    }
    
    $_SESSION["poskusi"]++;

    $poskusi = $_SESSION['poskusi'];
    $lokacije = $_SESSION["lokacije"];

    $updated_lokacije = array();
    
    $x = (int) $_GET["x"];
    $y = (int) $_GET["y"];

    $konec = false;
    $isHit= false;
    
    foreach($lokacije as $arr){
        if($arr["x"] == $x && $arr["y"] == $y){
            $isHit = true;
        }else{
            array_push($updated_lokacije,$arr);
        }
    }

    $_SESSION["lokacije"] = $updated_lokacije;

    if(count($_SESSION["lokacije"])<1){
        $konec=true;
    }
    
    $odgovor = array(
        "isHit" => $isHit,
        "poskusi" => $poskusi,
        "konec" => $konec,
    );

    $json = json_encode($odgovor);
    
    echo $json

?>