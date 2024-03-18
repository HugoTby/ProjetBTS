import React from 'react';
import image_trotinette from './images/undraw_scooter_re_lrsb.svg';
import image_telephone from './images/undraw_home_screen_re_640d.svg';
import image_statistiques from './images/undraw_statistic_chart_re_w0pk.svg';
import image_statut from './images/undraw_completing_re_i7ap.svg';
import logo_laprovidence from './images/logolpr.svg';

import './css/accueil.css';

function Accueil_component() {
    return (
        <div className="container">
            <div class="landing-page">
                <header>
                    <div class="container">
                        {/* <a href={"test"} class="logo">La <b>Providence</b></a> */}
                        <img class="logolpr" src={logo_laprovidence} alt="" />
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
            

            {/* footer section */}

            <footer class="site-footer">
                <div class="container3">
                    <div class="row">
                        <div class="col-sm-12 col-md-6">
                            <h6>A propos</h6>
                            <p class="text-justify">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi. Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat. Duis semper. Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim. Pellentesque congue. Ut in risus volutpat libero pharetra tempor.</p>
                        </div>

                        <div class="col-xs-6 col-md-3">
                            <h6>Divers</h6>
                            <ul class="footer-links">
                                <li><a href={"test"}>Mentions légales</a></li>
                                <li><a href={"test"}>Conditions générales d'utilisation</a></li>
                                <li><a href={"test"}>Politique de confidentialité</a></li>
                            </ul>
                        </div>
                    </div>
                    <hr></hr>
                </div>
                <div class="container3">
                    <div class="row">
                        <div class="col-md-8 col-sm-6 col-xs-12">
                            <p class="copyright-text">Copyright &copy; 2024 tout droits réservés par
                                <a target='blank' href={"https://www.la-providence.net/fr/"}> La Providence Amiens</a>.
                            </p>
                        </div>

                        <div class="col-md-4 col-sm-6 col-xs-12">
                            <ul class="social-icons">
                                <li><a class="facebook" href={"test"}><i class="fa fa-facebook"></i></a></li>
                                <li><a class="twitter" href={"test"}><i class="fa fa-twitter"></i></a></li>
                                <li><a class="dribbble" href={"test"}><i class="fa fa-dribbble"></i></a></li>
                                <li><a class="linkedin" href={"test"}><i class="fa fa-linkedin"></i></a></li>
                            </ul>
                        </div>
                    </div>
                </div>
            </footer>
        </div></div>
    );
}

export default Accueil_component;
