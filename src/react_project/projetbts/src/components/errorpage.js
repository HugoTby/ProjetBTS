import React from 'react';
import { Link } from 'react-router-dom';
import image_warning from './images/undraw_warning_re_eoyh.svg';

function Error() {
  return (
    <div className="container">
            <div class="landing-page">
                <div class="content">
                    <div class="container2">
                        <div className="image">
                            <img src={image_warning} alt="Abri de recharge pour véhicules électriques" />
                        </div>
                        <div className="info">
                            <h1>Error 404</h1>
                            <p>Désolé, la page que vous recherchez semble avoir disparu dans les profondeurs du web ! Il est possible que l'adresse soit incorrecte ou que la page ait été déplacée ou supprimée. Ne vous inquiétez pas, vous pouvez utiliser le menu principal pour trouver ce que vous cherchez. Sinon, vous pouvez toujours revenir à la page d'accueil en cliquant sur le logo en haut de la page. Merci de votre compréhension et bonne navigation !</p>
                            <button> <Link to="/">Accueil</Link></button>
                        </div>
                    </div>
                </div>
            </div>
        </div>
  );
}

export default Error;
