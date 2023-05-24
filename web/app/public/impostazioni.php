<?php require_once "/php/private/model/auth/sessione.php";
require_once "/php/private/view/navbar.php";
include_once "/php/private/model/auth/auth.php";
include_once "/php/private/model/dispositivo/dispositivo.php";
redirect_to_login_if_not_logged_in() ?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="/style/bootstrap.css">
    <link rel="stylesheet" href="/style/jmpit.css">
    <title>Impostazioni Utente</title>
    <style>
.toggle-switch {
  position: relative;
  display: inline-block;
  width: 80px;
  height: 40px;
  cursor: pointer;
}

.toggle-switch input[type="checkbox"] {
  display: none;
}

.toggle-switch-background {
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: #f5f5f5;
  border-radius: 20px;
  box-shadow: inset 0 0 0 2px #f0f0f0;
  transition: background-color 0.3s ease-in-out;
}

.toggle-switch-handle {
  position: absolute;
  top: 5px;
  left: 5px;
  width: 30px;
  height: 30px;
  background-color: #fff;
  border-radius: 50%;
  box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2);
  transition: transform 0.3s ease-in-out;
}

.toggle-switch::before {
  content: "";
  position: absolute;
  top: -25px;
  right: -35px;
  font-size: 12px;
  font-weight: bold;
  color: #aaa;
  text-shadow: 1px 1px #fff;
  transition: color 0.3s ease-in-out;
}

.toggle-switch input[type="checkbox"]:checked + .toggle-switch-handle {
  transform: translateX(45px);
  box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2), 0 0 0 3px #05c46b;
}

.toggle-switch input[type="checkbox"]:checked + .toggle-switch-background {
  background-color: #05c46b;
  box-shadow: inset 0 0 0 2px #04b360;
}

.toggle-switch input[type="checkbox"]:checked + .toggle-switch:before {
  content: "On";
  color: #05c46b;
  right: -15px;
}

.toggle-switch input[type="checkbox"]:checked + .toggle-switch-background .toggle-switch-handle {
  transform: translateX(40px);
}

    </style>
</head>

<body>
    <?php echo_navbar("impostazioni") ?>
    <div class="container">
        <? if (isset($_SESSION["aggiunta_corda_error_message"])) {
            // Display error message in a Bootstrap alert
            echo '<div class="alert alert-danger" role="alert">' . $_SESSION["aggiunta_corda_error_message"] . '</div>';
            // Unset the login error variable
            unset($_SESSION["aggiunta_corda_error_message"]);
        } ?>
        <? if (isset($_SESSION["rimozione_corda_error_message"])) {
            // Display error message in a Bootstrap alert
            echo '<div class="alert alert-danger" role="alert">' . $_SESSION["rimozione_corda_error_message"] . '</div>';
            // Unset the login error variable
            unset($_SESSION["rimozione_corda_error_message"]);
        } ?>
        <? if (isset($_SESSION["eliminazione_account_error_message"])) {
            // Display error message in a Bootstrap alert
            echo '<div class="alert alert-danger" role="alert">' . $_SESSION["eliminazione_account_error_message"] . '</div>';
            // Unset the login error variable
            unset($_SESSION["eliminazione_account_error_message"]);
        } ?>
        <? if (isset($_SESSION["cambio_password_error_message"])) {
            // Display error message in a Bootstrap alert
            echo '<div class="alert alert-danger" role="alert">' . $_SESSION["cambio_password_error_message"] . '</div>';
            // Unset the login error variable
            unset($_SESSION["cambio_password_error_message"]);
        } ?>
        <? if (isset($_SESSION["aggiunta_nuova_corda"])) {
            // Display error message in a Bootstrap alert
            echo '<div class="alert alert-success" role="alert">' . "La corda è stata aggiunta con successo al tuo account." . '</div>';
            // Unset the login error variable
            unset($_SESSION["aggiunta_nuova_corda"]);
        } ?>
        <? if (isset($_SESSION["cambiata_password"])) {
            // Display error message in a Bootstrap alert
            echo '<div class="alert alert-success" role="alert">' . "Password cambiata con successo." . '</div>';
            // Unset the login error variable
            unset($_SESSION["cambiata_password"]);
        } ?>
        <div class="row mt-5">
            <div class="col-md-6 mx-auto">
                <div class="card text-center username-card first-card">
                    <div class="card-body">
                        <div class="user-profile-picture">
                            <img src=<?php echo_profile_picture(); ?> alt="User Picture" width="200" height="200">
                        </div>
                        <h3 class="card-title">
                            <?php echo_username(); ?>
                        </h3>
                        <hr/>
                        <form action="/php/aggiornaimpostazioni.php" method="POST">
                            <div class="form-group">
                                <label for="new_password">Partecipazione classifica:</label>
                                <label class="toggle-switch">
  <input type="checkbox">
  <div class="toggle-switch-background">
    <div class="toggle-switch-handle"></div>
  </div>
