#include "WifiPasswordGetter.hpp"

const char* WifiPasswordGetter::MAIN_PAGE = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
    <title>Configurazione WiFi</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        /* CSS styles */
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }

        body {
            font-family: Arial, sans-serif;
            text-align: center;
            background-color: #bb2323;

        }

        .container {
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            height: 100vh;
            padding: 20px;
            background-color: #f1f1f1;

        }

        .form-container {
            max-width: 400px;
            width: 100%;
            margin-bottom: 20px;
            background-color: #fff;
            border-radius: 5px;
            border: 1px solid #ccc;
            padding: 20px;
        }

        .form-container select,
        .form-container input[type="password"],
        .form-container button {
            width: 100%;
            padding: 10px;
            margin-bottom: 10px;
            border-radius: 5px;
            border: 1px solid #ccc;
            font-size: 16px;
        }

        .form-container button {
            background-color: #198754;
            color: #fff;
            cursor: pointer;
        }

        .form-container button:disabled {
            background-color: #ccc;
            cursor: not-allowed;
        }

        .loading-container {
            display: none;
            max-width: 400px;
            width: 100%;
        }

        .loading-animation {
            width: 50px;
            height: 50px;
            border: 5px solid #ccc;
            border-top-color: #333;
            border-radius: 50%;
            animation: spin 1s infinite linear;
            margin: 0 auto 20px auto;
        }

        .status-message {
            margin-bottom: 20px;
        }

        .alert-container {
            margin-top: 20px;
            text-align: center;
        }

        .alert-box {
            display: inline-block;
            padding: 10px;
            background-color: #f44336;
            color: #fff;
            border-radius: 5px;
        }

        .small-button {
            width: 120px;
            padding: 8px;
            font-size: 14px;
        }

        .title {
            font-size: 24px;
            margin-bottom: 20px;
        }

        @keyframes spin {
            0% {
                transform: rotate(0deg);
            }

            100% {
                transform: rotate(360deg);
            }
        }

        /* Mobile-specific styles */
        @media (max-width: 480px) {
            .loading-animation {
                margin: 0 auto;
            }
        }

        .alert-container {
            margin-top: 20px;
            text-align: center;
        }

        .alert-box {
            display: inline-block;
            padding: 10px;
            background-color: #f44336;
            color: #fff;
            border-radius: 5px;
        }

        .error {
            background-color: #f44336;
        }

        .success {
            background-color: #198754;
        }

        #refreshButton {
            background-color: #2196f3;
            color: #fff;
            margin-top: 10px;
            width: 40px;
            height: 40px;
            display: flex;
            align-items: center;
            justify-content: center;
            border: none;
            border-radius: 5px;
        }

        #refreshButton:hover {
            background-color: #1976d2;
        }

        @media (max-width: 480px) {
            #refreshButton {
                width: 100%;
            }
        }
    </style>
</head>

