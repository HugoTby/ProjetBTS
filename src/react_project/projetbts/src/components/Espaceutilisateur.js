import './css/login.css';
import React from 'react';
import image_signin from './images/undraw_sign_up_n6im.svg';


function EspaceUser() {
    return (
        <div className="container">
            <div class="landing-page">
            <div className="content" style={{ paddingTop: '55px' }}> 
                    <div class="container2">
                        <div className="image">
                            <img src={image_signin} alt="Abri de recharge pour véhicules électriques" />
                        </div>
                        <div class="login">
                            <div class="form">
                                <h2>Bienvenue</h2>
                                <input type="text" placeholder="Username" />
                                <input type="password" placeholder="Password" />
                                <input type="submit" value="Se connecter" class="submit" />
                            </div>
                        </div>
                    </div>
                </div>



            </div>
        </div>
    );
}

export default EspaceUser;