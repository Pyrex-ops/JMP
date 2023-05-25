<?php require_once "/php/private/model/auth/sessione.php";
require_once "/php/private/view/navbar.php";
include_once "/php/private/model/auth/auth.php";
include_once "/php/private/model/user/user.php";
redirect_to_login_if_not_logged_in() ?>

<!DOCTYPE html>
<html>

<head>
  <title>Dashboard</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="/style/bootstrap.css">
  <link rel="stylesheet" href="/style/jmpit.css">
</head>

<body>
  <?php echo_navbar("dashboard") ?>

  <div class="container dashboard-container">
    <h1 class="text-center" style="margin-bottom:30px"> Dashboard </h1>
    <div class="row">
    </div>
    <div class="row">
      <div class="col-md-12">
        <div class="card text-center daysofweek-card">
          <div class="card-body">
            <h5 class="card-title">Ultimi 7 giorni</h5>
            <div id="daysContainer"></div>
          </div>
        </div>
      </div>
    </div>
    <div class="row">
      <div class="col-md-6">
        <div class="card">
          <div class="card-body text-center">
            <h5 class="card-title">Trend</h5>
            <canvas id="activityChart" class="graph"></canvas>
          </div>
        </div>
      </div>
      <div class="col-md-6">
        <div class="card">
          <div class="card-body text-center">
            <h5 class="card-title">Ultimi allenamenti</h5>
            <table class="table table-borderless table-column-width">
              <thead>
                <tr>
                  <th><i class='fa fa-calendar'></i> </th>
                  <th><i class="fa fa-clock"></i></th>
                  <th><i class="fas fa-star"></i></th>
                </tr>
              </thead>
              <tbody id="trainingsContainer"></tbody>
            </table>
            <button onclick="location.href = '/allenamenti';" class="btn btn-primary">Vedi tutti</button>
          </div>
        </div>
      </div>
    </div>
  </div>

  <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.4/Chart.min.js"></script>
  <script src="https://kit.fontawesome.com/98491d0baf.js" crossorigin="anonymous"></script>
  <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.bundle.min.js"></script>
  <script>
    // API response with selected days (example)
    //const selectedDays = ['Lunedì', 'Mercoledì'];
    <?php successful_days_of_week(); ?>

    // Generate circles for last 7 days
    const daysContainer = document.getElementById('daysContainer');
    const daysOfWeek = ['Lunedì', 'Martedì', 'Mercoledì', 'Giovedì', 'Venerdì', 'Sabato', 'Domenica'];
    for (let i = 0; i < 7; i++) {
      const circle = document.createElement('div');
      circle.classList.add('circle');
      if (selectedDays.includes(daysOfWeek[i])) {
        circle.classList.add('green');
      } else {
        circle.classList.add('gray');
      }
      circle.textContent = daysOfWeek[i].charAt(0);
      daysContainer.appendChild(circle);
    }
    // Chart.js code for the activity time trend
    var ctx = document.getElementById('activityChart').getContext('2d');
    <?php duration_graph(); ?>
    var activityChart = new Chart(ctx, {
      type: 'line',
      data: {
        //labels: ['23/04', '30/04', '06/05', '13/05'],
        labels: arrayDate,
        datasets: [{
          label: 'Tempo di attività',
          //data: [30, 45, 60, 50],
          data: arrayDurata,
          backgroundColor: '#198754',
          borderColor: '#198754',
          borderWidth: 1
        }]
      },
      options: {
        elements: {
          point:{
            radius: 0
          }
        },
        scales: {
          xAxes: [{
            ticks: {
              autoSkip: true,
              maxTicksLimit: 5
            },
            gridLines: {
              display:false,
            }
          }],
          yAxes: [{
            ticks: {
              beginAtZero: true,
              stepSize: 30
            },
            gridLines: {
              display:false,
            }
          }]
        }
      }
    });

    // Generate training boxes
    const trainingsContainer = document.getElementById('trainingsContainer');
    const trainingsData = /*[
      { name: '03/05', duration: '45 min', goalReached: false },
      { name: '07/05', duration: '70 min', goalReached: true },
      { name: '10/05', duration: '30 min', goalReached: false }]*/
      <?php last_trainings(); ?>;

    maxTrainingTime = parseInt(trainingsData.sort(
      function (a, b) {
        return parseInt(b['duration']) - parseInt(a['duration']);
      }
    )[0]['duration'])

    if(maxTrainingTime===0) {
            maxTrainingTime = 1;
        }

    trainingsData.sort(
      function (a, b) {
        return parseInt(b['id']) - parseInt(a['id']);
      }
    )

    trainingsData.forEach(training => {
      const row = document.createElement('tr');

      const titleCell = document.createElement('td');
      titleCell.textContent = training.name;
      row.appendChild(titleCell);

      const progressCell = document.createElement('td');
      const progressBar = document.createElement('div');
      progressBar.classList.add('progress');
      progressBar.style.height = '20px';
      progressBar.innerHTML = `
    <div class="progress-bar" role="progressbar" style="width: ${100 * parseInt(training.duration) / maxTrainingTime}%;" aria-valuenow="${parseInt(training.duration)}" aria-valuemin="0" aria-valuemax="${maxTrainingTime}">${training.duration}</div>
  `;
      progressCell.appendChild(progressBar);
      row.appendChild(progressCell);

      const goalCell = document.createElement('td');
      if (training.goalReached) {
        const starIcon = document.createElement('i');
        starIcon.classList.add('fas', 'fa-star');
        goalCell.appendChild(starIcon);
        goalCell.appendChild(starIcon);
      }
      row.appendChild(goalCell);

      trainingsContainer.appendChild(row);
    });
  </script>
</body>

</html>