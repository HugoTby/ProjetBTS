import React, { useState } from 'react';
import image_trotinette from './images/undraw_scooter_re_lrsb.svg';
import logo_laprovidence from './images/logolpr.svg';

import './css/login.css';

function Login_component() {
    return (
        <div className="container">
            <div class="landing-page">
                <header>
                    <div class="container">
                        {/* <a href="#" class="logo">La <b>Providence</b></a> */}
                        <img class="logolpr" src={logo_laprovidence} />
                        <ul class="links">
                            <li>Accueil</li>
                            <li>A propos</li>
                            <li>Informations</li>
                            <li>Espace utilisateur</li>
                        </ul>
                    </div>
                </header>
                <div class="content">
                    <div class="container">
                        <div className="info">
                            <h1>Notre projet : un abri de recharge pour véhicules électriques</h1>
                            <p>Découvrez notre solution innovante pour la recharge de vos véhicules électriques. Notre abri de recharge est conçu pour offrir une expérience de recharge rapide, fiable et confortable.</p>
                            <button>En savoir plus</button>
                        </div>
                        <div className="image">
                            <img src={image_trotinette} alt="Abri de recharge pour véhicules électriques" />
                        </div>
                    </div>
                </div>
            </div>
        </div>
    );
}

export default Login_component;
