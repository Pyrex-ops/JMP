<?php

include_once "/php/private/model/db/dbconnessione.php";

function echo_tipologie_obiettivo(): void
{
    global $database;
    $queryObiettivi = $database->query("SELECT IDCategoria,Descrizione FROM categoriaObiettivo ORDER BY IDCategoria ASC;");
    $arrayObiettivi = [];
    $arrayIcone = ['fa-person-running', 'fa-fire', 'fa-clock'];
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

function dettagli_allenamento($id): ?array
{
    global $database;
    $queryDettagli = $database->prepare("SELECT
    allenamento.IDAllenamento AS 'IdAllenam',
    DATE_FORMAT(MIN(misura.timestamp),'%d/%m/%Y') AS 'data',
    (
        UNIX_TIMESTAMP(MAX(misura.timestamp)) - UNIX_TIMESTAMP(MIN(misura.timestamp))
    ) AS `durata`,
    SUM(misura.numeroSalti) AS 'salti',
    SUM(misura.numeroSalti) * utente.peso * 0.1 * 2.205 AS 'calorie',
    obiettivo.IDCategoria AS `tipoObiettivo`,obiettivo.parametro AS 'parametroObiettivo',
    (
        CASE WHEN obiettivo.IDCategoria = 1 THEN(
        SELECT
            SUM(misura.numeroSalti)
        FROM
            misura
        WHERE
            misura.IDAllenamento = IDAllenam
    ) WHEN obiettivo.IDCategoria = 2 THEN(
    SELECT
        SUM(misura.numeroSalti) * utente.peso * 0.1 * 2.205
    FROM
        misura
    JOIN allenamento ON misura.IDAllenamento = allenamento.IDAllenamento
    JOIN obiettivo ON allenamento.IDObiettivo = obiettivo.IDObiettivo
    JOIN utente ON allenamento.IDUtente = utente.IDUtente
    WHERE
        allenamento.IDAllenamento = IdAllenam
    GROUP BY
        allenamento.IDAllenamento
) WHEN obiettivo.IDCategoria = 3 THEN(
    SELECT
        (
            UNIX_TIMESTAMP(MAX(misura.timestamp)) - UNIX_TIMESTAMP(MIN(misura.timestamp))
        ) / 60
    FROM
        misura
    JOIN allenamento ON misura.IDAllenamento = allenamento.IDAllenamento
    JOIN obiettivo ON allenamento.IDObiettivo = obiettivo.IDObiettivo
    JOIN utente ON allenamento.IDUtente = utente.IDUtente
    WHERE
        allenamento.IDAllenamento = IdAllenam
    GROUP BY
        allenamento.IDAllenamento
) ELSE 0
    END
) AS valoreRaggiunto
FROM
    allenamento
JOIN utente ON utente.IDUtente = allenamento.IDUtente
JOIN misura ON misura.IDAllenamento = allenamento.IDAllenamento
LEFT JOIN obiettivo ON allenamento.IDObiettivo = obiettivo.IDObiettivo 
WHERE
    allenamento.IDAllenamento = ?
GROUP BY
    allenamento.IDAllenamento
ORDER BY
    IDAllenam
DESC;");
    $queryDettagli->bind_param("i", $id);
    $queryDettagli->execute();
    $ris = $queryDettagli->get_result();
    while ($riga = $ris->fetch_assoc()) {
        $tipo = match ($riga["tipoObiettivo"]) {
            1 => "Numero salti",
            2 => "Calorie bruciate",
            3 => "Durata allenamento",
            default => "Nessuno",
        };
        if($riga["durata"] <= 60  ) {
            $riga["durata"] = 60;
        }
        if (isset($riga["parametroObiettivo"])) {
            if(($riga["tipoObiettivo"] == 3) && ($riga["valoreRaggiunto"] <= 1)) {
                $riga["valoreRaggiunto"] = 1;
            }
            $dettagli = ["data" => $riga["data"], "durata" => $riga["durata"]/60, "salti" => $riga["salti"],
                "calorie" => $riga["calorie"], "percentualeObiettivo" => (int)($riga["valoreRaggiunto"] / $riga["parametroObiettivo"]) * 100,
                "tipoObiettivo" => $tipo, "parametroObiettivo" => $riga["parametroObiettivo"], "valoreRaggiunto" => $riga["valoreRaggiunto"]];
        } else {

            $dettagli = ["data" => $riga["data"], "durata" => $riga["durata"]/60, "salti" => $riga["salti"],
                "calorie" => $riga["calorie"], "percentualeObiettivo" => 0,
                "tipoObiettivo" => $tipo, "parametroObiettivo" => 0, "valoreRaggiunto" => $riga["valoreRaggiunto"]];
        }
    }
//    $details = ["data" => "25/04/1999", "durata" => 50, "salti" => 801, "calorie" => 120,
//        "percentualeObiettivo" => 70, "tipoObiettivo" => "Calorie bruciate",
//        "parametroObiettivo" => 800, "valoreRaggiunto" => 700];
    return $dettagli;
}

function check_ownership($idAllenamento, $username)
{
    return true;
}

function echo_detail_card($categoria, $parametro, $icona)
{
    if($categoria === "Data") {
        $parametroFormattato = $parametro;
    } 
    else if($categoria === "Durata") {
        $parametroFormattato = round(floatval($parametro),1)." min";
    }
    else {
        $parametroFormattato = round(floatval($parametro),1);
    }
    echo('<div class="card allenamento-detail-card">
    <div class="card-body">
      <div class="row">
        <div class="col-5 text-center my-auto">
          <i class="fas fa-5x ' . $icona . '"aria-hidden="true"></i>
        </div>
        <div class="col-7 text-center">
          <h4 class="card-title"">' . $categoria . '</h4>
          <h5 class="card-text">' . $parametroFormattato . '</h5>
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