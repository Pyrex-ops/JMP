<?php

include_once "/php/private/model/auth/auth.php";

function echo_navbar($active_page): void
{

  echo '<nav class="navbar navbar-expand-md bg-primary bg-body-tertiary navbar-dark">
    <div class="container-fluid">
    <a class="navbar-brand">JMPit</a>
    <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNavAltMarkup" aria-controls="navbarNavAltMarkup" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button>
    <div class="collapse navbar-collapse" id="navbarNavAltMarkup">
      <div class="navbar-nav">';
  if (check_login()) {
    if ($active_page == "dashboard") {
      echo '
        <a class="nav-link active" aria-current="page" href="/dashboard">Dashboard</a>
        <a class="nav-link" href="/allenamenti">Allenamenti</a>
        <a class="nav-link" href="/classifica">Classifica</a>
        <a class="nav-link" href="/impostazioni">Impostazioni</a>
        <a class="nav-link" href="/php/logout">Logout</a>
        ';
    } else if ($active_page == "impostazioni") {
      echo '
        <a class="nav-link" href="/dashboard">Dashboard</a>
        <a class="nav-link" href="/allenamenti">Allenamenti</a>
        <a class="nav-link" href="/classifica">Classifica</a>
        <a class="nav-link active" aria-current="page" href="/impostazioni">Impostazioni</a>
        <a class="nav-link" href="/php/logout">Logout</a>
        ';
    } else if ($active_page == "allenamenti") {
      echo '
        <a class="nav-link" href="/dashboard">Dashboard</a>
        <a class="nav-link active" aria-current="page" href="/allenamenti">Allenamenti</a>
        <a class="nav-link" href="/classifica">Classifica</a>
        <a class="nav-link" href="/impostazioni">Impostazioni</a>
        <a class="nav-link" href="/php/logout">Logout</a>
        ';
    } else if($active_page == "classifica") {
      echo '
        <a class="nav-link" href="/dashboard">Dashboard</a>
        <a class="nav-link" href="/allenamenti">Allenamenti</a>
        <a class="nav-link active"aria-current="page" href="/classifica">Classifica</a>
        <a class="nav-link" href="/impostazioni">Impostazioni</a>
        <a class="nav-link" href="/php/logout">Logout</a>
        ';
    }
    
    else {
      echo '
      <a class="nav-link" href="/dashboard">Dashboard</a>
      <a class="nav-link" href="/allenamenti">Allenamenti</a>
      <a class="nav-link" href="/classifica">Classifica</a>
      <a class="nav-link" href="/impostazioni">Impostazioni</a>
      <a class="nav-link" href="/php/logout">Logout</a>
        ';
    }
  } else {
    if ($active_page == "login") {
      echo '
        <a class="nav-link active" aria-current="page" href="/login">Login</a>
        <a class="nav-link" href="/registrazione">Registrazione</a>
        ';
    } else if ($active_page == "registrazione") {
      echo '
        <a class="nav-link" href="/login">Login</a>
        <a class="nav-link active" aria-current="page" href="/registrazione">Registrazione</a>
        ';
    } else {
      echo '
        <a class="nav-link" href="/login">Login</a>
        <a class="nav-link" href="/registrazione">Registrazione</a>
        ';
    }
  }
  echo '
      </div>
    </div>
  </div>
</nav>';
}