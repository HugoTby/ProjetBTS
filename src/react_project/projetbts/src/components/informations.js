import React from 'react';
import image_warning from './images/undraw_warning_re_eoyh.svg';


function Informations() {
    return (
        <div className="container">
            <div class="landing-page">
                <div class="content">
                    <div class="container2">
                        <div className="image">
                            <img src={image_warning} alt="Abri de recharge pour véhicules électriques" />
                        </div>
                        <div className="info">
                            <h1>Informations - 503</h1>
                            <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi. Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat. Duis semper. Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim. Pellentesque congue.</p>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    );
}

export default Informations;