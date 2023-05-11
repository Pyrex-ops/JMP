<?php require_once "/php/private/model/db/sessione.php";
require_once "/php/private/view/navbar.php"; ?>

<!DOCTYPE html>
<html>

<head>
  <title>User Dashboard</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="/style/bootstrap.css">
  <link rel="stylesheet" href="/style/jmpit.css">
</head>

<body>
  <?php echo_navbar() ?>

  <div class="container dashboard-container">
    <h1 class="text-center" style="margin-bottom:30px"> Dashboard </h1>
    <div class="row">
      <div class="col-md-6 mx-auto">
        <div class="card text-center username-card first-card">
          <div class="card-body">
            <div class="user-profile-picture">
              <img src="https://api.multiavatar.com/Moguserr.png" alt="User Picture" width="100" height="100">
            </div>
            <h3 class="card-title">Moguser</h5>
          </div>
        </div>
      </div>
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
              <tbody id="trainingsContainer"></tbody>
            </table>
            <button class="btn btn-primary">Vedi tutti</button>
          </div>
        </div>
      </div>
    </div>
  </div>

  <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.4/Chart.min.js"></script>
  <script>
    // API response with selected days (example)
    const selectedDays = ['Lunedì', 'Mercoledì'];

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
    var activityChart = new Chart(ctx, {
      type: 'line',
      data: {
        labels: ['23/04', '30/04', '06/05', '13/05'],
        datasets: [{
          label: 'Tempo di attività',
          data: [30, 45, 60, 50],
          backgroundColor: '#198754',
          borderColor: '#198754',
          borderWidth: 1
        }]
      },
      options: {

        scales: {
          yAxes: [{
            ticks: {
              beginAtZero: true
            }
          }]
        }
      }
    });

    // Generate training boxes
    const trainingsContainer = document.getElementById('trainingsContainer');
    const trainingsData = [
      { name: '03/05', duration: '45 min', goalReached: false },
      { name: '07/05', duration: '70 min', goalReached: true },
      { name: '10/05', duration: '30 min', goalReached: false }
    ];

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
    <div class="progress-bar" role="progressbar" style="width: ${parseInt(training.duration)}%;" aria-valuenow="${parseInt(training.duration)}" aria-valuemin="0" aria-valuemax="100">${training.duration}</div>
  `;
      progressCell.appendChild(progressBar);
      row.appendChild(progressCell);

      const goalCell = document.createElement('td');
      if (training.goalReached) {
        const starIcon = document.createElement('i');
        starIcon.classList.add('star', 'goal-reached');
        starIcon.textContent = '★';
        goalCell.appendChild(starIcon);
      }
      row.appendChild(goalCell);

      trainingsContainer.appendChild(row);
    });
  </script>
</body>

</html>