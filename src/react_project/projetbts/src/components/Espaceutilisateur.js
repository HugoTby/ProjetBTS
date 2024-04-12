import './css/login.css';
import React, { useState, useCallback } from 'react';
import axios from 'axios';
import Cookies from 'js-cookie';
import { Link, useNavigate } from 'react-router-dom';
// import image_signin from './images/undraw_sign_up_n6im.svg';

function EspaceUser() {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [error, setError] = useState(null);
  const navigate = useNavigate();

  const handleSubmit = useCallback(async (event) => {
    event.preventDefault();

    try {
      const response = await axios.post('http://192.168.65.105:5001/login', {
        username,
        password,
      });

      if (response.data.success) {
        console.log('Connexion réussie :', response.data.user);

        // Créez un cookie de connexion qui expire au bout d'une heure
        const expires = new Date();
        expires.setTime(expires.getTime() + 60 * 60 * 1000); // Ajoute 1 heure en millisecondes
        Cookies.set('user', JSON.stringify(response.data.user), { expires });

        // Redirigez l'utilisateur vers la page souhaitée
        navigate('/user-profile');
      }

      else {
        // La connexion a échoué, affichez un message d'erreur à l'utilisateur.
        setError(response.data.message);
      }
    } catch (error) {
      // Une erreur s'est produite lors de la requête, affichez un message d'erreur à l'utilisateur.
      setError('Identifiants incorrects');
    }
  }, [username, password, navigate]);

  return (
    <div className="container">
      <div className="landing-page">
        <div className="content" style={{ paddingTop: '55px' }}>
          <div className="container2">
            {/* <div className="image">
              <img src={image_signin} id="signin" alt="Abri de recharge pour véhicules électriques" />
            </div> */}
            <div className="login">
              <div className="form">
                {/* <h2>Bienvenue</h2> */}
                <form onSubmit={handleSubmit}>
                  <input
                    type="text"
                    placeholder="prenom.nom"
                    value={username}
                    onChange={(e) => setUsername(e.target.value)}
                  />
                  <input
                    type="password"
                    placeholder="mot de passe"
                    value={password}
                    onChange={(e) => setPassword(e.target.value)}
                  />
                  <input type="submit" value="Se connecter" className="submit" />
                </form>
                <h5>
                  <Link to="/forgotten-password">Mot de passe oublié ?</Link>
                </h5>
                {error && <h1 className="error-login">{error}</h1>} {/* Mettre à jour la balise ici */}
              </div>
            </div>
          </div>

        </div>
      </div>
    </div>
  );
}

export default EspaceUser;
