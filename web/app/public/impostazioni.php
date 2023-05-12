<?php require_once "/php/private/model/auth/sessione.php";
require_once "/php/private/view/navbar.php";
include_once "/php/private/model/auth/auth.php";
redirect_to_login_if_not_logged_in() ?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="/style/bootstrap.css">
    <link rel="stylesheet" href="/style/jmpit.css">
    <title>Impostazioni Utente</title>
</head>

<body>
    <?php echo_navbar("impostazioni") ?>
    <div class="container">
        <div class="row mt-4">
        <div class="col-md-4 mx-auto">
        <div class="card text-center username-card first-card">
          <div class="card-body">
            <div class="user-profile-picture">
              <img src=<?php echo_profile_picture();?> alt="User Picture" width="200" height="200">
            </div>
            <h3 class="card-title"><?php echo_username();?></h5>
          </div>
        </div>
      </div>
            <div class="col-md-8">
                <div class="card">
                    <div class="card-body">
                        <h5 class="card-title text-center">Cambia password</h5>
                        <form action="update_password.php" method="POST">
                            <div class="form-group">
                                <label for="current_password">Password attuale</label>
                                <input type="password" class="form-control" id="current_password"
                                    name="current_password" required>
                            </div>
                            <div class="form-group">
                                <label for="new_password">Nuova password</label>
                                <input type="password" class="form-control" id="new_password" name="new_password"
                                    required>
                            </div>
                            <div class="form-group">
                                <label for="confirm_password">Conferma nuova password</label>
                                <input type="password" class="form-control" id="confirm_password"
                                    name="confirm_password" required>
                            </div>
                            <div class="text-center"> <!-- Wrap buttons in a div with 'text-center' class -->
                                <button type="submit" class="btn btn-primary">Salva password</button>
                            </div>
                        </form>
                    </div>
                </div>
                <div class="card mt-4">
                    <div class="card-body">
                        <h5 class="card-title text-center">Corde registrate</h5>
                        <ul class="list-group">
                            <li class="list-group-item">The momogus</li>
                            <li class="list-group-item">Mosmugus</li>
                            <li class="list-group-item">Le troll</li>
                        </ul>
                        <div class="text-center">
                            <button type="button" class="btn btn-primary mt-3" data-bs-toggle="modal"
                                data-bs-target="#addDeviceModal">Aggiungi corda</button>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <!-- Add Device Modal -->
    <div class="modal fade" id="addDeviceModal" tabindex="-1" role="dialog" aria-labelledby="addDeviceModalLabel"
        aria-hidden="true">
        <div class="modal-dialog" role="document">
            <div class="modal-content">
                <div class="modal-header">
                    <h5 class="modal-title" id="addDeviceModalLabel">Aggiungi nuova corda</h5>
                    <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                </div>
                <div class="modal-body">
                    <form action="add_device.php" method="POST">
                        <div class="form-group">
                            <label for="device_code">Codice corda</label>
                            <input type="text" class="form-control" id="device_code" name="device_code" required>
                        </div>
                        <button type="submit" class="btn btn-primary">Aggiungi corda</button>
                    </form>
                </div>
                <div class="modal-footer">
                    <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Chiudi</button>
                </div>
            </div>
        </div>
    </div>

    <!-- Success Modal -->
    <div class="modal fade" id="successModal" tabindex="-1" role="dialog" aria-labelledby="successModalLabel"
        aria-hidden="true">
        <div class="modal-dialog" role="document">
            <div class="modal-content">
                <div class="modal-header">
                    <h5 class="modal-title" id="successModalLabel">Successful!</h5>
                    <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                        <span aria-hidden="true">&times;</span>
                    </button>
                </div>
                <div class="modal-body">
                    <p>Your device has been successfully added.</p>
                </div>
                <div class="modal-footer">
                    <button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
                </div>
            </div>
        </div>
    </div>

    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.bundle.min.js"></script>
    <script>
        $(document).ready(function () {
            // Check if the device addition was successful
            <?php if (true): ?>
                $('#successModal').modal('show');
            <?php endif; ?>
        });
    </script>
</body>

</html>