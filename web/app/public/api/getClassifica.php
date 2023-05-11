<?php

require_once '../db/dbconnessione.php';
header('Content-Type: application/json');

if (isset($database)) {
    if (isset($_GET['tipo'])) {
        if ($_GET['tipo'] == 1) {
            //Numero salti utente
<<<<<<< HEAD:web/app/api/getClassifica.php
            //TODO: Prendi i dati dalle view
            $numSalti = $database->query("SELECT * FROM classificanumsalti");
            $arraySalti = array();
=======
            $numSalti = $database->query('SELECT utente.username, SUM(valore) as numSalti 
                                        FROM misura
                                            JOIN allenamento ON misura.IDAllenamento = allenamento.IDAllenamento
                                            JOIN utente ON allenamento.IDUtente = utente.IDUtente
                                        GROUP BY allenamento.IDAllenamento
                                        ORDER BY numSalti DESC;
                                ');
            $arraySalti = [];
>>>>>>> e2c8ce5daa4a3ce3ab6407ed2f918cc6f3f34fcc:web/app/public/api/getClassifica.php
            while ($riga = $numSalti->fetch_assoc()) {
                $arraySalti[] = $riga;
            }
            http_response_code(200);
            echo json_encode(['stato' => 'ok', 'classificaSalti' => $arraySalti]);
            exit;
        } elseif ($_GET['tipo'] == 2) {
            //Durata allenamento
<<<<<<< HEAD:web/app/api/getClassifica.php
            $durataAllenamenti = $database->query("SELECT * FROM classificadurata");

            $arrayDurata = array();
=======
            $durataAllenamenti = $database->query('SELECT utente.username, UNIX_TIMESTAMP(MAX(timestamp)) - UNIX_TIMESTAMP(MIN(timestamp)) durataAllenamento
                                                 FROM misura
                                                    JOIN allenamento ON misura.IDAllenamento = allenamento.IDAllenamento
                                                    JOIN utente ON allenamento.IDUtente = utente.IDUtente
                                                 GROUP BY misura.IDAllenamento
                                                 ORDER BY durataAllenamento DESC;
                                        ');
            $arrayDurata = [];
>>>>>>> e2c8ce5daa4a3ce3ab6407ed2f918cc6f3f34fcc:web/app/public/api/getClassifica.php
            while ($riga = $durataAllenamenti->fetch_assoc()) {
                $arrayDurata[] = $riga;
            }
            http_response_code(200);
            echo json_encode(['stato' => 'ok', 'classificaDurata' => $arrayDurata]);
            exit;
        } else {
            http_response_code(401);
            echo json_encode(['stato' => 'errore']);
            exit;
        }
    }
} else {
    http_response_code(401);
    echo json_encode(['stato' => 'errore']);
    exit;
}
