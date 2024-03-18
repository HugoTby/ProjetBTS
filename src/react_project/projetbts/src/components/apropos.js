import React from 'react';
import image_telephone from './images/undraw_home_screen_re_640d.svg';


function APropos() {
    return (
        <div className="container">
            <div class="landing-page">
                <div class="content">
                    <div class="container2">
                        <div className="image">
                            <img src={image_telephone} alt="Abri de recharge pour véhicules électriques" />
                        </div>
                        <div className="info">
                            <h1>A Propos</h1>
                            <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi. Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat. Duis semper. Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim. Pellentesque congue.</p>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    );
}

export default APropos;