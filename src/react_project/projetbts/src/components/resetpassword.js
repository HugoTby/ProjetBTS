import React from 'react';
import image_warning from './images/undraw_warning_re_eoyh.svg';


function ForgottenPassword() {
    return (
        <div className="container">
            <div class="landing-page">
                <div class="content">
                    <div class="container2">
                        <div className="image">
                            <img src={image_warning} alt="Abri de recharge pour véhicules électriques" />
                        </div>
                        <div className="info">
                            <h1>Reset - 503</h1>
                            <p>Formulaire de contact admin (en développement)</p>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    );
}

export default ForgottenPassword;