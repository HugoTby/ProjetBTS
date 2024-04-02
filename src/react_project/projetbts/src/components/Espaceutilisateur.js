import './css/login.css';
import React, { useState, useCallback } from 'react';
import axios from 'axios';
import { Link, useNavigate } from 'react-router-dom';
import image_signin from './images/undraw_sign_up_n6im.svg';

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
        // Connexion réussie, vous pouvez enregistrer les informations de l'utilisateur dans le state de l'application ou les stocker dans le localStorage, puis rediriger l'utilisateur vers la page souhaitée.
        console.log('Connexion réussie :', response.data.user);

        // Stockez les informations de l'utilisateur dans le state ou le localStorage
        // Redirigez l'utilisateur vers la page souhaitée
        navigate('/user-profile'); // Remplacez '/user-profile' par la route appropriée et utilisez la variable mise à jour
      } else {
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
            <div className="image">
              <img src={image_signin} id="signin" alt="Abri de recharge pour véhicules électriques" />
            </div>
            <div className="login">
              <div className="form">
                <h2>Bienvenue</h2>
                {error && <h1 className="error-login">{error}</h1>} {/* Mettre à jour la balise ici */}
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
                <br />
                <br />
                <h5>
                  <Link to="/forgotten-password">Mot de passe oublié ?</Link>
                </h5>
              </div>
              <button>
                <Link to="/user-profile">accès temporaire (dev only)</Link>
              </button>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}

export default EspaceUser;
