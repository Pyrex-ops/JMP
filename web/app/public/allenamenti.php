<?php require_once "/php/private/model/auth/sessione.php";
require_once "/php/private/view/navbar.php";
include_once "/php/private/model/auth/auth.php";
include_once "/php/private/model/user/user.php";
redirect_to_login_if_not_logged_in() ?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Workout Tracker</title>
    <link rel="stylesheet" href="/style/bootstrap.css">
    <link rel="stylesheet" href="/style/jmpit.css">
</head>

<body>
    <?php echo_navbar("allenamenti") ?>
    <h1 class="text-center" style="margin-bottom:10px"> Obiettivo corrente </h1>
    <div class="container mt-5 dashboard-container">
        <div class="card goal-card">
            <div class="card-body">
                <div class="row">
                    <div class="col-5 text-center my-auto">
                        <i class="fas fa-5x" id="training-icon-box"></i>
                    </div>
                    <div class="col-7 text-center">
                        <h5 class="card-title" id="goalDescription"></h5>
                        <p class="card-text" id="goalValue"></p>
                        <button type="button" class="btn btn-primary" data-bs-toggle="modal"
                            data-bs-target="#changeGoalModal">Modifica</button>
                    </div>
                </div>
            </div>
        </div>

        <h1 class="text-center" style="margin-bottom:55px"> Allenamenti </h1>
        <div class="col-md-12">
            <div class="card">
                <div class="card-body text-center">
                    <table class="table table-borderless table-column-width table-trainings">
                        <tbody id="trainingsContainer"></tbody>
                    </table>
                </div>
            </div>
        </div>
    </div>
    </div>

    <!-- Change Goal Modal -->
    <div class="modal fade" id="changeGoalModal" tabindex="-1" role="dialog" aria-labelledby="changeGoalModalLabel"
        aria-hidden="true">
        <div class="modal-dialog" role="document">
            <div class="modal-content">
                <div class="modal-header">
                    <h5 class="modal-title" id="changeGoalModalLabel">Modifica obiettivo</h5>
                    <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                </div>
                <div class="modal-body">
                    <div class="form-group">
                        <label for="goalType">Tipologia:</label>
                        <select class="form-control" id="goalType">
                            <option value="duration">Tempo di allenamento</option>
                            <option value="calories">Numero di calorie bruciate</option>
                            <option value="skips">Numero di salti</option>
                        </select>
                    </div>
                    <div class="form-group">
                        <label for="goalValue">Valore:</label>
                        <div class="d-flex align-items-center">
                            <input type="range" class=" form-range flex-grow-1" id="goalValueSlider" min="1" max="300"
                                value="50" style="width:420%;margin-right:40px">
                            <input type="text" class="form-control" id="goalValueInput" value="50">

                        </div>
                    </div>
                </div>

                <div class="modal-footer">
                    <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Chiudi</button>
                    <button id="confirmGoalBtn" type="button" class="btn btn-primary">Conferma</button>
                </div>
            </div>
        </div>
    </div>

    <script src="https://kit.fontawesome.com/98491d0baf.js" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.bundle.min.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.2/dist/umd/popper.min.js"></script>
    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"></script>

    <script>

        const tipologieAllenamento = [
            { name: 'Numero Mogus Catturati', icon: 'fa-times', max: '50' },
            { name: 'Numero Mogus intervistati', icon: 'fa-dumbbell', max: '100' }
        ];

        const obiettivoCorrente = { name: 'Numero Mogus intervistati', value: '30' };

        function updateCurrentGoal() {
            const goalIcon = document.getElementById("training-icon-box");
            const selectedGoal = tipologieAllenamento.find(goal => goal.name === obiettivoCorrente.name);
            if (selectedGoal) {
                goalIcon.classList.add("fas", selectedGoal.icon); // Add the appropriate class to the icon element
                document.getElementById('goalValueSlider').max = 10;
                document.getElementById('goalValueSlider').value = document.getElementById('goalValueSlider').max / 2;
                document.getElementById('goalValueInput').max = 10;
                document.getElementById('goalValueInput').value = document.getElementById('goalValueSlider').max / 2;
                document.getElementById('goalDescription').textContent = selectedGoal.name;
                document.getElementById('goalValue').textContent = obiettivoCorrente.value;
            }
        }

        updateCurrentGoal();

        // Event listener for goal type select

        // Event listener for goal value input
        document.getElementById('goalValueInput').addEventListener('input', function () {
            var value = parseInt(this.value);
            if (!isNaN(value)) {
                document.getElementById('goalValueSlider').value = value;
            }
        });

        // Event listener for goal value slider
        document.getElementById('goalValueSlider').addEventListener('input', function () {
            var value = parseInt(this.value);
            if (!isNaN(value)) {
                document.getElementById('goalValueInput').value = value;
            }
        });

        // Event listener for confirm goal button
        document.getElementById('confirmGoalBtn').addEventListener('click', function () {
            // Get selected goal type and value
            var goalType = document.getElementById('goalType').value;
            var goalValue = document.getElementById('goalValueSlider').value;

            // Create a new form element
            var form = document.createElement('form');
            form.method = 'post';
            form.action = 'process_goal.php'; // Replace with the actual URL or file path of the PHP page

            // Create hidden input fields for the goal type and value
            var goalTypeInput = document.createElement('input');
            goalTypeInput.type = 'hidden';
            goalTypeInput.name = 'goalType';
            goalTypeInput.value = goalType;
            form.appendChild(goalTypeInput);

            var goalValueInput = document.createElement('input');
            goalValueInput.type = 'hidden';
            goalValueInput.name = 'goalValue';
            goalValueInput.value = goalValue;
            form.appendChild(goalValueInput);

            // Append the form to the document and submit it
            document.body.appendChild(form);
            form.submit();
        });
        // Function to update the goal value display

        // Event listener for goal value input
        document.getElementById('goalValueInput').addEventListener('input', function () {
            var value = parseInt(this.value);
            if (!isNaN(value)) {
                document.getElementById('goalValueSlider').value = value;
            }
        });

        // Event listener for goal value slider
        document.getElementById('goalValueSlider').addEventListener('input', function () {
            var value = parseInt(this.value);
            if (!isNaN(value)) {
                document.getElementById('goalValueInput').value = value;
            }
        });


        // Function to add a workout to the list
        const trainingsContainer = document.getElementById('trainingsContainer');
        const trainingsData = <?php all_trainings() ?>;
        const maxTrainingTime = parseInt(trainingsData.sort(
                function (a, b) {
                    return parseInt(b['duration']) - parseInt(a['duration']);
                }
            )[0]['duration']);

            trainingsData.sort(
                function (a, b) {
                    return parseInt(b['id']) - parseInt(a['id']);
                }
            );

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
    <div class="progress-bar" role="progressbar" style="width: ${100 * parseInt(training.duration) / maxTrainingTime}%;" aria-valuenow="${parseInt(training.duration)}" aria-valuemin="0" aria-valuemax="${maxTrainingTime}">${training.duration}</div>
  `;
            progressCell.appendChild(progressBar);
            row.appendChild(progressCell);

            const goalCell = document.createElement('td');
            goalCell.classList.add('align-middle');
            if (training.goalReached) {
                const starIcon = document.createElement('i');
                starIcon.classList.add('star', 'goal-reached');
                starIcon.textContent = '★';
                goalCell.appendChild(starIcon);
            }
            row.appendChild(goalCell);

            const detailsCell = document.createElement('td');
            const detailsButton = document.createElement('button');
            detailsButton.innerHTML = '<i class="fas fa-search"></i>'; // Use the magnifier icon from Font Awesome
            detailsButton.classList.add('btn', 'btn-primary');
            detailsButton.addEventListener('click', function () {
                // Redirect to the details page with the training session ID as a GET parameter
                window.location.href = 'details.php?id=' + training.id;
            });
            detailsCell.appendChild(detailsButton);
            row.appendChild(detailsCell);

            trainingsContainer.appendChild(row);
        });

    </script>
</body>

</html>