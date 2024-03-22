import './css/login.css';
import React from 'react';
import { Link } from 'react-router-dom';
import image_signin from './images/undraw_sign_up_n6im.svg';


function EspaceUser() {
    return (
        <div className="container">
            <div class="landing-page">
                <div className="content" style={{ paddingTop: '55px' }}>
                    <div class="container2">
                        <div className="image">
                            <img src={image_signin} id='signin' alt="Abri de recharge pour véhicules électriques" />
                        </div>
                        <div class="login">
                            <div class="form">
                                <h2>Bienvenue</h2>
                                <input type="text" placeholder="prenom.nom" />
                                <input type="password" placeholder="mot de passe" />
                                <input type="submit" value="Se connecter" class="submit" />
                                <br /><br />
                                <h5><Link to="/forgotten-password">Mot de passe oublié ?</Link></h5>
                            </div>                        
                            <button><Link to="/user-profile">temp access account</Link></button>
                        </div>
                    </div>
                </div>



            </div>
        </div>
    );
}

export default EspaceUser;