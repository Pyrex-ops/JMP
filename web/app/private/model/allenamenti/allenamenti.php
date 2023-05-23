<?php

include_once "/php/private/model/db/dbconnessione.php";

function echo_tipologie_obiettivo() : void {
    echo "[

        { name: 'Numero salti', icon: 'fa-dumbbell', max: '50' },
        { name: 'Numero Mogus Catturati', icon: 'fa-times', max: '50' },
        { name: 'Numero Mogus intervistati', icon: 'fa-dumbbell', max: '100' }
    ]";
}

function echo_obiettivo($user) {
    echo "{ name: 'Numero salti', value: '30' }";
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