</label>

                            </div>
                            <div class="form-group">
                                <label for="confirm_password">Peso (kg)</label>
                                <input type="password" class="form-control" id="confirm_password"
                                    name="confirm_password" required>
                            </div>
                            <div class="text-center"> <!-- Wrap buttons in a div with 'text-center' class -->
                                <button type="submit" class="btn btn-primary">Salva impostazioni</button>
                            </div>
                        </form>
                        <hr/>
                        <button type="button" class="btn btn-danger mt-3" data-bs-toggle="modal"
                            data-bs-target="#eliminaAccountModal">Elimina account</button>
                    </div>
                </div>
            </div>
            <div class="col-md-6">
                <div class="card">
                    <div class="card-body">
                        <h5 class="card-title text-center">Cambia password</h5>
                        <form action="/php/cambiapassword.php" method="POST">
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
                <?php if (!has_registered_device()): ?>
                    <div class="card mt-4">
                        <div class="card-body">
                            <h5 class="card-title text-center">Registrazione corda</h5>
                            <div class="text-center">
                                <button type="button" class="btn btn-primary mt-3" data-bs-toggle="modal"
                                    data-bs-target="#addDeviceModal">Aggiungi</button>
                            </div>
                        </div>
                    </div>
                <?php else: ?>
                    <div class="card mt-4">
                        <div class="card-body">
                            <h5 class="card-title text-center">Corda registrata</h5>
                            <ul class="list-group">
                                <li class="list-group-item text-center">
                                    <?php echo (get_registered_device()) ?>
                                </li>
                            </ul>
                            <div class="text-center">
                                <button type="button" class="btn btn-danger mt-3" data-bs-toggle="modal"
                                    data-bs-target="#rimuoviCordaModal">Rimuovi corda</button>
                            </div>
                        </div>
                    </div>
                <?php endif; ?>
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
                    <form action="/php/aggiungicorda.php" method="POST">
                        <div class="form-group">
                            <label for="device_code">Codice corda</label>
                            <input type="text" class="form-control" id="IDCorda" name="IDCorda" required>
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

    <div class="modal fade" id="eliminaAccountModal" tabindex="-1" role="dialog"
        aria-labelledby="eliminaAccountModalLabel" aria-hidden="true">
        <div class="modal-dialog" role="document">
            <div class="modal-content">
                <div class="modal-header">
                    <h5 class="modal-title" id="addDeviceModalLabel">Eliminazione account</h5>
                    <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                </div>
                <div class="modal-body">
                    <div class="text-center">
                        <label for="device_code">Sei davvero sicuro di voler eliminare il tuo account?</label>
                        <div class="alert alert-danger" role="alert" style="margin-top:20px">
                            Tutti i tuoi dati andranno persi per sempre.
                        </div>
                        <form action="/php/eliminaaccount.php" method="POST">
                            <div class="text-center">
                                <button type="submit" style="margin-bottom:20px"
                                    class="btn btn-danger">Conferma</button>
                            </div>
                        </form>
                        <div class="modal-footer">
                            <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Chiudi</button>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <div class="modal fade" id="rimuoviCordaModal" tabindex="-1" role="dialog" aria-labelledby="rimuoviCordaModal"
        aria-hidden="true">
        <div class="modal-dialog" role="document">
            <div class="modal-content">
                <div class="modal-header">
                    <h5 class="modal-title" id="addDeviceModalLabel">Rimozione corda</h5>
                    <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                </div>
                <div class="modal-body">
                    <div class="text-center">
                        <label for="device_code">Sei davvero sicuro di voler rimuovere la corda dal tuo account?</label>
                        <div class="alert alert-info" role="alert" style="margin-top:20px">
                            Per continuare ad utilizzarla, dovrai registrarla a un nuovo account.
                        </div>
                        <form action="/php/rimuovicorda.php" method="POST">
                            <div class="text-center">
                                <button type="submit" style="margin-bottom:20px"
                                    class="btn btn-danger">Conferma</button>
                            </div>
                        </form>
                        <div class="modal-footer">
                            <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Chiudi</button>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.bundle.min.js"></script>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.4/jquery.min.js"></script>
</body>

</html>