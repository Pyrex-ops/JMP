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