<body>
    <div class="container">

        <h1 class="title">Configurazione WiFi</h1>
        <div id="formContainer" class="form-container">
            <select id="ssidSelect" disabled></select>
            <div style="display: flex; align-items: center; justify-content: center;">
                <span style="margin-left: 5px;">Aggiorna reti WiFi</span>
                <button id="refreshButton" class="small-button"
                    style="width: 40px; height: 40px; display: flex; align-items: center; justify-content: center; border: none; margin-left:20px;border-radius: 5px; background-color: #198754; color: #fff; margin-top: 10px;">
                    &#x21bb;
                </button>
            </div>
            <input type="password" id="passwordInput" placeholder="Inserisci la password">
            <button id="submitButton" class="small-button" disabled>Invia</button>
        </div>

        <div id="loadingContainer" class="loading-container">
            <div class="loading-animation"></div>
            <div id="statusMessage" class="status-message"></div>
        </div>

        <div id="alertContainer" class="alert-container"></div>

        <script>
            // JavaScript code
            const formContainer = document.getElementById('formContainer');
            const ssidSelect = document.getElementById('ssidSelect');
            const passwordInput = document.getElementById('passwordInput');
            const submitButton = document.getElementById('submitButton');
            const loadingContainer = document.getElementById('loadingContainer');
            const statusMessage = document.getElementById('statusMessage');
            const alertContainer = document.getElementById('alertContainer');
            var attemptNumber = 0;

            // Make a request to the api to get the list of SSIDs
            getSsids();

            // Function to display an alert message
            function displayAlert(type, message) {
                const alertElement = document.createElement('div');
                alertElement.className = `alert-box ${type}`;
                alertElement.textContent = message;

                alertContainer.innerHTML = ''; // Clear previous alerts
                alertContainer.appendChild(alertElement);

                // Remove the alert after 3 seconds
                setTimeout(() => {
                    alertContainer.innerHTML = '';
                }, 3000);
            }


            function getSsids() {
                fetch('api/get-ssids')
                    .then(response => response.json())
                    .then(data => {
                        if (data.ssids && data.ssids.length > 0) {
                            // Populate the SSID select dropdown
                            data.ssids.forEach(ssid => {
                                const option = document.createElement('option');
                                option.value = ssid;
                                option.textContent = ssid;
                                ssidSelect.appendChild(option);
                            });

                            ssidSelect.disabled = false;
                            submitButton.disabled = false;
                        } else {
                            formContainer.style.display = 'block';
                            loadingContainer.style.display = 'none';
                            displayAlert('error', 'Nessuna rete WiFi trovata.');
                        }
                    })
                    .catch(error => {
                        statusMessage.textContent = 'Error occurred while fetching SSIDs.';
                    });
            }



            // Submit button click event
            submitButton.addEventListener('click', () => {
                const ssid = ssidSelect.value;
                const password = passwordInput.value;

                // Make a POST request to the api with credentials
                fetch('api/connect', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({ ssid, password })
                })
                    .then(response => {
                        if (response.status === 400) {
                            displayAlert('error', 'Compilare tutti i campi.');
                            formContainer.style.display = 'block';
                            loadingContainer.style.display = 'none';
                        } else if (response.status === 200) {
                            formContainer.style.display = 'none';
                            loadingContainer.style.display = 'block';
                            attemptNumber = 0;
                            setTimeout(checkStatus, 2000);
                        } else {
                            throw new Error('Error occurred while connecting.');
                        }
                    })
                    .catch(error => {
                        displayAlert('Error', error.message);
                    });
            });

            // Add the refresh button variable
            const refreshButton = document.getElementById('refreshButton');

            // Refresh button click event
            refreshButton.addEventListener('click', () => {
                // Clear the SSID select dropdown and password input
                ssidSelect.innerHTML = '';
                passwordInput.value = '';

                fetch('api/refresh-ssids');

                // Make a request to get the updated list of SSIDs
                getSsids();
            });


            // Function to periodically check the status
            function checkStatus() {
                fetch('api/check-status')
                    .then(response => response.json())
                    .then(data => {
                        const status = data.status;
                        if (status === 'trying') {
                            if (attemptNumber < 3) {
                                attemptNumber++;
                                setTimeout(checkStatus, 1000); // Check status after 1 second
                            }
                            else {
                                displayAlert('error', 'Errore di connessione. Riprovare.');
                                formContainer.style.display = 'block';
                                loadingContainer.style.display = 'none';
                            }
                        } else if (status === 'connected') {
                            displayAlert('success', 'Configurazione completata. A breve verrai disconnesso.');
                            formContainer.style.display = 'none';
                            loadingContainer.style.display = 'none';
                        } else if (status === 'wrong credentials') {
                            formContainer.style.display = 'block';
                            loadingContainer.style.display = 'none';
                            displayAlert('error', 'Password errata. Riprovare.');
                        } else {
                            throw new Error('Unknown status.');
                        }
                    })
                    .catch(error => {
                        displayAlert('error', 'Errore generico. Riprovare.');
                        formContainer.style.display = 'block';
                        loadingContainer.style.display = 'none';
                    });
            }

        </script>
    </div>
</body>

</html>
)rawliteral";