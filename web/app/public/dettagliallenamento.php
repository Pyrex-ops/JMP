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
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Allenamenti</title>
  <link rel="stylesheet" href="/style/bootstrap.css">
  <link rel="stylesheet" href="/style/jmpit.css">
  <style>
.mt-100{
  margin-top: 200px;
}
.progress {
  width: 100px;
  height: 100px !important;
  float: left; 
  line-height: 150px;
  background: none;
  margin: 0px;
  box-shadow: none;
  position: relative;
}
.progress:after {
  content: "";
  width: 100%;
  height: 100%;
  border-radius: 50%;
  border: 12px solid #fff;
  position: absolute;
  top: 0;
  left: 0;
}
.progress>span {
  width: 50%;
  height: 100%;
  overflow: hidden;
  position: absolute;
  top: 0;
  z-index: 1;
}
.progress .progress-left {
  left: 0;
}
.progress .progress-bar {
  width: 100%;
  height: 100%;
  background: none;
  border-width: 15px;
  border-style: solid;
  position: absolute;
  top: 0;
}
.progress .progress-left .progress-bar {
  left: 100%;
  border-top-right-radius: 80px;
  border-bottom-right-radius: 80px;
  border-left: 0;
  -webkit-transform-origin: center left;
  transform-origin: center left;
}
.progress .progress-right {
  right: 0;
}
.progress .progress-right .progress-bar {
  left: -100%;
  border-top-left-radius: 80px;
  border-bottom-left-radius: 80px;
  border-right: 0;
  -webkit-transform-origin: center right;
  transform-origin: center right;
  animation: loading 1.8s linear forwards;
}
.progress .progress-value {
  width: 90%;
  height: 90%;
  border-radius: 50%;
  background: #fff;
  font-size: 25px;
  color: #000;
  line-height: 90px;
  text-align: center;
  position: absolute;
  top: 7px;
  left: 7px;
}
.progress.blue .progress-bar {
  border-color: #198754;
}
.progress.blue .progress-left .progress-bar {
  animation: loading-1 1.5s linear forwards 1.8s;
}
.progress.yellow .progress-bar {
  border-color: #fdba04;
}
.progress.yellow .progress-right .progress-bar {
  animation: loading 1.8s linear forwards;
}
.progress.yellow .progress-left .progress-bar {
  animation: none;
}
@keyframes loading {
  0% {
    -webkit-transform: rotate(0deg);
    transform: rotate(0deg);
  }
  100% {
    -webkit-transform: rotate(<?php echo($allenamento["percentualeObiettivo"]*1.8)?>deg);
    transform: rotate(<?php echo($allenamento["percentualeObiettivo"]*1.8)?>deg);
  }
}
    </style>
</head>

<body>
  <?php echo_navbar("allenamenti") ?>
  <h1 class="text-center"> Dettagli allenamento </h1>
  <div class="container mt-5 dashboard-container">
    <div class="row">
      <div class="col-md-6">
        <?php echo_detail_card("Data", $allenamento["data"], "fa-calendar") ?>
      </div>


      <div class="col-md-6">
      <?php echo_detail_card("Durata",$allenamento["durata"]." minuti","fa-clock") ?>
      </div>
    </div>
    <div class="row">
      <div class="col-md-6">
      <?php echo_detail_card("Numero di salti",$allenamento["salti"],"fa-dumbbell") ?>
      </div>


      <div class="col-md-6">
      <?php echo_detail_card("Calorie bruciate", $allenamento["calorie"], "fa-fire") ?>
      </div>
    </div>

    <div class="row">
      <div class="col-md-6">
      <?php echo_detail_card("Salti per minuto",$allenamento["salti"]/$allenamento["durata"],"fa-arrow-trend-up") ?>
      </div>


      <div class="col-md-6">
      <?php echo_detail_card("Calorie per minuto", $allenamento["calorie"]/$allenamento["durata"], "fa-chart-simple") ?>
      </div>
    </div>
    <div class="row">
  <div class"col-md-12">
  <div class="card allenamento-detail-card">
    <div class="card-body">
      <div class="row">
        <div class="col-5 text-center my-auto">
        <div class="progress blue">
                 <span class="progress-left">
                                   <span class="progress-bar"></span>
                 </span>
                 <span class="progress-right">
                                   <span class="progress-bar"></span>
                 </span>
                 <div class="progress-value">8%</div>
               </div>
        </div>
        <div class="col-7 text-center">
          <h4 class="card-title"">Obiettivo</h4>
          <h5 class="card-text">50</h5>
        </div>
      </div>
    </div>
  </div>
</div>
</div> 
  </div>

  <!-- Change Goal Modal -->

  <script src="https://kit.fontawesome.com/98491d0baf.js" crossorigin="anonymous"></script>
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.bundle.min.js"></script>
  <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.2/dist/umd/popper.min.js"></script>
  <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"></script>
</body>

</html>