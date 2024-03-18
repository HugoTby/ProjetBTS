import React from 'react';
import { Link } from 'react-router-dom';

function Navigation() {
  return (
    <div className="container">
    <div class="landing-page">
      <header>
        <div class="container">
          <img class="logolpr" src="logolpr.svg" alt="" />
          <ul class="links">
            <li>
              <Link to="/">Accueil</Link>
            </li>
            <li>
              <Link to="/apropos">A propos</Link>
            </li>
            <li>Informations</li>
            <li>Espace utilisateur</li>
          </ul>
        </div>
      </header>
    </div>
  </div>
  );
}

export default Navigation;
