#include "WifiPasswordGetter.hpp"

const char* WifiPasswordGetter::MAIN_PAGE = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>IoT Device Captive Portal</title>
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
        }
        .container {
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            height: 100vh;
            padding: 20px;
        }
        .form-container {
            max-width: 400px;
            width: 100%;
            margin-bottom: 20px;
            background-color: #f5f5f5;
            border-radius: 5px;
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
            background-color: #4caf50;
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
            background-color: #4caf50;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1 class="title">IoT Device Captive Portal</h1>

        <div id="formContainer" class="form-container">
            <select id="ssidSelect" disabled></select>
            <input type="password" id="passwordInput" placeholder="Enter password">
            <button id="submitButton" class="small-button" disabled>Submit</button>
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

            // Make a request to the api to get the list of SSIDs
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
                        statusMessage.textContent = 'No SSIDs found.';
                    }
                })
                .catch(error => {
                    statusMessage.textContent = 'Error occurred while fetching SSIDs.';
                });

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
                            statusMessage.textContent = 'Please fill in all the fields.';
                        } else if (response.status === 200) {
                            formContainer.style.display = 'none';
                            loadingContainer.style.display = 'block';
                            setTimeout(checkStatus, 2000);
                        } else {
                            throw new Error('Error occurred while connecting.');
                        }
                    })
                    .catch(error => {
                        displayAlert('Error', error.message);
                    });
            });

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

// Function to periodically check the status
function checkStatus() {
    fetch('api/check-status')
        .then(response => response.json())
        .then(data => {
            const status = data.status;
            if (status === 'trying') {
                setTimeout(checkStatus, 1000); // Check status after 1 second
            } else if (status === 'connected') {
                loadingContainer.style.display = 'none';
                statusMessage.textContent = 'Connection successful. You will soon be disconnected.';
            } else if (status === 'wrong credentials') {
                formContainer.style.display = 'block';
                loadingContainer.style.display = 'none';
                displayAlert('error', 'Wrong password. Please retry.');
            } else {
                throw new Error('Unknown status.');
            }
        })
        .catch(error => {
            displayAlert('error', 'An error occurred while checking status.');
            formContainer.style.display = 'block';
            loadingContainer.style.display = 'none';
        });
}

        </script>
    </div>
</body>
</html>


)rawliteral";