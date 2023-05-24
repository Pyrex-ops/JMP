<?php require_once "/php/private/model/auth/sessione.php";
require_once "/php/private/view/navbar.php";
include_once "/php/private/model/auth/auth.php";
include_once "/php/private/model/user/user.php";
include_once "/php/private/model/allenamenti/allenamenti.php";
redirect_to_login_if_not_logged_in() ?>

<!DOCTYPE html>
<html lang="it">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Classifica</title>
    <link rel="stylesheet" href="/style/bootstrap.css">
    <link rel="stylesheet" href="/style/jmpit.css">
    <style>
        .checkbox {
            opacity: 0;
            position: absolute;
        }

        .label {
            background-color: #198754;
            border-radius: 50px;
            cursor: pointer;
            display: flex;
            align-items: center;
            justify-content: space-between;
            padding: 5px;
            position: relative;
            height: 26px;
            width: 50px;
            transform: scale(1.5);
        }

        .label .ball {
            background-color: #fff;
            border-radius: 50%;
            position: absolute;
            top: 2px;
            left: 2px;
            height: 22px;
            width: 22px;
            transform: translateX(0px);
            transition: transform 0.2s linear;
        }

        .checkbox:checked+.label .ball {
            transform: translateX(24px);
        }
    </style>
</head>

<body>
    <?php echo_navbar("classifica") ?>
    <div class="container mt-5 dashboard-container">

        <div class="col-m-12" style="padding-bottom:40px">
            <div class="container d-flex justify-content-center align-items-center">
                <div class="one-quarter" id="switch">
                    <input type="checkbox" class="checkbox" id="chk" />
                    <label class="label" for="chk">
                        <i class="fas fa-person-running" style="color: #fff;"></i>
                        <i class="fas fa-clock" style="color: #fff;"></i>
                        <div class="ball"></div>
                    </label>
                </div>
            </div>
        </div>
        <h1 class="text-center" id="titoloClassifica" style="margin-bottom:30px"> Classifica durata</h1>
        <div class="col-md-12">
            <div class="card" id="durataCard">
                <div class="card-body text-center">
                    <table class="table table-borderless table-classifica">
                        <thead>
                            <tr>
                                <th><i class='fa fa-user'></i> </th>
                                <th><i class="fa fa-chart-simple"></i></th>
                                <th><i class="fas fa-clock"></i></th>
                            </tr>
                        </thead>
                        <tbody id="classificaDurataContainer"></tbody>
                    </table>
                </div>
            </div>
        </div>
        <div class="col-md-12">
            <div class="card collapse" id="saltiCard">
                <div class="card-body text-center">
                    <table class="table table-borderless table-classifica">
                        <thead>
                            <tr>
                                <th><i class='fa fa-user'></i> </th>
                                <th><i class="fa fa-chart-simple"></i></th>
                                <th><i class="fas fa-person-running"></i></th>
                            </tr>
                        </thead>
                        <tbody id="classificaSaltiContainer"></tbody>
                    </table>
                </div>
            </div>
        </div>
    </div>

    <script src="https://kit.fontawesome.com/98491d0baf.js" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.bundle.min.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.2/dist/umd/popper.min.js"></script>
    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"></script>
    <script>
        let trainingsContainer = document.getElementById('classificaDurataContainer');
        let trainingsData = <?php echo_classifica_durata() ?>;
        let maxTrainingTime = parseInt(trainingsData.sort(
            function (a, b) {
                return parseInt(b['durata']) - parseInt(a['durata']);
            }
        )[0]['durata']);

        trainingsData.sort(
            function (a, b) {
                return parseInt(b['durata']) - parseInt(a['durata']);
            }
        );
        if (maxTrainingTime === 0) {
            maxTrainingTime = 1;
        }

        trainingsData.forEach(training => {
            const row = document.createElement('tr');
            row.classList.add('my-auto');

            const titleCell = document.createElement('td');
            titleCell.classList.add('align-middle');
            titleCell.textContent = training.name;
            row.appendChild(titleCell);

            const progressCell = document.createElement('td');
            progressCell.classList.add('align-middle');
            const progressBar = document.createElement('div');
            progressBar.classList.add('progress');
            progressBar.style.height = '20px';
            progressBar.innerHTML = `
    <div class="progress-bar" role="progressbar" style="width: ${100 * parseInt(training.durata) / maxTrainingTime}%;" aria-valuenow="${parseInt(training.durata)}" aria-valuemin="0" aria-valuemax="${maxTrainingTime}"></div>
  `;
            progressCell.appendChild(progressBar);
            row.appendChild(progressCell);

            const valueCell = document.createElement('td');
            valueCell.classList.add('align-middle');
            valueCell.textContent = `${training.durata} min`;
            row.appendChild(valueCell);

            trainingsContainer.appendChild(row);
        });
        trainingsContainer = document.getElementById('classificaSaltiContainer');
        trainingsData = <?php echo_classifica_salti() ?>;
        maxTrainingTime = parseInt(trainingsData.sort(
            function (a, b) {
                return parseInt(b['salti']) - parseInt(a['salti']);
            }
        )[0]['salti']);

        trainingsData.sort(
            function (a, b) {
                return parseInt(b['salti']) - parseInt(a['salti']);
            }
        );
        if (maxTrainingTime === 0) {
            maxTrainingTime = 1;
        }

        trainingsData.forEach(training => {
            const row = document.createElement('tr');
            row.classList.add('my-auto');

            const titleCell = document.createElement('td');
            titleCell.classList.add('align-middle');
            titleCell.textContent = training.name;
            row.appendChild(titleCell);

            const progressCell = document.createElement('td');
            progressCell.classList.add('align-middle');
            const progressBar = document.createElement('div');
            progressBar.classList.add('progress');
            progressBar.style.height = '20px';
            progressBar.innerHTML = `
    <div class="progress-bar" role="progressbar" style="width: ${100 * parseInt(training.salti) / maxTrainingTime}%;" aria-valuenow="${parseInt(training.salti)}" aria-valuemin="0" aria-valuemax="${maxTrainingTime}"></div>
  `;
            progressCell.appendChild(progressBar);
            row.appendChild(progressCell);

            const valueCell = document.createElement('td');
            valueCell.classList.add('align-middle');
            valueCell.textContent = `${training.salti}`;
            row.appendChild(valueCell);

            trainingsContainer.appendChild(row);
        });

        $('#chk').change(function(){
    if(this.checked) {
        const durataCard =document.getElementById("durataCard");
        durataCard.classList.add("collapse");
        const saltiCard =document.getElementById("saltiCard");
        saltiCard.classList.remove("collapse");
        const titoloClassifica = document.getElementById("titoloClassifica");
        titoloClassifica.textContent = "Classifica salti";
    }
    else {
        const durataCard =document.getElementById("durataCard");
        durataCard.classList.remove("collapse");
        const saltiCard =document.getElementById("saltiCard");
        saltiCard.classList.add("collapse");
        titoloClassifica.textContent = "Classifica durata";
    }
});

    </script>

</body>

</html>