<?php

include_once "/php/private/model/db/dbconnessione.php";

function echo_tipologie_obiettivo(): void
{
    global $database;
    $queryObiettivi = $database->query("SELECT IDCategoria,Descrizione FROM categoriaObiettivo ORDER BY IDCategoria ASC;");
    $arrayObiettivi = [];
    $arrayIcone = ['fa-dumbbell', 'fa-times', 'fa-dumbbell'];
    //1000 salti, 20000 calorie, 1440 minuti
    //ATTENZIONE: Ricorda che il database tratta le durate in SECONDI!
    $arrayLimiti = [1000, 20000, 1440];
    $index = 0;
    while ($riga = $queryObiettivi->fetch_assoc()) {
        $arrayObiettivi[] = ["name" => $riga["Descrizione"], "icon" => $arrayIcone[$index], "max" => $arrayLimiti[$index]];
        $index++;
    }
    echo json_encode($arrayObiettivi);
//    echo "[
//        { name: 'Numero salti', icon: 'fa-dumbbell', max: '50' },
//        { name: 'Numero Mogus Catturati', icon: 'fa-times', max: '50' },
//        { name: 'Numero Mogus intervistati', icon: 'fa-dumbbell', max: '100' }
//    ]";
}

function echo_obiettivo($user)
{
    echo "{ name: 'Numero salti', value: '30' }";
}