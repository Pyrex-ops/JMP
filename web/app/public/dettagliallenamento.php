<?php require_once "/php/private/model/auth/sessione.php";
require_once "/php/private/view/navbar.php";
include_once "/php/private/model/auth/auth.php";
include_once "/php/private/model/user/user.php";
include_once "/php/private/model/allenamenti/allenamenti.php";
redirect_to_login_if_not_logged_in();
if (!isset($_GET["id"])) {
  header("location: /allenamenti");
  exit;
}
$id = $_GET["id"];
if (!check_ownership($id, get_username())) {
  header("location: /allenamenti");
  exit;
}

$allenamento = dettagli_allenamento($id);
?>

<!DOCTYPE html>
<html lang="it">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Allenamenti</title>
  <link rel="stylesheet" href="/style/bootstrap.css">
  <link rel="stylesheet" href="/style/jmpit.css">
</head>

<body>
  <?php echo_navbar("allenamenti") ?>
  <div class="container mt-5 dashboard-container">
    <?php if (!($allenamento["tipoObiettivo"] === "Nessuno")): ?>
      <div class="row">
        <div class"col-md-12">
          <div class="card allenamento-detail-card">
            <div class="card-body">
              <h2 class="card-title text-center">Obiettivo</h2>
              <hr />
              <h3 class="card-title text-center">
                <?php echo $allenamento["tipoObiettivo"] ?>
              </h3>
              <div class="row" style="padding-top:20px">
                <div class="col-6 text-center my-auto">
                  <div id="goalBarContainer"></div>
                </div>
                <div class="col-6 text-center" style="padding-top:40px">
                  <h5 class="card-text">
                    <?php echo $allenamento["valoreRaggiunto"] ?>/
                    <?php echo $allenamento["parametroObiettivo"] ?>
                  </h5>
                </div>
              </div>
              <div class="row" style="padding-top:20px">
                <div class="col-12 text-center">
                  <?php if ($allenamento["valoreRaggiunto"] >= $allenamento["parametroObiettivo"]): ?>
                    <div class="alert alert-success" role="alert">
                      Obiettivo raggiunto. Congratulazioni!
                    </div>
                  <?php else: ?>
                    <div class="alert alert-danger" role="alert">
                      Obiettivo non raggiunto. Non mollare!
                    </div>
                  <?php endif ?>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    <?php endif; ?>
    <div class="row">
      <div class="col-md-6">
        <?php echo_detail_card("Data", $allenamento["data"], "fa-calendar") ?>
      </div>


      <div class="col-md-6">
        <?php echo_detail_card("Durata", $allenamento["durata"] . " minuti", "fa-clock") ?>
      </div>
    </div>
    <div class="row">
      <div class="col-md-6">
        <?php echo_detail_card("Numero di salti", $allenamento["salti"], "fa-person-running") ?>
      </div>


      <div class="col-md-6">
        <?php echo_detail_card("Calorie bruciate", $allenamento["calorie"], "fa-fire") ?>
      </div>
    </div>

    <div class="row">
      <div class="col-md-6">
        <?php echo_detail_card("Salti per minuto", $allenamento["salti"] / $allenamento["durata"], "fa-arrow-trend-up") ?>
      </div>


      <div class="col-md-6">
        <?php echo_detail_card("Calorie per minuto", $allenamento["calorie"] / $allenamento["durata"], "fa-chart-simple") ?>
      </div>
    </div>
    <div class="row">
      <div class="col-md-12 text-center" style="padding-top:40px;padding-bottom:60px">
        <button onclick="location.href = '/allenamenti';" class="btn btn-primary"
          style="width:300px;padding-top:10px;padding-bottom:10px">Indietro</button>
      </div>

    </div>
  </div>
  </div>

  <!-- Change Goal Modal -->

  <script src="https://kit.fontawesome.com/98491d0baf.js" crossorigin="anonymous"></script>
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.bundle.min.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.2/dist/umd/popper.min.js"></script>
  <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"></script>
  <script src="/script/progressbar.js"></script>
  <?php if (!($allenamento["tipoObiettivo"] === "Nessuno")): ?>
    <script>

      // Assuming we have an empty <div id="container"></div> in
      // HTML
      let percentualeRaggiungimento = <?php echo $allenamento["valoreRaggiunto"] / $allenamento["parametroObiettivo"] ?>;
      if (percentualeRaggiungimento > 1) {
        percentualeRaggiungimento = 1;
      }
      var bar = new ProgressBar.Circle('#goalBarContainer', {
        strokeWidth: 10,
        easing: 'easeInOut',
        duration: 1400,
        color: '#198754',
        trailColor: '#eee',
        trailWidth: 1,
        svgStyle: null,
        text: {
          value: `${Math.trunc(percentualeRaggiungimento * 100)}%`,
          alignToBottom: false
        },
      });

      bar.text.style.color = '#000';
      bar.text.style.fontFamily = '"Raleway", Helvetica, sans-serif';
      bar.text.style.fontSize = '2rem';
      bar.animate(percentualeRaggiungimento);  // Number from 0.0 to 1.0
    </script>
  <?php endif; ?>
</body>

</html>