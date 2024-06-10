import React from 'react';
import { Link } from 'react-router-dom';

function Navigation() {
  return (
    <div className="container">
      <div class="landing-page">
        <header>
          <div class="container">
          <Link to="/"><img class="logolpr" src="logolpr.svg" alt="" /></Link>
            <ul class="links">
              <li>
                <Link to="/">Accueil</Link>
              </li>
              <li>
                <Link to="/about">A propos</Link>
              </li>
              <li>
                <Link to="/current-news">Informations</Link>
              </li>
              <Link to="/sign-in"><li>
                Espace utilisateur
                </li></Link>
            </ul>
          </div>
        </header>
      </div>
    </div>
  );
}

export default Navigation;
