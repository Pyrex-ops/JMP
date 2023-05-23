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
</head>

<body>
    <?php echo_navbar("classifica") ?>
    <div class="container mt-5 dashboard-container">

        <h1 class="text-center" style="margin-bottom:55px"> Classifica </h1>
        <div class="col-md-12">
            <div class="card">
                <div class="card-body text-center">
                    <table class="table table-borderless table-trainings">
                        <thead>
                            <tr>
                                <th><i class='fa fa-calendar'></i> </th>
                                <th><i class="fa fa-clock"></i></th>
                                <th><i class="fas fa-star"></i></th>
                                <th><i class="fa-solid fa-magnifying-glass"></i></th>
                            </tr>
                        </thead>
                        <tbody id="trainingsContainer"></tbody>
                    </table>
                </div>
            </div>
        </div>
        <div class="col-md-12">
            <div class="card">
                <div class="card-body text-center">
                    <table class="table table-borderless table-column-width table-trainings">
                        <thead>
                            <tr>
                                <th><i class='fa fa-calendar'></i> </th>
                                <th><i class="fa fa-clock"></i></th>
                                <th><i class="fas fa-star"></i></th>
                                <th><i class="fa-solid fa-magnifying-glass"></i></th>
                            </tr>
                        </thead>
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
                            <option value="">Seleziona</option>
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


</body>

</html>