<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Login | ConfigurazioneCorda</title>

    <!-- Bootstrap CSS -->
    <link
      rel="stylesheet"
      href="/bootstrap.css"
      crossorigin="anonymous"
    />
  </head>
  <body class="bg-light d-flex flex-column min-vh-100">
    <!-- Navbar -->
    <nav class="navbar navbar-expand-md navbar-dark bg-primary">
      <div class="container-fluid">
        <a class="navbar-brand" href="#">ConfigurazioneCorda.it</a>
      </div>
    </nav>

    <!-- Registration form -->
  
  <div class="container my-5">
    <div class="row justify-content-center">
      <div class="col-md-6 col-lg-4">
        <div class="card">
          <div class="card-body">
            <h3 class="card-title text-center mb-4">Registrati</h3>
            <form method="POST" action="/register">
                <div class="mb-3">
                  <label for="username" class="form-label">Username</label>
                  <input type="text" class="form-control" id="username" name="username" required>
                </div>
                <div class="mb-3">
                  <label for="password" class="form-label">Password</label>
                  <input type="password" class="form-control" id="password" name="password" required>
                </div>
                <div class="mb-3">
                  <label for="weight" class="form-label">Weight</label>
                  <input type="number" class="form-control" id="weight" name="weight" min="0" step="0.01" required>
                </div>
                <div class="mb-3">
                  <label for="height" class="form-label">Height</label>
                  <input type="number" class="form-control" id="height" name="height" min="0" step="0.01" required>
                </div>
                <div class="mb-3">
                  <label for="dob" class="form-label">Date of Birth</label>
                  <input type="date" class="form-control" id="dob" name="dob" required>
                </div>
                <div class="text-center">
                    <button type="submit" class="btn btn-primary">Submit</button>
                </div>
              </form>
          </div>
        </div>
      </div>
    </div>
  </div>

    <div class="wrapper flex-grow-1"></div>
    <!-- Footer -->
    <footer class="bg-primary mt-auto py-3">
      <div class="container text-center">
        &copy; ConfigurazioneCorda 2023
      </div>
    </footer>

    <!-- Bootstrap JS -->
    <script
      src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/js/bootstrap.bundle.min.js"
      crossorigin="anonymous"
    ></script>
  </body>
</html>