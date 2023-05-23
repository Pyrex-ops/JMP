<?php

include_once "/php/private/model/db/dbconnessione.php";

function echo_tipologie_obiettivo(): void
{
    global $database;
    $queryObiettivi = $database->query("SELECT IDCategoria,Descrizione FROM categoriaObiettivo ORDER BY IDCategoria ASC;");
    $arrayObiettivi = [];
    $arrayIcone = ['fa-dumbbell', 'fa-fire', 'fa-clock'];
    //1000 salti, 20000 calorie, 1440 minuti
    //ATTENZIONE: Ricorda che il database tratta le durate in SECONDI!
    $arrayLimiti = [1000, 20000, 1440];
    $index = 0;
    $arrayObiettivi[] = ["name" => "Nessuno", "icon" => "fa-times", "max" => 0];
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
    echo "{ name: 'Nessuno', value: '30' }";
}

function dettagli_allenamento($id) {
    $details = ["data" => "25/04/1999","durata" => 50, "salti" => 801,"calorie" => 120, 
    "percentualeObiettivo" => 70,"tipoObiettivo" => "Calorie bruciate",
    "parametroObiettivo" => 800 , "valoreRaggiunto" => 700];
    return $details;
}

function check_ownership($idAllenamento , $username) {
    return true;
}

function echo_detail_card($categoria,$parametro,$icona) {
    echo('<div class="card allenamento-detail-card">
    <div class="card-body">
      <div class="row">
        <div class="col-5 text-center my-auto">
          <i class="fas fa-5x '.$icona.'"aria-hidden="true"></i>
        </div>
        <div class="col-7 text-center">
          <h4 class="card-title"">'.$categoria.'</h4>
          <h5 class="card-text">'.$parametro.'</h5>
        </div>
      </div>
    </div>
  </div>');
}

function echo_classifica_durata() {
  echo "[
           { name: 'Joecom', durata : 900 },
           { name: 'Marco', durata : 400 },
           { name: 'Giuseppe', durata : 200 }
       ]";
}

function echo_classifica_salti() {
  echo "[
           { name: 'Marco', salti : 11000 },
           { name: 'Giuseppe', salti : 3000 },
           { name: 'Joecom', salti : 2000 }
       ]";
}