import React from 'react';
import { Link } from 'react-router-dom';
import image_trotinette from './images/undraw_scooter_re_lrsb.svg';
import image_telephone from './images/undraw_home_screen_re_640d.svg';
import image_statistiques from './images/undraw_statistic_chart_re_w0pk.svg';
import image_statut from './images/undraw_completing_re_i7ap.svg';

import './css/accueil.css';

function Accueilcomponent() {
    return (
        <div className="container">
            <div class="landing-page">
                <div class="content">
                    <div class="container">
                        <div className="info">
                            <h1>Notre projet : un abri de recharge pour véhicules électriques</h1>
                            <p>Découvrez notre solution innovante pour la recharge de vos véhicules électriques. Notre abri de recharge est conçu pour offrir une expérience de recharge rapide, fiable et confortable.</p>
                            <button> <Link to="/apropos">En savoir plus</Link></button>
                        </div>
                        <div className="image">
                            <img src={image_trotinette} alt="Abri de recharge pour véhicules électriques" />
                        </div>
                    </div>
                    <div class="container2">
                        <div className="image">
                            <img src={image_telephone} alt="Abri de recharge pour véhicules électriques" />
                        </div>
                        <div className="info">
                            <h1>Gérer votre emplacement depuis votre smartphone</h1>
                            <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi. Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat. Duis semper. Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim. Pellentesque congue.</p>
                        </div>
                    </div>
                    <div class="container2">
                        <div className="info">
                            <h1>Visualisez vos données de consommation d'énergie</h1>
                            <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi. Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat. Duis semper. Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim. Pellentesque congue.</p>
                        </div>
                        <div className="image">
                            <img src={image_statistiques} alt="Abri de recharge pour véhicules électriques" />
                        </div>
                    </div>
                    <div class="container2">
                        <div className="image">
                            <img src={image_statut} alt="Abri de recharge pour véhicules électriques" />
                        </div>
                        <div className="info">
                            <h1>Obtenez le statut de votre charge en direct</h1>
                            <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi. Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat. Duis semper. Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim. Pellentesque congue.</p>
                        </div>
                    </div>
                </div>
            

           
        </div></div>
    );
}

export default Accueilcomponent;
