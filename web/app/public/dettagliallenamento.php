<!DOCTYPE html>
<html>
<head>
  <title>Workout Session</title>
  <link rel="stylesheet" href="/style/bootstrap.css">
  <link rel="stylesheet" href="/style/jmpit.css">
  <style>
    /* Custom CSS Styles */
    .progress {
      width: 150px;
      height: 150px !important;
      float: left; 
      line-height: 150px;
      background: none;
      margin: 20px;
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
      border-width: 12px;
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
      animation: loading-1 1.8s linear forwards;
    }
    .progress .progress-value {
      width: 90%;
      height: 90%;
      border-radius: 50%;
      background: #fff;
      font-size: 24px;
      color: #000;
      line-height: 135px;
      text-align: center;
      position: absolute;
      top: 5%;
      left: 5%;
    }
    .progress.blue .progress-bar {
      border-color: #049dff;
    }
    .progress.blue .progress-left .progress-bar {
      animation: loading-2 1.5s linear forwards 1.8s;
    }
    .progress.yellow .progress-bar {
      border-color: #fdba04;
    }
    .progress.yellow .progress-right .progress-bar {
      animation: loading-3 1.8s linear forwards;
    }
    .progress.yellow .progress-left .progress-bar {
      animation: none;
    }
    @keyframes loading-1 {
      0% {
        -webkit-transform: rotate(0deg);
        transform: rotate(0deg);
      }
      100% {
        -webkit-transform: rotate(180deg);
        transform: rotate(180deg);
      }
    }
    @keyframes loading-2 {
      0% {
        -webkit-transform: rotate(0deg);
        transform: rotate(0deg);
      }
      100% {
        -webkit-transform: rotate(144deg);
        transform: rotate(144deg);
      }
    }
    @keyframes loading-3 {
      0% {
        -webkit-transform: rotate(0deg);
        transform: rotate(0deg);
      }
      100% {
        -webkit-transform: rotate(135deg);
        transform: rotate(135deg);
      }
    }
  </style>
</head>
<body>

<?php
// Assign example values to the variables
$date = date('Y-m-d');
$duration = '60 minutes';
$caloriesBurned = 500;
$jumps = 80;
$goal = 100;
?>

<div class="container text-center">
  <div class="col-md-6">
    <div class="card-text">
      <div class="card">
        <div class="card-body">
          <h6 class="card-subtitle">Date</h6>
          <p class="card-text"><?php echo $date; ?></p>
        </div>
      </div>
      <div class="card">
        <div class="card-body">
          <h6 class="card-subtitle">Duration</h6>
          <p class="card-text"><?php echo $duration; ?></p>
        </div>
      </div>
      <div class="card">
        <div class="card-body">
          <h6 class="card-subtitle">Calories Burned</h6>
          <p class="card-text"><?php echo $caloriesBurned; ?></p>
        </div>
      </div>
    </div>
    <div id="jumpsGraphContainer">
      <canvas id="jumpsGraph"></canvas>
    </div>
    <div class="card">
      <div class="card-body">
        <h6 class="card-subtitle">Goal</h6>
        <p class="card-text"><?php echo $goal; ?> jumps</p>
      </div>
    </div>
    <div class="circle-graph">
      <div class="col-md-3 col-sm-6">
        <div class="progress blue">
          <span class="progress-left">
            <span class="progress-bar"></span>
          </span>
          <span class="progress-right">
            <span class="progress-bar"></span>
          </span>
          <div class="progress-value">90%</div>
        </div>
      </div>
    </div>
    <?php
      if ($jumps >= $goal) {
        echo '<p class="card-text text-success">Goal Reached! Congratulations!</p>';
      } else {
        echo '<p class="card-text">Goal Not Reached. Keep Trying!</p>';
      }
    ?>
    <a href="#" class="btn btn-primary btn-block mt-3">Return to Training Sessions</a>
  </div>
</div>

<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
<script>
  // JavaScript code for the jumps graph
  var jumpsData = {
    labels: ['0', '10', '20', '30', '40', '50', '60'],
    datasets: [{
      label: 'Jumps',
      data: [0, 5, 10, 8, 15, 12, <?php echo $jumps; ?>], // Use the $jumps variable here
      backgroundColor: 'rgba(0, 123, 255, 0.5)',
      borderColor: 'rgba(0, 123, 255, 1)',
      borderWidth: 2,
      fill: false
    }]
  };

  var jumpsOptions = {
    responsive: true,
    maintainAspectRatio: false,
    scales: {
      y: {
        beginAtZero: true
      }
    }
  };

  var jumpsChart = new Chart(document.getElementById('jumpsGraph'), {
    type: 'line',
    data: jumpsData,
    options: jumpsOptions
  });
</script>

</body>
</html>
